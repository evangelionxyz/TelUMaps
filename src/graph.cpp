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

    Edge *current = first_edge;
    while (current && current->next)
        current = current->next;
    current->next = new_edge;
    return new_edge;
}

void Node::remove_edge(const std::string &to)
{
    Edge *edge = first_edge;
    Edge *prev = nullptr;
    while (edge)
    {
        if (edge->target_node == to)
        {
            Edge *delete_edge = edge;
            if (edge->next && prev)
                prev->next = edge->next;
            if (delete_edge == first_edge)
                first_edge = nullptr;
            delete delete_edge;
            break;
        }
        edge = edge->next;
        prev = edge;
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

Graph::~Graph()
{
    Node *node = first;
    while (node)
    {
        Edge *edge = node->first_edge;
        while (edge)
        {
            Edge *delete_edge = edge;
            edge = edge->next;
            delete edge;
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

    Node *current = first;
    while (current && current->next)
    {
        current = current->next;
    }
    current->next = new_node;
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

    Node *current = first;
    Node *prev = nullptr;

    while (current)
    {
        if (current->name == name)
        {
            Node *delete_node = current;
            if (current->next && prev)
                prev->next = current->next;
            delete delete_node;
            return true;
        }
        current = current->next;
        prev = current;
    }
    return false;
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

Edge *Graph::find_edge(Node *node, const std::string &to)
{
    for (Edge *edge = node->first_edge; edge != nullptr; edge = edge->next)
    {
        if (edge->target_node == to) return edge;
    }
    return nullptr;
}

int Graph::find_route_weight(const std::string &from, const std::string &to)
{
    Node *from_node = find_node(from);
    if (!from_node) return INT_MAX;
    for (Edge *edge = from_node->first_edge; edge != nullptr; edge = edge->next)
    {
        if (edge->target_node == to) return edge->weight;
    }
    return INT_MAX;
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

void Graph::find_shortest_path(const std::string &start, const std::string &end)
{
    std::unordered_map<std::string, NodeDistance> distances;

    for (Node *node = first; node != nullptr; node = node->next)
    {
        distances[node->name] = { node, std::numeric_limits<int>::max(), false, "" };
    }

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

    distances[start].distance = 0;
    pq.push({ 0, start });

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
        Edge *edge = node->first_edge;
        for (Edge *edge = node->first_edge; edge != nullptr; edge = edge->next)
        {
            printf("   ");
            edge->print();
        }
    }
}
#pragma endregion // !GRAPH

}