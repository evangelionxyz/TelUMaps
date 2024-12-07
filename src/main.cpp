// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include <iostream>
#include "graph.hpp"

int main(int argc, char **argv) {
    
    telu::Graph myGraph;
    myGraph.insert_node("Gedung Cacuk");
    myGraph.insert_node("Gedung Serba Guna");
    myGraph.insert_node("Telkom University Landmark Tower");

    myGraph.print();

    return 0;
}