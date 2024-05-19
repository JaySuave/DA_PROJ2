/**
 * @file Graph.h
 * @brief Graph data structure and related algorithms for the Traveling Salesman Problem (TSP).
 *
 * This file contains the definitions of the Node, Edge, and Graph classes, which are used to
 * represent a graph and perform various algorithms such as backtracking and nearest neighbor
 * approximation for solving the TSP.
 */

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

/**
 * @class Edge
 * @brief Represents an edge in a graph, connecting two nodes with a specified distance (weight).
 */
class Edge{
public:

    /**
     * @brief Constructor to create an edge with specified origin, destination, and weight.
     * @param origin Pointer to the origin node.
     * @param dest Pointer to the destination node.
     * @param dist Distance or weight of the edge.
     */
    Edge(Node *origin, Node *dest, double dist);

    /**
     * @brief Default constructor for Edge.
     */
    Edge()=default;

    /**
     * @brief Gets the origin node of the edge.
     * @return Pointer to the origin node.
     */
    Node* getEdgeOrigin() const;

    /**
     * @brief Gets the destination node of the edge.
     * @return Pointer to the destination node.
     */
    Node* getEdgeDest() const;

    /**
     * @brief Gets the weight of the edge.
     * @return Distance or weight of the edge.
     */
    double getEdgeWeight() const;

private:
    Node* edge_origin_; ///< Pointer to the origin node.
    Node* edge_dest_;   ///< Pointer to the destination node.
    double edge_weight_;///< Weight of the edge.
};

/**
 * @class Node
 * @brief Represents a node in a graph with an ID, longitude, latitude, and adjacent edges.
 */
class Node{
public:

    /**
     * @brief Constructor to create a node with a specified ID, longitude, and latitude.
     * @param id ID of the node.
     * @param node_longitude Longitude of the node (default is 0).
     * @param node_latitude Latitude of the node (default is 0).
     */
    Node(int id, double node_longitude = 0, double node_latitude = 0);

    /**
     * @brief Default constructor for Node.
     */
    Node() = default;

    /**
     * @brief Gets the ID of the node.
     * @return ID of the node.
     */
    int getNodeId() const;

    /**
     * @brief Gets the longitude of the node.
     * @return Longitude of the node.
     */
    double getNodeLongitude() const;

    /**
     * @brief Gets the latitude of the node.
     * @return Latitude of the node.
     */
    double getNodeLatitude() const;

    /**
     * @brief Adds an edge to the node's adjacency list.
     * @param new_edge Pointer to the new edge to be added.
     * @return Pointer to the added edge.
     */
    Edge* add_edge_to_node(Edge * new_edge);

    /**
     * @brief Finds an edge in the node's adjacency list that leads to a specified destination node.
     * @param node_destination Pointer to the destination node.
     * @return Pointer to the found edge, or nullptr if not found.
     */
    Edge* find_edge(const Node * node_destination);

    /**
     * @brief Gets all adjacent edges of the node.
     * @return Vector of pointers to adjacent edges.
     */
    vector<Edge *> get_adjacent_edges() const;

    /**
     * @brief Gets the edge leading to a specified destination node.
     * @param node_dest Pointer to the destination node.
     * @return Pointer to the edge, or nullptr if not found.
     */
    Edge* get_edge_to_node(Node* node_dest);

private:
    int node_id_; ///< ID of the node.
    double node_dist_; ///< Distance from the starting node (used in algorithms).
    double node_longitude_; ///< Longitude of the node.
    double node_latitude_; ///< Latitude of the node.
    vector<Edge *> adjacent_edges_; ///< List of adjacent edges.
    bool visited; ///< Visitation state of the node (used in algorithms).
};

/**
 * @class Graph
 * @brief Represents a graph consisting of nodes and edges, with methods for TSP algorithms.
 */
class Graph {
public:
    /**
     * @brief Default constructor for Graph.
     */
    Graph()=default;

    /**
     * @brief Gets the vector of nodes in the graph.
     * @return Vector of pointers to nodes.
     */
    vector<Node *> get_nodes_vector();

    /**
     * @brief Adds a node to the graph.
     * @param new_node Pointer to the new node to be added.
     * @return True if the node was added successfully, false otherwise.
     */
    bool add_node(Node * new_node);

    /**
     * @brief Adds an edge to the graph.
     * @param new_edge Pointer to the new edge to be added.
     * @return True if the edge was added successfully, false otherwise.
     */
    bool add_edge(Edge * new_edge);

    /**
     * @brief Finds a node in the graph by its ID.
     * @param node_id ID of the node to be found.
     * @return Pointer to the found node, or nullptr if not found.
     */
    Node* find_node(unsigned int node_id);

    /**
     * @brief Finds an edge between two specified nodes.
     * @param node1 Pointer to the first node.
     * @param node2 Pointer to the second node.
     * @return Pointer to the found edge, or nullptr if not found.
     */
    Edge* find_edge_between(Node* node1, Node* node2);

    /**
     * @brief Deletes the entire graph, freeing all allocated memory.
     */
    void delete_graph();

    /**
     * @brief Backtracking algorithm for TSP.
     * @param n Number of nodes.
     * @param pos Current position.
     * @param visited Set of visited node IDs.
     * @param cost Current cost of the path.
     * @param minCost Minimum cost found so far.
     * @param curPath Current path being explored.
     * @param bestPath Best path found so far.
     */
    void backtracking(unsigned int n, unsigned int pos, unordered_set<int>& visited, double cost, double& minCost, vector<unsigned int>& curPath, vector<unsigned int>& bestPath);

    /**
     * @brief Caller for the backtracking algorithm, initializing necessary variables.
     */
    void backtracking_caller();

    /**
     * @brief Nearest neighbour algorithm for TSP.
     */
    void nearest_neighbour(int initial_node);

    /**
     * @brief Computes the Haversine distance between two geographical points.
     * @param lat1 Latitude of the first point.
     * @param lon1 Longitude of the first point.
     * @param lat2 Latitude of the second point.
     * @param lon2 Longitude of the second point.
     * @return Distance between the two points.
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Approximate TSP solution using triangular inequality.
     */
    void approximateTSP();

    /**
     * @brief Preorder traversal of the graph for MST-based TSP approximation.
     * @param node Pointer to the starting node.
     * @param visited Map of visited nodes.
     * @return Vector of node IDs in preorder traversal order.
     */
    std::vector<unsigned int> preorderTraversal(Node* node, unordered_map<int, bool>& visited);

    /**
     * @brief Calculates the total distance of a given tour.
     * @param tour Vector of node IDs representing the tour.
     * @return Total distance of the tour.
     */
    double calculateTourDistance(const std::vector<unsigned int>& tour);

    /**
     * @brief Computes the Minimum Spanning Tree (MST) of the graph.
     */
    void computeMST();

    vector<int> dijkstra(int src, int dest);

    void real_world_nearest_neighbours(unsigned int start_node_id);

private:
    vector<Node *> nodes_vector_; ///< Vector of pointers to nodes in the graph.
};

#endif //GRAPH_H
