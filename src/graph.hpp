// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#pragma once

namespace telu {

struct Edge {
    int weight;
    Edge *next;

    Edge();
};

struct Node {
    Node *next;
    Edge *first_edge;

    Node();
    Node(Node *next);
};

struct Graph
{
    Node *first;
    
    Graph();
    ~Graph();

    void print();
};

}