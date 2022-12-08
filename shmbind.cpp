#include "include/SharedMemory.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

namespace py = pybind11;

PYBIND11_MODULE(shmbind, m)
{
    m.doc() = "Shared memory module";
    py::class_<SharedMemory<float>>(m, "SharedList")
        .def(py::init<const char *>())
        .def("read", &SharedMemory<float>::read)
        .def("write", &SharedMemory<float>::write)
        .def("append", &SharedMemory<float>::append)
        .def("shape", &SharedMemory<float>::getShape);

    // py::class_<SharedMemory<int>>(m, "SharedList")
    //     .def(py::init<const char *>())
    //     .def("read", &SharedMemory<int>::read)
    //     .def("write", &SharedMemory<int>::write)
    //     .def("append", &SharedMemory<int>::append)
    //     .def("shape", &SharedMemory<int>::getShape);
}