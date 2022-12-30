#include "include/SharedMemory.hpp"

template <typename T>
void addClassType(py::module &m, std::string dtype)
{
    using Class = SharedMemory<T>;
    
    std::string className = dtype + std::string("List");

    py::class_<Class>(m, className.c_str(), py::buffer_protocol(), py::dynamic_attr())
        .def(py::init<const char *>())
        .def("read", &Class::readNumpy)
        .def("append", &Class::append)
        .def("shape", &Class::getShape)
        .def("close", &Class::close);
}

PYBIND11_MODULE(shared, m)
{
    m.doc() = "pybp module";
    addClassType<long double>(m, "double");
    addClassType<long int>(m, "integer");
    addClassType<char>(m, "char");
    
    
}