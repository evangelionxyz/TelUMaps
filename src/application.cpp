// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "application.hpp"
#include <iostream>
#include <stdio.h>
#include <conio.h>

#include <thread>

Application::Application()
{
    printf("Welcome to Tel-U Maps program\n");

    printf(">> Intializing map routes...\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    // shortest 2
    // longest 24
    map.setup_route("Gd. Cacuk 1", "Gd. Cacuk 2", 2);
    map.setup_route("Gd. Cacuk 1", "TULT", 19);
    map.setup_route("Gd. Cacuk 2", "TULT", 21);
    map.setup_route("Gd. E", "TULT", 24);
    map.setup_route("Gd. KU3", "TULT", 16);
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
        {
            pause();
            system("cls");
        }
    }

    printf("Thank you!!");
}
