cmake_minimum_required(VERSION 3.4)
project(example LANGUAGES CXX)

find_package(pybind11 REQUIRED)  # or add_subdirectory(pybind11)

add_library(shared MODULE shared.cpp)

target_link_libraries(shared PRIVATE pybind11::module pybind11::lto pybind11::windows_extras)

pybind11_extension(shared)
if(NOT MSVC AND NOT ${CMAKE_BUILD_TYPE} MATCHES Debug|RelWithDebInfo)
    # Strip unnecessary sections of the binary on Linux/macOS
    pybind11_strip(shared)
endif()


string(
    APPEND _opts
    "$<IF:$<CXX_COMPILER_ID:MSVC>,"
        "/W4;$<$<CONFIG:RELEASE>:/O2>,"
        "-Wall;-Wextra;-Werror;"
            "$<$<CONFIG:RELEASE>:-O3>"
            "$<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>"
    ">"
)

add_compile_options("${_opts}")                                        
target_compile_features(shared PUBLIC cxx_lambda_init_captures)


set_target_properties(shared PROPERTIES CXX_VISIBILITY_PRESET "hidden"
                                         CUDA_VISIBILITY_PRESET "hidden")



                                         
