#include "graph.hpp"

#include <pybind11/gil.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(graph, m) {
    py::class_<Edge>(m, "Edge")
        //        .def(py::init<Node *, Node *, int64_t>());
        .def("to", &Edge::to);
    py::class_<Node>(m, "Node")
        //        .def(py::init<const std::string>())
        .def("Compute", [](Node &node, const std::function<std::string(const std::string &, const std::string &)> func, const std::string &constant) {
            return node.Compute(func, constant);
        })
        .def("s", &Node::s)
        .def("out_edges", &Node::out_edges);
    py::class_<Graph>(m, "Graph")
        .def(py::init<>())
        .def("AddNode", &Graph::AddNode)
        .def("AddEdge", &Graph::AddEdge);
}
