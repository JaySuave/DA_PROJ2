#include <iostream>
#include "Handler.h"
#include<unistd.h>

using namespace std;

void mainMenu(Handler handler)
{
    char option;
    bool isToy = handler.isToy();

    cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
    cout << "Choose action:" << endl;
    if(handler.isToy()) {
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
                cout << "triangluar todo";
            }
            break;
        case '2':
            cout << "todo";
            break;
        case '3':
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
    basic_string<char> filePath = "../Toy-Graphs/";

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
            handler.load_toyGraph(filePath);
            mainMenu(handler);
            break;
        case '2':
            filePath.append("stadiums.csv");
            handler.load_toyGraph(filePath);
            mainMenu(handler);
            break;
        case '3':
            filePath.append("tourism.csv");
            handler.load_toyGraph(filePath);
            mainMenu(handler);
            break;
        default:
            cout << "Invalid Choice. Please Choose Again.\n";
            break;
    }

}

void fullyConnectedChoice(Handler handler)
{

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

    if (option == "1") {
        //handler.read_FullyConnectedGraph("edges_25.csv");
        sleep(1);
        mainMenu(handler);
    } else if (option == "2") {
        //handler.read_FullyConnectedGraph("edges_25.csv");
        handler.print_Graph();
        sleep(1);
        mainMenu(handler);
    }else if (option == "3"){

    }

}

void datasetChoice(Handler handler) {

    string optionData;
    cout << "------ SHIPPING AND DELIVERIES ------ \n" << endl;
    cout << "Choose DataSet:" << endl;
    cout << "1 - Toy Graphs." << endl;
    cout << "2 - Real-World Graphs." << endl;
    cout << "3 - Extra Fully Connected Graphs." << endl;
    cout << "------------------------------------- \n" << endl;

    cout << "Enter your choice: ";
    cin >> optionData;

    if (optionData == "1") {
    handler.setToy(true);
    toygraphChoice(handler);
    } else if (optionData == "2") {
        //para testar:
    handler.read_RealWorld("../Real-world-Graphs/graph1/nodes.csv", "../Real-world-Graphs/graph1/edges.csv");
        handler.print_RealWorld_Graph();

    } else if (optionData == "3"){
        fullyConnectedChoice(handler);
    }
}



int main()
{
    Handler handler;

    datasetChoice(handler);

    return 0;
}