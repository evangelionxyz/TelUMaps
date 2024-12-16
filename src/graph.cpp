// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
        std::string previous_node;
    };

    printf("Finding path from %s to %s\n", start.c_str(), end.c_str());
    
    // initialize all of the nodes
    NodeDistance nodes[100];
    int node_count = 0;
    bool start_found = false;
    bool end_found = false;

    // first pass: check if start and end nodes exist
    Node *check_node = first;
    while (check_node)
    {
        printf("Graph node found: %s\n", check_node->name.c_str());
        if (check_node->name == start) start_found = true;
        if (check_node->name == end) end_found = true;
        check_node = check_node->next;
    }

    if (!start_found) 
    {
        printf("Start node %s not found in graph\n", start.c_str());
        return;
    }

    if (!end_found) 
    {
        printf("End node %s not found in graph\n", end.c_str());
        return;
    }

    // store the distance to each nodes
    // make distance to 0 if it was a 'start' node
    // otherwise make it the max value
    Node *current = first;
    while (current && node_count < 100)
    {
        nodes[node_count].node = current;
        nodes[node_count].distance = (current->name == start) ? 0 : INT_MAX;
        nodes[node_count].visited = false;
        nodes[node_count].previous_node = "";
        current = current->next;
        node_count++;
    }

    printf("Initialized %d nodes\n", node_count);

    while (true)
    {
        // find the closest unvisited node
        NodeDistance *closest = nullptr;
        for (int i = 0; i < node_count; ++i)
        {
            if (!nodes[i].visited && (!closest || nodes[i].distance < closest->distance))
                closest = &nodes[i];
        }

        // if not found, break the loop
        if (!closest || closest->distance == INT_MAX)
        {
            printf("No more nodes to process\n");
            break;
        }
        // else, then mark the closest as visited
        closest->visited = true;

        printf("---------------------------\n");
        printf("Processing node: %s (distance: %d)\n", closest->node->name.c_str(), closest->distance);

        // process edges
        Edge *edge = closest->node->first_edge;
        int edge_count = 0;
        while (edge)
        {
            printf("  Examining edge to %s (weight: %d)\n", edge->target_node.c_str(), edge->weight);
            
            for (int i = 0; i < node_count; ++i)
            {
                if (nodes[i].node->name == edge->target_node)
                {
                    int new_distance = closest->distance + edge->weight;
                    printf("    Potential new distance to %s: %d (current: %d)\n", 
                           nodes[i].node->name.c_str(), new_distance, nodes[i].distance);
                    
                    if (new_distance < nodes[i].distance) 
                    {
                        nodes[i].distance = new_distance;
                        nodes[i].previous_node = closest->node->name;
                        printf("    Updated distance to %s\n", nodes[i].node->name.c_str());
                    }
                    break;
                }
            }
            edge = edge->next;
            edge_count++;
        }
        printf("Processed %d edges from node %s\n", edge_count, closest->node->name.c_str());
    }
    printf("---------------------------\n");

    // find the end node and print path
    for (int i = 0; i < node_count; ++i)
    {
        if (nodes[i].node->name == end)
        {
            if (nodes[i].distance == INT_MAX)
                printf("No path from %s to %s\n", start.c_str(), end.c_str());
            else
            {
                printf("Shortest path from %s to %s is %d\n", start.c_str(), end.c_str(), nodes[i].distance);
                
                // Reconstruct path
                std::vector<std::string> path;
                std::string current = end;
                while (!current.empty())
                {
                    path.push_back(current);
                    
                    // Find previous node
                    bool found = false;
                    for (int j = 0; j < node_count; ++j)
                    {
                        if (nodes[j].node->name == current)
                        {
                            current = nodes[j].previous_node;
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) break;
                    if (current == start) 
                    {
                        path.push_back(current);
                        break;
                    }
                }
                
                // Print path
                printf("Path: ");
                for (int j = path.size() - 1; j >= 0; --j)
                {
                    printf("%s", path[j].c_str());
                    if (j > 0) printf(" -> ");
                }
                printf("\n");
            }
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