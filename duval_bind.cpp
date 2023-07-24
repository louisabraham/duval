#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "duval.hpp"

namespace py = pybind11;

PYBIND11_MODULE(duval, m)
{
    m.def("duval", &duval, "A function that calculates Lyndon factorization");
    m.def("min_rotation", &min_rotation, "A function that calculates the smallest rotation of a string");
}
