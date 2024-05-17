#include "Graph.h"

#include <algorithm>
#include <unordered_set>
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

void Graph::backtracking(unsigned int n, unsigned int pos, unordered_set<int>& visited, double cost, double& minCost, vector<unsigned int>& curPath, vector<unsigned int>& bestPath) {
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