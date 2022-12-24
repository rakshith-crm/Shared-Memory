#include "include/SharedMemory.hpp"

PYBIND11_MODULE(shared, m)
{
    m.doc() = "Shared memory module";
    py::class_<SharedMemory<double>>(m, "List")
        .def(py::init<const char *>())
        .def("read", &SharedMemory<double>::readNumpy)
        .def("append", &SharedMemory<double>::append)
        .def("shape", &SharedMemory<double>::getShape);
}