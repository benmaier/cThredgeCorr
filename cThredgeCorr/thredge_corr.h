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

#ifndef __TC_H__
#define __TC_H__

#include "Utilities.h"
#include "thredge_corr.h"
#include <assert.h>

using namespace std;

size_t edge_index(size_t const &N,
                  size_t const &i,
                  size_t const &j
                  );

vector < pair < size_t, size_t > > get_slow_edge_list( size_t N, 
                                                  double rho, 
                                                  double t,
                                                  vector < double > parameters,
                                                  double seed
                                                );

vector < pair < size_t, size_t > > get_edge_list( 
                                                  size_t N, 
                                                  double rho, 
                                                  double t,
                                                  vector < double > parameters,
                                                  double seed
                                                );

vector < pair < size_t, size_t > > get_fast_edge_list( size_t N, 
                                                  double rho, 
                                                  double t,
                                                  double seed
                                                );
#endif
