// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"
#include <iostream>

int main(int argc, char **argv) {
    telu::Graph telu_map;
    
    telu_map.insert_node("Gedung Serba Guna");
    telu_map.insert_node("TULT");

    telu_map.print();


    return 0;
}