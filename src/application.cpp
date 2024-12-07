// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "application.hpp"
#include <iostream>
#include <stdio.h>

Application::Application()
{
    build();
}

void Application::build()
{
    map.insert_node("Gedung Serba Guna");
    map.insert_node("TULT");
}

void Application::print_menu(int *selected)
{
    *selected = -1;
    while (*selected < 1 || *selected > 3)
    {
        printf("1. Search\n");
        printf("2. Show All\n");
        printf("3. Exit\n");
        printf("Please choose a menu: ");
        scanf("%d", selected);
        if (*selected < 1 || *selected > 3)
            printf("Please enter 1 to 3\n");
    }
}

void Application::run()
{
    int option = -1;
    std::cout << "I am running\n";

    while (option != 3)
    {
        print_menu(&option);
        switch (option)
        {
            case 1:
            {
                printf("I am hereeee\n");
                break;
            }
            case 2:
            {
                map.print();
                break;
            }
        }
    }

    printf("Thank you!!");
}
