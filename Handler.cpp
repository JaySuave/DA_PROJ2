#include "Handler.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <limits>
#include <queue>
#include <stack>
#include <unordered_map>

Graph Handler::get_graph() {
    return this->graph_;
}

bool Handler::isToy() {
    return this->isToy_;
}

void Handler::setToy(bool toy) {
    this->isToy_ = toy;
}

bool Handler::isEFC() {
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

void Handler::load_RealWorld_Nodes(string nodesFile) {
    ifstream file(nodesFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << nodesFile << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, lon_str, lat_str;

        getline(ss, id_str, ',');
        getline(ss, lon_str, ',');
        getline(ss, lat_str, ',');

        int id = stoi(id_str);
        double longitude = stod(lon_str);
        double latitude = stod(lat_str);

        Node* new_node = new Node(id, longitude, latitude);
        this->graph_.add_node(new_node);
    }

    file.close();
}

void Handler::load_RealWorld_Edges(string edgesFile) {
    ifstream file(edgesFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << edgesFile << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string origem_str, destino_str, distancia_str;

        getline(ss, origem_str, ',');
        getline(ss, destino_str, ',');
        getline(ss, distancia_str, ',');

        int origem = stoi(origem_str);
        int destino = stoi(destino_str);
        double distancia = stod(distancia_str);

        Node* origin_node = this->graph_.find_node(origem);
        Node* dest_node = this->graph_.find_node(destino);

        if (origin_node && dest_node) {
            // Create and add 2 edges to simulate bidirectional edges
            Edge* edge1 = new Edge(origin_node, dest_node, distancia);
            Edge* edge2 = new Edge(dest_node, origin_node, distancia);
            origin_node->add_edge_to_node(edge1);
            dest_node->add_edge_to_node(edge2);;
        }
    }

    file.close();
}

void Handler::load_RealWorld(string nodeFile, string edgeFile) {
    load_RealWorld_Nodes(nodeFile);
    load_RealWorld_Edges(edgeFile);
}

void Handler::print_Graph() {
    std::cout << "Printing graph:" << std::endl;
    for (const auto& node : graph_.get_nodes_vector()) {
        std::cout << "Node: " << node->getNodeId() << std::endl;
        for (const auto& edge : node->get_adjacent_edges()) {
            std::cout << "Edge to Node: " << edge->getEdgeDest()->getNodeId() << ", Distance: " << edge->getEdgeWeight() << std::endl;
        }
    }
}

void Handler::print_RealWorld_Graph() {
    std::cout << "Printing real-world graph:" << std::endl;
    for (const auto& node : real_world_graph_.get_nodes_vector()) {
        std::cout << "Node: " << node->getNodeId() << ", Longitude: " << node->getNodeLongitude() << ", Latitude: " << node->getNodeLatitude() << std::endl;
        for (const auto& edge : node->get_adjacent_edges()) {
            std::cout << "Edge to Node: " << edge->getEdgeDest()->getNodeId() << ", Distance: " << edge->getEdgeWeight() << std::endl;
        }
    }
}
