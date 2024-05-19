/**
 * @file Handler.h
 * @brief Handler class for managing graph operations, including reading from files and printing graphs.
 *
 * This file contains the definition of the Handler class, which provides methods for loading and managing
 * both fully connected toy graphs and real-world graphs from files.
 */

#ifndef HANDLER_H
#define HANDLER_H

#include <vector>
#include "Graph.h"
#include <string>
#include <filesystem>
#include <unordered_map>

/**
 * @class Handler
 * @brief Manages the loading, storing, and operations on graphs, including both toy and real-world graphs.
 */
class Handler {
public:
    Graph graph; ///< Public graph instance for general use.

    /**
     * @brief Reads a fully connected graph from a file.
     * @param file Path to the file containing the graph data.
     */
    void read_FullyConnectedGraph(string file);

    /**
     * @brief Prints the currently loaded graph.
     */
    void print_Graph();

    /**
     * @brief Prints the real-world graph.
     */
    void print_RealWorld_Graph();

    /**
     * @brief Loads a toy edge-first connected (EFC) graph from a line of text.
     * @param line Line of text containing the EFC graph data.
     */
    void load_toy_efc_Graph(string line);

    /**
     * @brief Gets the current graph.
     * @return The current graph instance.
     */
    Graph get_graph();

    /**
     * @brief Loads a real-world graph from node and edge files.
     * @param nodeFile Path to the file containing node data.
     * @param edgeFile Path to the file containing edge data.
     */
    void load_RealWorld(string nodeFile, string edgeFile);

    /**
     * @brief Loads real-world nodes from a line of text.
     * @param line Line of text containing node data.
     */
    void load_RealWorld_Nodes(string line);

    /**
     * @brief Loads real-world edges from a line of text.
     * @param line Line of text containing edge data.
     */
    void load_RealWorld_Edges(string line);

    /**
     * @brief Checks if the current graph is a toy graph.
     * @return True if the graph is a toy graph, false otherwise.
     */
    bool isToy();

    /**
     * @brief Sets the current graph as a toy graph.
     * @param toy Boolean value indicating if the graph is a toy graph.
     */
    void setToy(bool toy);

    /**
     * @brief Checks if the current graph is an edge-first connected (EFC) graph.
     * @return True if the graph is an EFC graph, false otherwise.
     */
    bool isEFC();

    /**
     * @brief Sets the current graph as an edge-first connected (EFC) graph.
     * @param efc Boolean value indicating if the graph is an EFC graph.
     */
    void setEFC(bool efc);

private:
    Graph graph_; ///< Internal graph instance for general use.
    Graph real_world_graph_; ///< Internal graph instance for the real-world graph.
    vector<Node> real_world_nodes_; ///< Vector of nodes for the real-world graph.
    bool isToy_ = false; ///< Boolean flag indicating if the graph is a toy graph.
    bool isEFC_ = false; ///< Boolean flag indicating if the graph is an edge-first connected graph.
};

#endif //HANDLER_H
