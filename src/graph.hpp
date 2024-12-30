// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#pragma once
#include <vector>
#include <set>
#include <unordered_set>
#include <string>

namespace telu {

// forward declaration
struct Node;
struct Graph;

struct Edge {
    int weight;
    Edge *next;
    std::string target_node;

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
    void remove_edge(const std::string &to);
    void print();
};

struct NodeDistance
{
    Node *node;
    int distance;
    bool visited;
    std::string previous_node;
};

struct Graph
{
    Node *first;
    
    Graph(); // create
    ~Graph(); // destroy

    Node *insert_node(Node *new_node);
    Node *insert_node(const std::string &name);
    bool remove_node(const std::string &name);
    Node *find_node(const std::string &name);
    Edge *find_edge(Node *node, const std::string &to);
    void setup_route(const std::string &from, const std::string &to, int weight);
    void remove_route(const std::string &from, const std::string &to);
    void find_shortest_path(const std::string &start, const std::string &end);
    bool is_empty();
    void print();
};

}