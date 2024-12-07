// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "graph.hpp"

struct Application
{
    Application();

    void run();

private:
    void build();
    void print_menu(int *selected);
    telu::Graph map;
};
