// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"

struct Application
{
    Application();

    void run();

private:
    void print_routes();
    void print_menu(int *selected);
    
    static void pause();
    telu::Graph map;
};
