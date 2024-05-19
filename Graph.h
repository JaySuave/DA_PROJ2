#ifndef GRAPH_H
#define GRAPH_H

// C++ Libraries
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <unordered_set>
#include <unordered_map>

// Header Files


using namespace std;

class Node;

class Edge{
public:

    Edge(Node *origin, Node *dest, double dist);

    Edge()=default;

    Node* getEdgeOrigin() const;

    Node* getEdgeDest() const;

    double getEdgeWeight() const;

private:
    Node* edge_origin_;
    Node* edge_dest_;
    double edge_weight_;
};

class Node{
public:

    Node(int id, double node_longitude = 0, double node_latitude = 0);

    Node() = default;

    int getNodeId() const;

    double getNodeLongitude() const;

    double getNodeLatitude() const;

    Edge* add_edge_to_node(Edge * new_edge);

    Edge* find_edge(const Node * node_destination);

    vector<Edge *> get_adjacent_edges() const;

    Edge* get_edge_to_node(Node* node_dest);

private:
    int node_id_;
    double node_dist_;
    double node_longitude_;
    double node_latitude_;
    vector<Edge *> adjacent_edges_;
    bool visited;
};


class Graph {
public:
    Graph()=default;

    vector<Node *> get_nodes_vector();

    bool add_node(Node * new_node);

    bool add_edge(Edge * new_edge);

    Node* find_node(unsigned int node_id);

    Edge* find_edge_between(Node* node1, Node* node2);

    void delete_graph();

    //backtracking
    void backtracking(unsigned int n, unsigned int pos, unordered_set<int>& visited, double cost, double& minCost, vector<unsigned int>& curPath, vector<unsigned int>& bestPath);
    void backtracking_caller();

    //triangular approx
    void nearest_neighbour();
    double haversine(double lat1, double lon1, double lat2, double lon2);
    void approximateTSP();
    std::vector<unsigned int> preorderTraversal(Node* node, unordered_map<int, bool>& visited);
    double calculateTourDistance(const std::vector<unsigned int>& tour);
    void computeMST();
private:
    vector<Node *> nodes_vector_;
};


#endif //GRAPH_H
