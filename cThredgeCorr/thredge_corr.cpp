/* 
 * The MIT License (MIT)
 * Copyright (c) 2018, Benjamin Maier
 *
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without 
 * restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall 
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-
 * INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 */

#include "Utilities.h"
#include "thredge_corr.h"
#include <assert.h>

using namespace std;

size_t edge_index(size_t const &N,
                  size_t const &i,
                  size_t const &j
                  )
{
    return i*N + j - (i+2)*(i+1) / 2;
}

vector < pair < size_t, size_t > > get_slow_edge_list( size_t N, 
                                                  double rho, 
                                                  double t,
                                                  vector < double > parameters,
                                                  double seed
                                                )
{

    assert(N>=3);
    assert(rho >= 0.0 && rho < 0.5);   
    assert(parameters.size() == 3);
    double a = parameters[0];
    double b = parameters[1];
    double c = parameters[2];
    size_t m = N * (N - 1) / 2;

    mt19937_64 generator;
    if (seed == 0)
        randomly_seed_engine(generator);
    else
        generator.seed(0);

    normal_distribution<double> randn(0.0,1.0);

    vector < double > Y;

    double s = 0.0;
    for(size_t e = 0; e<m; ++e)
    {
        double r = randn(generator);
        Y.push_back(r);
        s += r;
    }

    vector < double > w;
    for(size_t i = 0; i<N; ++i)
    {
        double this_w = 0.0;
        for(size_t j = 0; j<i; ++j)
            this_w += Y[edge_index(N,j,i)];
        for(size_t j = i+1; j<N; ++j)
            this_w += Y[edge_index(N,i,j)];
        w.push_back(this_w);
    }

    vector <double> X;

    for(size_t e = 0; e<m; ++e)
    {
        double x = (a - 2*b + c) * Y[e] + c*s;
        X.push_back(x);
    }

    vector < pair < size_t, size_t > > edges;
    for(size_t i = 0; i<N-1; ++i)
    {
        for(size_t j = i+1; j<N; ++j)
        {
            size_t e = edge_index(N,i,j);
            X[e] += (b-c) * (w[i]+w[j]);
            if (X[e] >= t)
                edges.push_back(make_pair(i,j));
        }
    }
    return edges;
}

vector < pair < size_t, size_t > > get_edge_list( size_t N, 
                                                  double rho, 
                                                  double t,
                                                  vector < double > parameters,
                                                  double seed
                                                )
{

    //cout << "Greetings! You called the pointer method!" << endl;

    assert(N>=3);
    assert(rho >= 0.0 && rho < 0.5);   
    assert(parameters.size() == 3);
    double a = parameters[0];
    double b = parameters[1];
    double c = parameters[2];
    size_t m = N * (N - 1) / 2;

    mt19937_64 generator;
    if (seed == 0)
        randomly_seed_engine(generator);
    else
        generator.seed(0);

    normal_distribution<double> randn(0.0,1.0);

    vector < double > Y;

    double s = 0.0;
    for(size_t e = 0; e<m; ++e)
    {
        double r = randn(generator);
        Y.push_back(r);
        s += r;
    }

    vector < double > w;
    auto it_Yi = Y.begin();
    // fill for j first
    for(size_t i = 0; i<N; ++i)
    {
        double this_w = 0.0;
        for(size_t j = 0; j<i; ++j)
            this_w += Y[edge_index(N,j,i)];
        for(size_t j = i+1; j<N; ++j)
        {
            this_w += *it_Yi;
            ++it_Yi;
        }
        w.push_back(this_w);
    }

    vector <double> X;

    auto it_Y = Y.begin();
    for(size_t e = 0; e<m; ++e)
    {
        double x = (a - 2*b + c) * (*it_Y) + c*s;
        X.push_back(x);
        ++it_Y;
    }

    vector < pair < size_t, size_t > > edges;
    auto it_x = X.begin();
    auto it_wi = w.begin();
    for(size_t i = 0; i<N-1; ++i)
    {
        auto it_wj = it_wi+1;        
        for(size_t j = i+1; j<N; ++j)
        {
            *it_x += (b-c) * (*it_wi + *it_wj);
            if (*it_x >= t)
                edges.push_back(make_pair(i,j));

            ++it_x;
            ++it_wj;
        }
        ++it_wi;
    }
    return edges;
}

vector < pair < size_t, size_t > > get_fast_edge_list( size_t N, 
                                                  double rho, 
                                                  double t,
                                                  double seed
                                                )
{

    //cout << "Greetings! You called the pointer method!" << endl;

    assert(N>=3);
    assert(rho >= 0.0 && rho < 0.5);
    size_t m = N * (N - 1) / 2;

    double sqrt_rho = sqrt(rho);
    double sqrt_1_m_2rho = sqrt(1.0-2.0*rho);

    mt19937_64 generator;
    if (seed == 0)
        randomly_seed_engine(generator);
    else
        generator.seed(0);

    normal_distribution<double> randn(0.0,1.0);

    vector < double > Z;

    for(size_t n = 0; n<N; ++n)
    {
        double z = randn(generator);
        Z.push_back(z);
    }

    vector < pair < size_t, size_t > > edges;

    auto zi = Z.begin();

    for(size_t i = 0; i < N-1; ++i)
    {
        auto zj = zi+1;
        for(size_t j = i+1; j < N; ++j)
        {
            double y = randn(generator);
            if (y > (t - sqrt_rho*((*zi)+(*zj))) / sqrt_1_m_2rho)
                edges.push_back(make_pair(i, j));

            ++zj;
        }
        ++zi;
    }

    return edges;
}
