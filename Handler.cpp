#include "Handler.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>


Graph Handler::get_graph()
{
    return this->graph_;
}

bool Handler::isToy(){
    return this->isToy_;
}

void Handler::setToy(bool toy) {
    this->isToy_ = toy;
}

bool Handler::isEFC(){
    return this->isEFC_;
}

void Handler::setEFC(bool efc) {
    this->isEFC_ = efc;
}

//TODO: add labels to origin and destination nodes
void Handler::load_toy_efc_Graph(std::string filePath) {
    std::fstream file;
    file.open(filePath);

    if (file.fail()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string origem, destino, distancia;

        std::getline(ss, origem, ',');
        std::getline(ss, destino, ',');
        std::getline(ss, distancia, ',');

        int origemId = std::stoi(origem);
        int destinoId = std::stoi(destino);
        double dist = std::stod(distancia);

        // Find or create origin node
        Node* origin_node = this->graph_.find_node(origemId);
        if (origin_node == nullptr) {
            origin_node = new Node(origemId);
            this->graph_.add_node(origin_node);
        }

        // Find or create destination node
        Node* dest_node = this->graph_.find_node(destinoId);
        if (dest_node == nullptr) {
            dest_node = new Node(destinoId);
            this->graph_.add_node(dest_node);
        }

        // Create and add 2 edges to simulate bidirectional edges
        Edge* edge1 = new Edge(origin_node, dest_node, dist);
        Edge* edge2 = new Edge(dest_node, origin_node, dist);
        origin_node->add_edge_to_node(edge1);
        dest_node->add_edge_to_node(edge2);

        }

    file.close();
}


void Handler::load_RealWorld_Nodes(string line)
{
    vector<string> loaded;
    stringstream ss(line);
    string col;

    while(getline(ss,col, ',')) {
        loaded.push_back(col);
    }

    Node input(stoi(loaded[0]), stod(loaded[1]), stod(loaded[2]));

    Node * real_node = new Node(input.getNodeId(), input.getNodeLongitude(), input.getNodeLatitude());
    this->real_world_graph_.add_node(real_node);
    this->real_world_nodes_.push_back(input);
}

void Handler::load_RealWorld_Edges(string line)
{
    vector<string> loaded;
    stringstream ss(line);
    string col;

    while(getline(ss,col, ',')) {
        loaded.push_back(col);
    }

        Node * origin_node = this->real_world_graph_.find_node(stoi(loaded[0]));
        if (origin_node == nullptr) {
            origin_node = new Node(stoi(loaded[0]));
            this->real_world_graph_.add_node(origin_node);
        }

        Node * dest_node = this->real_world_graph_.find_node(stoi(loaded[1]));
        if (dest_node == nullptr) {
            dest_node = new Node(stoi(loaded[1]));
            this->real_world_graph_.add_node(dest_node);
        }

        Edge * new_edge = new Edge(origin_node, dest_node, stod(loaded[2]));

        origin_node->add_edge_to_node(new_edge);

}

void Handler::read_RealWorld(string NodeFilePath, string EdgeFilePath){
    this->real_world_nodes_.clear();
    this->real_world_graph_.delete_graph();

    // ---------------------- Node Handling ---------------------- //
    fstream realWorldNodesCSV;
    realWorldNodesCSV.open(NodeFilePath);

    // This CSV has a header
    int linePos = 0;

    if(realWorldNodesCSV.fail()) {
        cerr << "Erro: " << NodeFilePath << endl;
    }

    string line;
    while(getline(realWorldNodesCSV, line)) {
        if(line.empty()) {
            continue;
        }

        if(linePos == 1){
            load_RealWorld_Nodes(line);
        }

        linePos = 1;
    }

    realWorldNodesCSV.close();


    // ---------------------- Edge Handling ---------------------- //
    fstream realWorldEdgesCSV;
    realWorldNodesCSV.open(EdgeFilePath);

    // This CSV has a header
    int linePos2 = 0;

    if(realWorldEdgesCSV.fail()) {
        cerr << "Unable to open specified file: " << NodeFilePath << endl;
    }

    string lined;
    while(getline(realWorldEdgesCSV, lined)) {
        if(line.empty()) {
            continue;
        }

        if(linePos2 == 1){
            load_RealWorld_Edges(lined);
        }

        linePos2 = 1;
    }

    realWorldEdgesCSV.close();

}



void Handler::print_Graph() {
    cout << "Printing graph:" << endl;
    for (const auto &node : graph_.get_nodes_vector()) {
        cout << "Node: " << node->getNodeId() << endl;
        for (const auto &edge : node->get_adjacent_edges()) {
            cout << "Edge to Node: " << edge->getEdgeDest()->getNodeId() << ", Distance: " << edge->getEdgeWeight() << endl;
        }
    }
}

void Handler::print_RealWorld_Graph() {
    cout << "Printing real-world graph:" << endl;
    for (const auto &node : real_world_graph_.get_nodes_vector()) {
        cout << "Node: " << node->getNodeId() << ", Longitude: " << node->getNodeLongitude() << ", Latitude: " << node->getNodeLatitude() << endl;
        for (const auto &edge : node->get_adjacent_edges()) {
            cout << "Edge to Node: " << edge->getEdgeDest()->getNodeId() << ", Distance: " << edge->getEdgeWeight() << endl;
        }
    }
}


