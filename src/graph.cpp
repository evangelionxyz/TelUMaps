// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"
#include <iostream>
#include <queue>
#include <unordered_map>

const int MAX_ITERATE = 50;

namespace telu {

Edge::Edge()
    : weight(0), next(nullptr)
{
}

Edge::Edge(int weight)
    : weight(weight), next(nullptr)
{
}

void Edge::print()
{
    printf("-> %s - %d\n", target_node.c_str(), weight);
}

Node::Node()
    : next(nullptr), first_edge(nullptr)
{
}

Node::Node(const std::string &name)
    : name(name), next(nullptr), first_edge(nullptr)
{
}

Edge *Node::add_edge(Graph *graph, const std::string &to, int weight)
{
    Node *target_node = graph->find_node(to);
    if (!target_node)
    {
        printf("Could not find target node: %s\n", to.c_str());
        return nullptr;
    }

    Edge *new_edge = new Edge(weight);
    new_edge->target_node = target_node->name;
    if (!first_edge)
    {
        first_edge = new_edge;
        return new_edge;
    }

    Edge *edge = first_edge;
    while (edge && edge->next)
        edge = edge->next;

    edge->next = new_edge;
    return new_edge;
}

void Node::remove_edge(const std::string &to)
{
    if (!first_edge)
        return;

    if (first_edge->target_node == to)
    {
        Edge *delete_target = first_edge;
        first_edge = first_edge->next;
        delete delete_target;
        return;
    }

    Edge *edge = first_edge;
    while (edge->next)
    {
        if (edge->next->target_node == to)
        {
            Edge *delete_edge = edge->next;
            edge->next = edge->next->next;
            delete delete_edge;
            return;
        }
        edge = edge->next;
    }
}

void Node::print()
{
    std::cout << "Node: " << name << '\n';
}

/// -----------------
/// ----------- GRAPH
/// -----------------

#pragma region GRAPH

Graph::Graph()
    : first(nullptr)
{
}

Graph::~Graph() // destructor
{
    Node *node = first;
    while (node)
    {
        Edge *edge = node->first_edge;
        while (edge)
        {
            Edge *delete_edge = edge;
            edge = edge->next;

            delete delete_edge;
        }

        Node *delete_node = node;
        node = node->next;

        delete delete_node;
    }
}

// insert last
Node *Graph::insert_node(Node *new_node)
{
    if (!first)
    {
        first = new_node;
        return new_node;
    }

    Node *node = first;
    while (node && node->next)
        node = node->next;

    node->next = new_node;
    return new_node;
}

// insert last
Node *Graph::insert_node(const std::string &name)
{
    Node *new_node = new Node(name);
    return insert_node(new_node);
}

bool Graph::remove_node(const std::string &name)
{
    if (!first)
        return false;


    bool removed = false;
    if (first->name == name)
    {
        Node *delete_node = first;
        first = first->next;
        delete delete_node;
        removed = true;
    }

    Node *current = first;
    while (current->next && !removed)
    {
        if (current->next->name == name)
        {
            Node *delete_node = current->next;
            current->next = current->next->next;
            delete delete_node;
            removed = true;
            break;
        }
        current = current->next;
    }

    current = first;
    // remove connected node
    while (current && removed)
    {
        current->remove_edge(name);
        current = current->next;
    }

    return removed;
}

Node *Graph::find_node(const std::string &name)
{
    Node *node = first;
    while (node)
    {
        if (node->name == name)  return node;
        node = node->next;
    }
    return nullptr;
}

Edge *Graph::find_edge(Node *node, const std::string &to)
{
    for (Edge *edge = node->first_edge; edge != nullptr; edge = edge->next)
    {
        if (edge->target_node == to) return edge;
    }
    return nullptr;
}

void Graph::setup_route(const std::string &from, const std::string &to, int weight)
{
    // find or create node
    Node *from_node = find_node(from);
    Node *to_node = find_node(to);
    if (!from_node)
    {
        printf("Failed to setup route: Node %s not found\n", from.c_str());
        printf("Please add the node first\n");
        return;
    }

    if (!to_node)
    {
        printf("Failed to setup route: Node %s not found\n", to.c_str());
        printf("Please add the node first\n");
        return;
    }

    Edge *existing_edge = find_edge(from_node, to);
    if (existing_edge)
    {
        // update the weight if the new weight is smaller
        if (weight < existing_edge->weight)
            existing_edge->weight = weight;
        return; // no need to proceed further
    }

    // add edge for both nodes
    from_node->add_edge(this, to, weight);
    to_node->add_edge(this, from, weight);
}

// DIJKSTRA ALGORITHM
void Graph::find_shortest_path(const std::string &start, const std::string &end)
{
    std::unordered_map<std::string, NodeDistance> distances;

    for (Node *node = first; node != nullptr; node = node->next)
    {
        distances[node->name] = { node, std::numeric_limits<int>::max(), false, "" };
    }

    // comparison function from longest to shortest distance
    auto compare = [](const std::pair<int, std::string> &a, const std::pair<int, std::string> &b)
    {
        return a.first > b.first;
    };

    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, decltype(compare)> pq(compare);

    if (distances.find(start) == distances.end())
    {
        printf("Start node not found: %s\n", start.c_str());
        return;
    }

    // push distances to queue
    distances[start].distance = 0;
    pq.push({ 0, start });

    // processing total distance
    while (!pq.empty())
    {
        auto [current_distance, current_name] = pq.top();
        pq.pop();

        NodeDistance &current = distances[current_name];
        if (current.visited)
            continue;

        current.visited = true;
        for (Edge *edge = current.node->first_edge; edge != nullptr; edge = edge->next)
        {
            NodeDistance &neighbor = distances[edge->target_node];

            int new_distance = current_distance + edge->weight;
            if (new_distance < neighbor.distance)
            {
                neighbor.distance = new_distance;
                neighbor.previous_node = current_name;
                pq.push({ new_distance, edge->target_node });
            }
        }   
    }

    if (distances[end].distance == std::numeric_limits<int>::max())
    {
        printf("No path from %s to %s\n", start.c_str(), end.c_str());
        return;
    }

    std::vector<std::string> path;
    std::string current = end;

    // inserting previous path for printing
    while (!current.empty())
    {
        path.push_back(current);
        current = distances[current].previous_node;
    }

    std::reverse(path.begin(), path.end());

    printf("Shortest path: ");
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i > 0)
            printf(" -> ");
        printf("%s", path[i].c_str());
    }
    printf(": %d\n", distances[end].distance);
}

void Graph::remove_route(const std::string &from, const std::string &to)
{
    Node *from_node = find_node(from);
    Node *to_node = find_node(to);

    if (from_node && to_node)
    {
        from_node->remove_edge(to);
        to_node->remove_edge(from);
    }
}

bool Graph::is_empty()
{
    return first == nullptr;
}

void Graph::print()
{
    for (Node *node = first; node != nullptr; node = node->next)
    {
        node->print();
        for (Edge *edge = node->first_edge; edge != nullptr; edge = edge->next)
        {
            printf("   ");
            edge->print();
        }
    }
}
#pragma endregion // !GRAPH

}