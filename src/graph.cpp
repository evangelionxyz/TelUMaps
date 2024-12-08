// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"
#include <iostream>

namespace telu {

Edge::Edge() : weight(0), next(nullptr) {}
Edge::Edge(int weight): weight(weight), next(nullptr) {}

void Edge::print()
{
    printf("-> %s - weights %d\n", target_node.c_str(), weight);
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
    Node *current = first;
    while (current) {
        Node *to_delete = current;
        current = current->next;

        // delete edges
        Edge *edge = to_delete->first_edge;
        while (edge) {
            Edge *edge_to_delete = edge;
            edge = edge->next;
            delete edge_to_delete;
        }

        delete to_delete;
    }
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
    return insert_node(new_node);
}

Node *Graph::find_node(const std::string &name)
{
    Node *current = first;
    while (current)
    {
        if (current->name == name)  return current;
        current = current->next;
    }
    return nullptr;
}

void Graph::setup_route(const std::string &from, const std::string &to, int weight)
{
    Node *from_node = find_node(from);
    if (!from_node) from_node = insert_node(from);

    Node *to_node = find_node(to);
    if (!to_node) to_node = insert_node(to);

    // add edge for both nodes
    from_node->add_edge(this, to, weight);
    to_node->add_edge(this, from, weight);
}

void Graph::find_shortest_path(const std::string &start, const std::string &end)
{
    if (this->is_empty())
    {
        printf("Graph is empty.\n");
        return;
    }

    struct NodeDistance
    {
        Node *node;
        int distance;
        bool visited;
    };

    // initialize all of the nodes
    NodeDistance nodes[100];
    int node_count = 0;

    Node *current = first;
    while (current && node_count < 100)
    {
        nodes[node_count].node = current;
        nodes[node_count].distance = (current->name == start) ? 0 : INT_MAX;
        nodes[node_count].visited = false;
        current = current->next;
        node_count++;
    }

    while (true)
    {
        NodeDistance *closest = nullptr;
        for (int i = 0; i < node_count; ++i)
        {
            if (!nodes[i].visited && (!closest || nodes[i].distance < closest->distance))
            {
                closest = &nodes[i];
            }
        }

        if (!closest || closest->distance == INT_MAX) break;

        closest->visited = true;
        Edge *edge = closest->node->first_edge;
        while (edge)
        {
            for (int i = 0; i < node_count; ++i)
            {
                if (nodes[i].node->name == edge->target_node)
                {
                    int new_distance = closest->distance + edge->weight;
                    if (new_distance < nodes[i].distance) 
                        nodes[i].distance = new_distance;
                    break;
                }
            }
            edge = edge->next;
        }
    }

    for (int i = 0; i < node_count; ++i)
    {
        if (nodes[i].node->name == end)
        {
            if (nodes[i].distance == INT_MAX) printf("No path from %s to %s\n", start.c_str(), end.c_str());
            else printf("Shortest path from %s to %s is %d\n", start.c_str(), end.c_str(), nodes[i].distance);
            return;
        }
    }

    printf("Node %s not found in graph\n", end.c_str());
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
        Edge *edge = current->first_edge;
        while (edge)
        {
            printf("   ");
            edge->print();
            edge = edge->next;
        }
        current = current->next;
    }
}

#pragma endregion // !GRAPH

}