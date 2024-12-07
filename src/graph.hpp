// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#pragma once
#include <string>

namespace telu {

// forward declaration
struct Node;
struct Graph;

struct Edge {
    int weight;
    std::string target_node;
    Edge *next;
    
    Edge();
    Edge(int weight);

    void print();
};

struct Node {
    Node *next;
    Edge *first_edge;
    std::string name;

    Node();
    Node(const std::string &name);

    Edge *add_edge(Graph *graph, const std::string &to, int weight);
    void print();
};

struct Graph
{
    Node *first;
    
    Graph();
    ~Graph();

    Node *insert_node(Node *new_node);
    Node *insert_node(const std::string &name);
    Node *find_node(const std::string &name);

    bool is_empty();

    void print();
};

}