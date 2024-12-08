// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "application.hpp"
#include <iostream>
#include <stdio.h>
#include <conio.h>

Application::Application()
{
    map.setup_route("Building A", "Building B", 4);
    map.setup_route("Building A", "Building C", 2);
    map.setup_route("Building B", "Building C", 1);
    map.setup_route("Building B", "Building D", 5);
    map.setup_route("Building C", "Building D", 8);
}

void Application::print_menu(int *selected)
{
    *selected = -1;
    while (*selected < 1 || *selected > 3)
    {
        system("cls");

        printf("1. Search\n");
        printf("2. Show All\n");
        printf("3. Exit\n");
        printf("Please choose a menu: ");
        scanf("%d", selected);
        if (*selected < 1 || *selected > 3)
        {
            printf("Please enter 1 to 3\n");
        }
    }
}

void Application::pause()
{
    printf("Press any key to continue\n");
    char input = _getch();
}

void Application::run()
{
    int option = -1;
    const int EXIT = 3;
    while (option != EXIT)
    {
        print_menu(&option);
        switch (option)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                map.print();
                break;
            }
        }

        if (option != EXIT)
            pause();
    }

    printf("Thank you!!");
}
