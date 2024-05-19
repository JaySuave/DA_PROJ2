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

void Handler::load_RealWorld_Nodes(std::string line) {
    std::vector<std::string> loaded;
    std::stringstream ss(line);
    std::string col;

    while (std::getline(ss, col, ',')) {
        loaded.push_back(col);
    }

    Node input(std::stoi(loaded[0]), std::stod(loaded[1]), std::stod(loaded[2]));

    Node* real_node = new Node(input.getNodeId(), input.getNodeLongitude(), input.getNodeLatitude());
    this->real_world_graph_.add_node(real_node);
    this->real_world_nodes_.push_back(input);
}

void Handler::load_RealWorld_Edges(std::string line) {
    std::vector<std::string> loaded;
    std::stringstream ss(line);
    std::string col;

    while (std::getline(ss, col, ',')) {
        loaded.push_back(col);
    }

    Node* origin_node = this->real_world_graph_.find_node(std::stoi(loaded[0]));
    if (origin_node == nullptr) {
        origin_node = new Node(std::stoi(loaded[0]));
        this->real_world_graph_.add_node(origin_node);
    }

    Node* dest_node = this->real_world_graph_.find_node(std::stoi(loaded[1]));
    if (dest_node == nullptr) {
        dest_node = new Node(std::stoi(loaded[1]));
        this->real_world_graph_.add_node(dest_node);
    }


    Edge* new_edge = new Edge(origin_node, dest_node, std::stod(loaded[2]));

    origin_node->add_edge_to_node(new_edge);

}

void Handler::read_RealWorld(std::string NodeFilePath, std::string EdgeFilePath) {
    this->real_world_nodes_.clear();
    this->real_world_graph_.delete_graph();

    // ---------------------- Node Handling ---------------------- //
    std::fstream realWorldNodesCSV;
    realWorldNodesCSV.open(NodeFilePath);

    if (realWorldNodesCSV.fail()) {
        std::cerr << "Error: " << NodeFilePath << std::endl;
        return;
    }

    std::string line;
    std::getline(realWorldNodesCSV, line); // Skip the header
    while (std::getline(realWorldNodesCSV, line)) {
        if (!line.empty()) {
            load_RealWorld_Nodes(line);
        }
    }

    realWorldNodesCSV.close();

    // ---------------------- Edge Handling ---------------------- //
    std::fstream realWorldEdgesCSV;
    realWorldEdgesCSV.open(EdgeFilePath);

    if (realWorldEdgesCSV.fail()) {
        std::cerr << "Unable to open specified file: " << EdgeFilePath << std::endl;
        return;
    }

    std::getline(realWorldEdgesCSV, line); // Skip the header
    while (std::getline(realWorldEdgesCSV, line)) {
        if (!line.empty()) {
            load_RealWorld_Edges(line);
        }
    }

    realWorldEdgesCSV.close();
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
