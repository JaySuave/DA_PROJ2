#include <iostream>
#include "Handler.h"
#include<unistd.h>

using namespace std;

void mainMenu(Handler handler)
{
    char option;
    bool isToy = handler.isToy();
    bool isEFC = handler.isEFC();

    cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
    cout << "Choose action:" << endl;
    if(handler.isToy() || handler.isEFC()) {
        cout << "1 - Backtracking Algorithm." << endl;
        cout << "2 - Triangular Approximation Heuristic." << endl;
        cout << "3 - Show loaded Graph." << endl;
    }
    else{
        cout << "1 - Triangular Approximation Heuristic." << endl;
        cout << "2 - Other Heuristics." << endl;
        cout << "3 - Show loaded Graph." << endl;
    }
    cout << "------------------------------------- \n" << endl;

    cout << "Enter your choice: ";
    cin >> option;

    switch(option){
        case '1':
            if(isToy){
                vector<unsigned int> path;
                double min_cost = handler.get_graph().backtracking_caller(path);
                cout << "Minimum Cost: " << min_cost << endl;
                cout << "BestPath:";
                for(int i = 0; i < path.size() ; i++){
                    cout << path[i] << "->";
                }
                cout << path[0] << endl;
            }
            else{
                handler.computeMST();
                handler.approximateTSP();
            }
            break;
        case '2':
            if(isToy){
                handler.triangular_approximation_tsp();
            }
            else if(isEFC){
                handler.computeMST();
                handler.approximateTSP();

            }
            else{
                cout << "TODO Other Heuristics" << endl;

            }
            break;
        case '3':
            if(isToy){
                handler.print_Graph();
            }
            else{
                handler.print_RealWorld_Graph();
            }
            handler.print_Graph();
            break;
        default:
            cout << "Invalid Choice";
            break;
    }

    /*
    auto start = chrono::high_resolution_clock::now();
    int min_path = handler.get_graph().TSP_Backtracking(0);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Minimum path length: " << min_path << endl;
    cout << "Time taken by TSP_Backtracking: " << duration.count() << " microseconds" << endl;
    */

}


void toygraphChoice(Handler handler)
{
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

    switch(option){
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

void fullyConnectedChoice(Handler handler)
{
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

    switch(stoi(option)){
        case 1:
            //filePath.append("edges_25.csv");
            handler.read_RealWorld("../Extra_Fully_Connected_Graphs/nodes.csv", "../Extra_Fully_Connected_Graphs/edges_25.csv");

            //handler.load_toy_efc_Graph(filePath);
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



void datasetChoice(Handler handler) {

    char optionData;
    cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
    cout << "Choose DataSet:" << endl;
    cout << "1 - Toy Graphs." << endl;
    cout << "2 - Real-World Graphs." << endl;
    cout << "3 - Extra Fully Connected Graphs." << endl;
    cout << "------------------------------------- \n" << endl;

    cout << "Enter your choice: ";
    cin >> optionData;


    switch(optionData){
        case '1':
            handler.setToy(true);
            toygraphChoice(handler);
            break;
        case '2':
            handler.read_RealWorld("../Real-world-Graphs/graph1/nodes.csv", "../Real-world-Graphs/graph1/edges.csv");
            mainMenu(handler);
            break;break;
        case '3':
            handler.setEFC(true);
            fullyConnectedChoice(handler);
            break;
        default:
            cout << "Invalid Choice.";
            break;
    }
}



int main()
{
    Handler handler;

    datasetChoice(handler);

    return 0;
}