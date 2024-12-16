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

    // shortest 2, longest 24
    map.setup_route("Cacuk 1", "Cacuk 2", 2);
    map.setup_route("Cacuk 1", "TULT", 19);
    map.setup_route("Cacuk 2", "TULT", 21);
    map.setup_route("E", "TULT", 24);
    map.setup_route("KU3", "TULT", 16);
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
        std::cin >> *selected;
        
        // clear newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (*selected < 1 || *selected > 3)
        {
            printf("Please enter 1 to 3\n");
        }
    }
}

void Application::pause()
{
    printf("Press any key to continue...");
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
                print_routes();

                std::string start, end;

                printf("Enter start route: ");
                std::getline(std::cin, start);
                printf("Enter end route: ");
                std::getline(std::cin, end);

                map.find_shortest_path(start, end);

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

void Application::print_routes()
{
    printf("---- Routes ----\n");
    telu::Node *current = map.first;
    while (current)
    {
        current->print();
        current = current->next;
    }
    printf("-----------------\n");
}
