/* 
 * The MIT License (MIT)
 * Copyright (c) 2016, Benjamin Maier
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

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <set>
#include <utility>
#include <random>
#include <cmath>
#include <numeric>
#include <random>
#include <ctime>
#include <tuple>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Utilities.h"
#include "thredge_corr.h"
//#include "ResultClasses.h"
//#include "test.h"

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(cThredgeCorr, m) {
    m.doc() = "For fast generation of edge lists from the thresholded correlated edge weight model.";
    
    m.def("get_edge_list", &get_edge_list, R"pbdoc(Get an edge list for the thresholded correlated edge weight model. RNG is non-deterministically initialized if seed = 0.)pbdoc",
            py::arg("N"),
            py::arg("covariance"),
            py::arg("threshold"),
            py::arg("parameters"),
            py::arg("seed") = 0
            );

    m.def("get_fast_edge_list", &get_fast_edge_list, R"pbdoc(Get an edge list for the thresholded correlated edge weight model. RNG is non-deterministically initialized if seed = 0.)pbdoc",
            py::arg("N"),
            py::arg("covariance"),
            py::arg("threshold"),
            py::arg("parameters"),
            py::arg("seed") = 0
            );
}
