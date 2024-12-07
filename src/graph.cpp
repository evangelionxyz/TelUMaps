// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"
#include <iostream>

namespace telu {

Edge::Edge() : weight(0), next(nullptr) {}
Edge::Edge(int weight): weight(weight), next(nullptr) {}

void Edge::print()
{
}

Node::Node(): next(nullptr), first_edge(nullptr) {}


Node::Node(const std::string &name): name(name), next(nullptr), first_edge(nullptr){}

Edge *Node::add_edge(Graph *graph, const std::string &to, int weight)
{
    Node *target_node = graph->find_node(to);
    if (!target_node)
    {
        std::cout << "Could not find target node: " << to << '\n';
        return nullptr;
    }

    Edge *new_edge = new Edge(weight);
    new_edge->target_node = target_node->name;
    
    if (!first_edge)
    {
        first_edge = new_edge;
        return new_edge;
    }

    Edge *current = first_edge;
    while (current && current->next)
        current = current->next;
    current->next = new_edge;
    return new_edge;
}

void Node::print()
{
    std::cout << "Node: " << name << '\n';
}


#pragma region GRAPH

Graph::Graph()
    : first(nullptr)
{
}

Graph::~Graph()
{
}

// insert last
Node* Graph::insert_node(Node *new_node)
{
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
    return nullptr;
}

bool Graph::is_empty()
{
    return first == nullptr;
}

void Graph::print()
{
     Node *current = first;
    while (current)
    {
        current->print();
        current = current->next;
    }
}

}