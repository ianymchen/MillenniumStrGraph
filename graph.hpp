#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using UmapStrStr = std::unordered_map<std::string, std::string>;

class Node;

class Edge {
  public:
    Edge(Node* fr, Node* to, int64_t value)
        : fr_(fr), to_(to), value_(value) {
    }

    Node* fr() const { return fr_; }
    Node* to() const { return to_; }
    int64_t value() const { return value_; }

  private:
    Node* fr_;
    Node* to_;

    int64_t value_;
};

class Node {
  public:
    Node(const std::string& name, const std::string& s)
        : name_(name), s_{s} {}

    template <typename F>
    std::string Compute(F&& f, const std::string& constant) {
        std::string ret = f(s_, constant);
        return ret;
    }

    const std::vector<Edge*>& out_edges() const { return out_edges_; }

    const std::string& s() const { return s_; }

  private:
    std::vector<Edge*> in_edges_;
    std::vector<Edge*> out_edges_;

    std::string name_;
    std::string s_;

    friend class Graph;
};

class Graph {
  public:
    Node* AddNode(const std::string& name, const std::string& s) {
        Node* node = new Node(name, s);
        nodes_[name] = node;
        return node;
    }
    Edge* AddEdge(Node* fr, Node* to, int64_t value) {
        Edge* edge = new Edge(fr, to, value);
        fr->out_edges_.emplace_back(edge);
        to->in_edges_.emplace_back(edge);
        edges_.emplace_back(edge);
        return edge;
    }

  private:
    std::unordered_map<std::string, Node*> nodes_;
    std::vector<Edge*> edges_;
};

