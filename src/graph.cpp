// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"

namespace telu {

Edge::Edge(): weight(0), next(nullptr)
{
}

Node::Node(): next(nullptr), first_edge(nullptr)
{
}

Node::Node(Node *next): next(next), first_edge(nullptr)
{
}

Graph::Graph(): first(nullptr)
{
}

Graph::~Graph()
{
}

void Graph::print()
{
    // todo printing
}

}