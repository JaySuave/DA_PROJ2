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

////////////////////////////////////////////// Triangular Approximation TSP //////////////////////////////////////////////

const double R = 6371.0; // Earth radius in kilometers

double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double Handler::haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0;
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);

    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::sin(dLon / 2) * std::sin(dLon / 2) * std::cos(lat1) * std::cos(lat2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c;
}

void Handler::approximateTSP() {
    // Compute the MST (Minimum Spanning Tree)
    computeMST();

    // Perform a Preorder DFS traversal on the MST
    std::unordered_map<int, bool> visited;
    std::vector<int> tour;
    Node* start_node = real_world_graph_.find_node(0);
    if (start_node != nullptr) {
        tour = preorderTraversal(start_node, visited);
    }

    // Compute the total distance of this TSP tour
    double tour_distance = calculateTourDistance(tour);
    std::cout << "Approximate TSP tour distance: " << tour_distance << std::endl;
}

std::vector<int> Handler::preorderTraversal(Node* node, unordered_map<int, bool>& visited) {
    std::vector<int> tour;
    if (node == nullptr) return tour;

    stack<Node*> stack;
    stack.push(node);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        if (visited[current->getNodeId()]) continue;

        visited[current->getNodeId()] = true;
        tour.push_back(current->getNodeId());

        for (auto edge : current->get_adjacent_edges()) {
            Node* neighbor = edge->getEdgeDest();
            if (!visited[neighbor->getNodeId()]) {
                stack.push(neighbor);
            }
        }
    }

    // Return to the starting node
    tour.push_back(node->getNodeId());

    return tour;
}

double Handler::calculateTourDistance(const std::vector<int>& tour) {
    double total_distance = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        Node* node1 = real_world_graph_.find_node(tour[i]);
        Node* node2 = real_world_graph_.find_node(tour[i + 1]);

        if (node1 != nullptr && node2 != nullptr) {
            // Check if there's a direct edge
            double distance = haversine(node1->getNodeLatitude(), node1->getNodeLongitude(),
                                        node2->getNodeLatitude(), node2->getNodeLongitude());
            total_distance += distance;
        }
    }
    return total_distance;
}

void Handler::computeMST() {
    // Priority queue to select the minimum weight edge at each step
    priority_queue<std::pair<double, std::pair<Node*, Node*>>,
                   std::vector<std::pair<double, std::pair<Node*, Node*>>>,
                   std::greater<>> minHeap;

    // Track nodes that have been added to the MST
    std::unordered_map<int, bool> inMST;

    // Start with the first node (with ID 0)
    Node* startNode = real_world_graph_.find_node(0);
    if (startNode == nullptr) return;

    inMST[startNode->getNodeId()] = true;

    // Add all edges from the start node to the priority queue
    for (auto edge : startNode->get_adjacent_edges()) {
        minHeap.push({edge->getEdgeWeight(), {startNode, edge->getEdgeDest()}});
    }

    // While the priority queue is not empty
    while (!minHeap.empty()) {
        // Get the minimum weight edge
        auto minEdge = minHeap.top();
        minHeap.pop();

        Node* u = minEdge.second.first;
        Node* v = minEdge.second.second;
        double weight = minEdge.first;

        // Check if the destination node is already in MST
        if (inMST[v->getNodeId()]) continue;

        // Add the node to MST
        inMST[v->getNodeId()] = true;

        // Create the edge and add it to MST
        Edge* mstEdge1 = new Edge(u, v, weight);
        Edge* mstEdge2 = new Edge(v, u, weight); // Bidirectional edge
        u->add_edge_to_node(mstEdge1);
        v->add_edge_to_node(mstEdge2);

        // Add all edges from the newly added node to the priority queue
        for (auto edge : v->get_adjacent_edges()) {
            if (!inMST[edge->getEdgeDest()->getNodeId()]) {
                minHeap.push({edge->getEdgeWeight(), {v, edge->getEdgeDest()}});
            }
        }
    }
}

double Handler::triangular_approximation_tsp() {
    // Ensure graph is not empty
    if (graph_.get_nodes_vector().empty()) {
        return 0.0;
    }

    // Start at the node with the zero-identifier label
    Node* current_node = graph_.find_node(0);
    if (current_node == nullptr) {
        return 0.0; // Error: Starting node not found
    }

    // Set to keep track of visited nodes
    std::unordered_set<Node*> visited;
    visited.insert(current_node);

    // Initialize total distance and current node ID
    double total_distance = 0.0;
    int current_node_id = 0;

    // Loop until all nodes are visited
    while (visited.size() < graph_.get_nodes_vector().size()) {
        // Find the nearest neighbor not yet visited
        double min_distance = numeric_limits<double>::max();
        Node* nearest_neighbor = nullptr;
        for (auto& edge : current_node->get_adjacent_edges()) {
            Node* neighbor = edge->getEdgeDest();
            if (visited.find(neighbor) == visited.end()) {
                double distance = edge->getEdgeWeight();
                if (distance < min_distance) {
                    min_distance = distance;
                    nearest_neighbor = neighbor;
                }
            }
        }

        // Move to the nearest neighbor
        if (nearest_neighbor != nullptr) {
            total_distance += min_distance;
            visited.insert(nearest_neighbor);
            current_node = nearest_neighbor;
        } else {
            return 0.0; // Error: No unvisited neighbors found
        }
    }

    // Connect back to the starting node
    total_distance += current_node->get_edge_to_node(graph_.find_node(0))->getEdgeWeight();

    cout << "Triangular Approximation TSP tour distance: " << total_distance << endl;

    return total_distance;
}








