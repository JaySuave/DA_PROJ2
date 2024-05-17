#ifndef GRAPH_H
#define GRAPH_H

// C++ Libraries
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <unordered_set>

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

    double haversine_formula(const Node* destination_node) const;

    Edge* get_edge_to_node(Node* node_dest);

    bool isVisited();

    void setVisited(bool visited);


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

    void backtracking(unsigned int n, unsigned int pos, unordered_set<int>& visited, double cost, double& minCost, vector<unsigned int>& curPath, vector<unsigned int>& bestPath);

    double backtracking_caller(vector<unsigned int>& path);

    void delete_graph();
private:
    vector<Node *> nodes_vector_;
};


#endif //GRAPH_H
