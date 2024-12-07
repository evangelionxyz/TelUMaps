// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#pragma once
#include <string>

namespace telu {

struct Edge {
    int weight;
    Edge *next;

    Edge();
};

struct Node {
    Node *next;
    Edge *first_edge;
    std::string name;

    Node();
    Node(const std::string &name);
};

struct Graph
{
    Node *first;

    Graph();
    ~Graph();

    Node *insert_node(const std::string &name);
    Node *find_node(const std::string &name);
    
    bool is_empty() const;

    void print();
};

}