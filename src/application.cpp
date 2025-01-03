// Copyright (c) 2024 Evangelion Manuhutu | Nur Ilmi Mufidah

#include "application.hpp"
#include <iostream>
#include <stdio.h>
#include <conio.h>

#include <thread>

const int EXIT = 7;

Application::Application()
{
    printf(">> Intializing map routes...\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    // shortest 2, longest 24
    map.insert_node("CACUK 1");
    map.insert_node("CACUK 2");
    map.insert_node("TULT");
    map.insert_node("E");
    map.insert_node("GKU");
    map.insert_node("BANGKIT");

    map.setup_route("CACUK 1", "CACUK 2", 2);
    map.setup_route("CACUK 1", "GKU", 15);
    map.setup_route("CACUK 1", "TULT", 21);
    map.setup_route("CACUK 1", "BANGKIT", 3);

    map.setup_route("CACUK 2", "BANGKIT", 5);
    map.setup_route("CACUK 2", "E", 10);
    map.setup_route("CACUK 2", "GKU", 14);
    map.setup_route("CACUK 2", "TULT", 19);

    map.setup_route("E", "BANGKIT", 13);
    map.setup_route("E", "CACUK 1", 8);
    map.setup_route("E", "GKU", 19);
    map.setup_route("E", "TULT", 24);

    map.setup_route("BANGKIT", "GKU", 6);
    map.setup_route("BANGKIT", "TULT", 22);

    map.setup_route("GKU", "TULT", 16);
}

void Application::print_menu(int *selected)
{
    *selected = -1;
    while (*selected < 1 || *selected > EXIT)
    {
        printf("1. Search Shortest Route\n");
        printf("2. Print graph\n");
        printf("3. Create new node\n");
        printf("4. Remove a node\n");
        printf("5. Create new route\n");
        printf("6. Remove a route\n");
        printf("7. Exit\n");
        printf("Please choose a menu: ");
        std::cin >> *selected;
        
        // clear newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (*selected < 1 || *selected > EXIT)
        {
            printf("Please enter 1 to %d\n", EXIT);
        }
    }
}
 
void Application::to_upper(std::string &str)
{
    for (int i = 0; i < str.size(); ++i)
    {
        str[i] -= 32 * (str[i] <= 'z' && str[i] >= 'a');
    }
}

void Application::pause()
{
    printf("Press any key to continue...");
    char input = _getch(); // get character
}

void Application::run()
{
    int option = -1;

    while (option != EXIT)
    {
        printf("Welcome to Tel-U Maps program\n");
        print_menu(&option);

        switch (option)
        {
            case 1:
            {
                printf("--- Search Shortest Route ---\n");
                print_routes();
                std::string start, end;
                printf("Enter start route: ");
                std::getline(std::cin, start);
                printf("Enter end route: ");
                std::getline(std::cin, end);
                to_upper(start);
                to_upper(end);
                map.find_shortest_path(start, end);
                break;
            }
            case 2: // printing
            {
                map.print();
                break;
            }
            case 3:
            {
                // create node if not found
                printf("--- Add New Node ---\n");
                std::string node_name;
                printf("Enter node name: ");
                std::getline(std::cin, node_name);
                to_upper(node_name);

                telu::Node *found_node = map.find_node(node_name);
                if (found_node)
                {
                    printf("Node with name %s already exists\n", node_name.c_str());
                }
                else
                {
                    map.insert_node(node_name);
                    printf("Node %s inserted successful\n", node_name.c_str());
                }
                break;
            }
            case 4: 
            {
                printf("--- Remove A Node ---\n");
                std::string node_name;
                printf("Enter node name: ");
                std::getline(std::cin, node_name);
                to_upper(node_name);

                if (map.remove_node(node_name))
                {
                    printf("Node %s has been removed successfully\n", node_name.c_str());
                }
                else
                {
                    printf("Failed to remove node %s\n", node_name.c_str());
                }

                break;
            }
            case 5:
            {
                printf("--- Add New Route ---\n");
                // shortest 2, longest 24

                int weight = 0;
                while (weight < 2 || weight >  24)
                {
                    std::string start, end;
                    printf("Enter start route: ");
                    std::getline(std::cin, start);
                    printf("Enter end route: ");
                    std::getline(std::cin, end);
                    printf("Enter weight 2 - 24: ");
                    to_upper(start);
                    to_upper(end);
                    std::cin >> weight;

                    if (weight < 2 || weight > 24)
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        printf("Please try again\n");
                        printf("Enter weight with range between 2 - 24\n");
                        pause();
                        system("cls");
                    }
                    else
                    {
                        map.setup_route(start, end, weight);
                        printf("Added new route from %s to %s weight %d successful\n", start.c_str(), end.c_str(), weight);
                    }
                }
                
                break;
            }
            case 6:
            {
                printf("--- Remove Route ---\n");
                std::string start, end;
                printf("Enter start route: ");
                std::getline(std::cin, start);
                printf("Enter end route: ");
                std::getline(std::cin, end);

                to_upper(start);
                to_upper(end);

                map.remove_route(start, end);
                printf("Route %s to %s has been deleted\n", start.c_str(), end.c_str());
                break;
            }
        }

        if (option != EXIT)
        {
            pause();
            system("cls");
        }
    }

    system("cls");
    printf("Thank you!!\n");
    pause();
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
