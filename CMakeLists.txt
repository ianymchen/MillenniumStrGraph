cmake_minimum_required(VERSION 3.17)

# g++ -O3 -Wall -shared -std=c++20 -fPIC `python3 -m pybind11 --includes` graph.cpp -o graph`python3-config --extension-suffix`

project(StrGraphCpp)

find_package(pybind11 REQUIRED)

set(SOURCES
    graph.cpp
)

pybind11_add_module(graph MODULE ${SOURCES})

target_link_libraries(graph PRIVATE pybind11::module)

set_target_properties(graph PROPERTIES OUTPUT_NAME "graph")

execute_process(
    COMMAND python3-config --extension-suffix
    OUTPUT_VARIABLE PYTHON_EXTENSION_SUFFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)
add_custom_command(TARGET graph POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:graph> ${LIBRARY_OUTPUT_PATH}/graph${PYTHON_EXTENSION_SUFFIX}
)
