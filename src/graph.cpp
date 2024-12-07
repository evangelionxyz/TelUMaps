// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"
#include <iostream>

namespace telu {

Edge::Edge(): weight(0), next(nullptr)
{
}

Node::Node(): next(nullptr), first_edge(nullptr)
{
}

Node::Node(const std::string &name)
    : next(nullptr), first_edge(nullptr), name(name)
{
}

#define CHECK_GRAPH_IS_NOT_EMPTY() if (Graph::is_empty())\
                                       std::cout << "[WARNING] Graph is empty!!\n"

Graph::Graph(): first(nullptr)
{
}

Graph::~Graph()
{
}

// insert last
Node *Graph::insert_node(const std::string &name)
{
    Node *new_node = new Node(name);
    if (!first)
    {
        first = new_node;
        return new_node;
    }

    Node *current = first;
    while (current && current->next)
        current = current->next;
    current->next = new_node;
    return new_node;
}

Node *Graph::find_node(const std::string &name)
{
    CHECK_GRAPH_IS_NOT_EMPTY();

    Node *current = first;
    while (current) {
        if (current->name == name)
            return current;
        current = current->next;
    }
    return nullptr;
}

bool Graph::is_empty() const
{
    return first == nullptr;
}

void Graph::print()
{
    CHECK_GRAPH_IS_NOT_EMPTY();

    Node *current = first;
    while (current) {
        std::cout << "Vertex: " << current->name << '\n';
        current = current->next;
    }
}

}