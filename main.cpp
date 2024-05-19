/**
* @file main.cpp
 */

#include <chrono>
#include <iostream>
#include "Handler.h"

using namespace std;

int chooseNumber(Handler handler) {
    int starting_point;
    size_t num_nodes = handler.get_graph().get_nodes_vector().size();
    cout << "Graph has " << num_nodes << " nodes. Choose Starting Point: ";
    while (true) {
        if (cin >> starting_point) {
            if (starting_point >= 0 && static_cast<size_t>(starting_point) < num_nodes) {
                cout << endl;
                break;
            } else {
                cout << "Invalid input. Please enter a number between 0 and " << num_nodes - 1 << ": ";
            }
        } else {
            cout << "Invalid input. Please enter a valid integer: ";
            cin.clear(); // Clear the error flag
        }
    }

    return starting_point;
}

/**
 * @brief Display the main menu and handle user input for graph operations.
 *
 * @param handler The Handler object to manage the graph.
 */

bool mainMenuOn = true;

void mainMenu(Handler handler)
{
    mainMenuOn = true;
    while(mainMenuOn) {
        char option;
        bool isToy = handler.isToy();
        bool isEFC = handler.isEFC();

        cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
        cout << "Choose action:" << endl;
        if (handler.isToy() || handler.isEFC()) {
            cout << "1 - Backtracking Algorithm." << endl;
            cout << "2 - Triangular Approximation Heuristic." << endl;
            cout << "3 - Nearest Neighbours" << endl;
            cout << "4 - Real-world Nearest Neighbours" << endl;
            cout << "5 - Show loaded Graph." << endl;
            cout << "6 - Exit" << endl;
        } else {
            cout << "1 - Triangular Approximation Heuristic." << endl;
            cout << "2 - Nearest Neighbours." << endl;
            cout << "3 - Real-world Nearest Neighbours" << endl;
            cout << "4 - Show loaded Graph." << endl;
            cout << "5 - Exit" << endl;

        }
        cout << "------------------------------------- \n" << endl;

        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case '1':
                if (isToy || isEFC) {
                    handler.get_graph().backtracking_caller();
                } else {
                    auto start = chrono::high_resolution_clock::now();

                    handler.get_graph().computeMST();
                    handler.get_graph().approximateTSP();

                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    cout << "Time taken by TSP: " << duration.count() << " microseconds" << endl;
                }
                break;
            case '2':
                if (isToy || isEFC) {
                    handler.get_graph().computeMST();
                    handler.get_graph().approximateTSP();
                } else {
                    int initial_node = chooseNumber(handler);

                    auto start = chrono::high_resolution_clock::now();

                    handler.get_graph().nearest_neighbour(initial_node);

                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    cout << "Time taken by TSP: " << duration.count() << " microseconds" << endl;
                }
                break;
            case '3':
                if (isToy || isEFC) {
                    int initial_node = chooseNumber(handler);
                    handler.get_graph().nearest_neighbour(initial_node);
                } else {
                    int initial_node = chooseNumber(handler);
                    handler.get_graph().real_world_nearest_neighbours(initial_node);
                }
                break;
            case '4':
                if (isToy || isEFC) {
                    int initial_node = chooseNumber(handler);
                    handler.get_graph().real_world_nearest_neighbours(initial_node);
                } else {
                    handler.print_RealWorld_Graph();
                }
                break;
            case '5':
                if(isToy || isEFC){
                    handler.print_Graph();
                }
                else{
                    cout << "Exiting Main Menu ..." << endl;
                    mainMenuOn = false;
                    break;
                }
            case '6':
                if(isToy || isEFC){
                    cout << "Exiting Main Menu ..." << endl;
                    mainMenuOn = false;
                    break;
                }
                else{
                    cout << "Invalid Choice." << endl;
                    break;
                }
            default:
                cout << "Invalid Choice";
                break;
        }

        /*
        auto start = chrono::high_resolution_clock::now();

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time taken by TSP: " << duration.count() << " microseconds" << endl;
        */
    }
}

/**
 * @brief Display the toy graph selection menu and handle user input.
 *
 * @param handler The Handler object to manage the graph.
 */
void toygraphChoice(Handler handler) {
    string filePath = "../Toy-Graphs/";

    char option;
    cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
    cout << "Choose Toy Graph:" << endl;
    cout << "1 - Shipping Graph." << endl;
    cout << "2 - Stadiums Graph." << endl;
    cout << "3 - Tourism Graph." << endl;
    cout << "------------------------------------- \n" << endl;

    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case '1':
            filePath.append("shipping.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case '2':
            filePath.append("stadiums.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case '3':
            filePath.append("tourism.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        default:
            cout << "Invalid Choice. Please Choose Again.\n";
            break;
    }
}

/**
 * @brief Display the fully connected graph selection menu and handle user input.
 *
 * @param handler The Handler object to manage the graph.
 */
void fullyConnectedChoice(Handler handler) {
    string filePath = "../Extra_Fully_Connected_Graphs/";
    string option;

    cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
    cout << "Choose Fully Connected Graph:" << endl;
    cout << "1 - 25." << endl;
    cout << "2 - 50" << endl;
    cout << "3 - 75." << endl;
    cout << "4 - 100." << endl;
    cout << "5 - 200." << endl;
    cout << "6 - 300." << endl;
    cout << "7 - 400." << endl;
    cout << "8 - 500." << endl;
    cout << "9 - 600." << endl;
    cout << "10 - 700." << endl;
    cout << "11 - 800." << endl;
    cout << "12 - 900." << endl;
    cout << "------------------------------------- \n" << endl;

    cout << "Enter your choice: ";
    cin >> option;

    switch (stoi(option)) {
        case 1:
            filePath.append("edges_25.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 2:
            filePath.append("edges_50.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 3:
            filePath.append("edges_75.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 4:
            filePath.append("edges_100.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 5:
            filePath.append("edges_200.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 6:
            filePath.append("edges_300.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 7:
            filePath.append("edges_400.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 8:
            filePath.append("edges_500.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 9:
            filePath.append("edges_600.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 10:
            filePath.append("edges_700.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 11:
            filePath.append("edges_800.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        case 12:
            filePath.append("edges_900.csv");
            handler.load_toy_efc_Graph(filePath);
            mainMenu(handler);
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
    }
}

/**
 * @brief Display the real-world graph selection menu and handle user input.
 *
 * @param handler The Handler object to manage the graph.
 */
void realWorldMenu(Handler handler) {
    char optionData;
    cout << "------ REAL-WORLD GRAPHS ------ \n";
    cout << "Choose DataSet:" << endl;
    cout << "1 - Graph 1." << endl;
    cout << "2 - Graph 2." << endl;
    cout << "3 - Graph 3." << endl;
    cout << "4 - Exit." << endl;
    cout << "------------------------------------- \n" << endl;

    cout << "Enter your choice: " << endl;
    cin >> optionData;

    switch (optionData) {
        case '1':
            cout << "Loading graph ..." << endl;
            handler.load_RealWorld("../Real-world-Graphs/graph1/nodes.csv", "../Real-world-Graphs/graph1/edges.csv");
            mainMenu(handler);
            break;
        case '2':
            cout << "Loading graph ..." << endl;
            handler.load_RealWorld("../Real-world-Graphs/graph2/nodes.csv", "../Real-world-Graphs/graph2/edges.csv");
            mainMenu(handler);
            break;
        case '3':
            cout << "Loading graph ..." << endl;
            handler.load_RealWorld("../Real-world-Graphs/graph3/nodes.csv", "../Real-world-Graphs/graph3/edges.csv");
            mainMenu(handler);
            break;
        case '4':
            cout << "Exiting Real-World Graph Menu..." << endl;
            break;
        default:
            cout << "Invalid Input. Please Try Again." << endl;
            realWorldMenu(handler);
            break;
    }
}

bool menuOn = true;

/**
 * @brief Display the dataset selection menu and handle user input.
 *
 * @param handler The Handler object to manage the graph.
 */
void datasetChoice(Handler handler) {
    char optionData;
    cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
    cout << "Choose DataSet:" << endl;
    cout << "1 - Toy Graphs." << endl;
    cout << "2 - Real-World Graphs." << endl;
    cout << "3 - Extra Fully Connected Graphs." << endl;
    cout << "4 - Exit." << endl;
    cout << "------------------------------------- \n" << endl;

    cout << "Enter your choice: " << endl;
    cin >> optionData;

    switch (optionData) {
        case '1':
            handler.setToy(true);
            toygraphChoice(handler);
            break;
        case '2':
            realWorldMenu(handler);
            break;
        case '3':
            handler.setEFC(true);
            fullyConnectedChoice(handler);
            break;
        case '4':
            menuOn = false;
            break;
        default:
            cout << "Invalid Choice.";
            break;
    }
}

/**
 * @brief Main function to start the program and display the dataset selection menu.
 *
 * @return int Exit status code.
 */
int main() {
    Handler handler;

    while (menuOn) {
        datasetChoice(handler);
    }

    return 0;
}
