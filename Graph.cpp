#include "Graph.h"

#include <algorithm>
#include <limits>
#include <unordered_set>
#include <queue>
#include <stack>

// ============ Edge Functions ============== //

Edge::Edge(Node* origin, Node* destination, double distance) {
    this->edge_origin_ = origin;
    this->edge_dest_ = destination;
    this->edge_weight_ = distance;
}

Node* Edge::getEdgeOrigin() const {
    return this->edge_origin_;
}

Node* Edge::getEdgeDest() const{
    return this->edge_dest_;
}

double Edge::getEdgeWeight() const{
    return this->edge_weight_;
}


// ============ Node Functions ============== //

Node::Node(int id, double node_longitude, double node_latitude){
    this->node_id_ = id;
    this->node_longitude_ = node_longitude;
    this->node_latitude_ = node_latitude;
}

int Node::getNodeId() const{
    return this->node_id_;
}

double Node::getNodeLongitude() const{
    return this->node_longitude_;
}

double Node::getNodeLatitude() const{
    return this->node_latitude_;
}

Edge* Node::add_edge_to_node(Edge* edge)
{
    this->adjacent_edges_.push_back(edge);
    return edge;
}

bool Node::isVisited() {
    return this->visited;
}

void Node::setVisited(bool visited_) {
    this->visited = visited_;
}

vector<Edge *> Node::get_adjacent_edges() const {
    return this->adjacent_edges_;
}

// ============ Graph Functions ============== //

vector<Node *> Graph::get_nodes_vector() {
    return this->nodes_vector_;
}

void Graph::delete_graph() {
    this->nodes_vector_.clear();
}

bool Graph::add_node(Node *new_node) {
    if(find_node(new_node->getNodeId())!= nullptr){
        return false;
    }
    this->nodes_vector_.push_back(new_node);
    return true;
}


bool Graph::add_edge(Edge *new_edge) {
    auto origin_node = find_node(new_edge->getEdgeOrigin()->getNodeId());
    auto destination_node = find_node(new_edge->getEdgeDest()->getNodeId());

    if(origin_node == nullptr || destination_node == nullptr){
        perror("Invalid Nodes");
        return false;
    }

    return true;
}

Node* Graph::find_node(unsigned int node_id) {
    for(auto n : this->nodes_vector_){
        if(n->getNodeId() == node_id)return n;
    }
    return nullptr;
}

Edge* Node::get_edge_to_node(Node* node_dest) {
    for(auto edge: this->adjacent_edges_){
        if(edge->getEdgeDest() == node_dest){
            return edge;
        }
    }
    return nullptr;
}


// ============ Functions ============== //


// ========= Backtracking ============= //
void Graph::backtracking(unsigned int n, unsigned int pos, unordered_set<int>& visited, double cost, double& minCost, vector<unsigned int>& curPath, vector<unsigned int>& bestPath) {
    //cout << "Current Node: " << pos << endl;

    visited.insert(pos);
    curPath.push_back(pos);

    bool canBack = false; // boolean para ver se há caminho de regresso ao nó 0
    double temp_weight = 0;

    if (visited.size() == n) {
        for (auto e: this->find_node(pos)->get_adjacent_edges()) {
            if (e->getEdgeDest()->getNodeId() == 0) {
                canBack = true;
                temp_weight = e->getEdgeWeight();
                break;
            }
        }
        if (canBack) {
            cost += temp_weight;
            if ((cost < minCost)) {
                minCost = cost;
                bestPath = curPath;
            }
            curPath.pop_back();
            visited.erase(pos);
            return;
        }
    }

    for (const Edge *e : this->find_node(pos)->get_adjacent_edges()) {
        if (visited.find(e->getEdgeDest()->getNodeId()) == visited.end()) {
            double newCost = cost + e->getEdgeWeight();
            if (newCost < minCost) {
                this->backtracking(n, e->getEdgeDest()->getNodeId(), visited, newCost, minCost, curPath, bestPath);
            }
        }
    }
    curPath.pop_back();
    visited.erase(pos);
}

double Graph::backtracking_caller(vector<unsigned int>& path) {
    unordered_set<int> visited;
    double minCost = numeric_limits<double>::max();
    vector<unsigned int> currentPath;
    vector<unsigned int> bestPath;

    int n = this->nodes_vector_.size();
    backtracking(n,0,visited,0,minCost,currentPath,bestPath);

    //cout << bestPath[0] << " " << bestPath[5] << " " << bestPath[7] << " " << bestPath[13] << "\n";
    path.clear();

    path=bestPath;

    return minCost;
}

// ========== Triangular Apprx ======== //

const double R = 6371.0; // Earth radius in kilometers

double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double Graph::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);

    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::sin(dLon / 2) * std::sin(dLon / 2) * std::cos(lat1) * std::cos(lat2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c;
}

void Graph::approximateTSP() {
    // Compute the MST (Minimum Spanning Tree)
    computeMST();

    // Perform a Preorder DFS traversal on the MST
    std::unordered_map<int, bool> visited;
    std::vector<int> tour;
    Node* start_node = find_node(0);
    if (start_node != nullptr) {
        tour = preorderTraversal(start_node, visited);
    }

    // Compute the total distance of this TSP tour
    double tour_distance = calculateTourDistance(tour);
    std::cout << "Approximate TSP tour distance: " << tour_distance << std::endl;
}

std::vector<int> Graph::preorderTraversal(Node* node, std::unordered_map<int, bool>& visited) {
    std::vector<int> tour;
    if (node == nullptr) return tour;

    std::stack<Node*> stack;
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

double Graph::calculateTourDistance(const std::vector<int>& tour) {
    double total_distance = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        Node* node1 = find_node(tour[i]);
        Node* node2 = find_node(tour[i + 1]);

        if (node1 != nullptr && node2 != nullptr) {
            // Check if there's a direct edge
            double distance = haversine(node1->getNodeLatitude(), node1->getNodeLongitude(),
                                        node2->getNodeLatitude(), node2->getNodeLongitude());
            total_distance += distance;
        }
    }
    return total_distance;
}

void Graph::computeMST() {
    // Priority queue to select the minimum weight edge at each step
    std::priority_queue<std::pair<double, std::pair<Node*, Node*>>,
            std::vector<std::pair<double, std::pair<Node*, Node*>>>,
            std::greater<>> minHeap;

    // Track nodes that have been added to the MST
    std::unordered_map<int, bool> inMST;

    // Start with the first node (with ID 0)
    Node* startNode = find_node(0);
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

double Graph::triangular_approximation_tsp() {
    // Ensure graph is not empty
    if (nodes_vector_.empty()) {
        return 0.0;
    }

    // Start at the node with the zero-identifier label
    Node* current_node = find_node(0);
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
    while (visited.size() < nodes_vector_.size()) {
        // Find the nearest neighbor not yet visited
        double min_distance = std::numeric_limits<double>::max();
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
    Edge* return_edge = current_node->get_edge_to_node(find_node(0));
    if (return_edge) {
        total_distance += return_edge->getEdgeWeight();
    }

    std::cout << "Triangular Approximation TSP tour distance: " << total_distance << std::endl;

    return total_distance;
}