#ifndef HANDLER_H
#define HANDLER_H

#include <vector>

#include "Graph.h"
#include <string>
#include <filesystem>
#include <unordered_map>

class Handler {
public:
    Graph graph;
    void read_FullyConnectedGraph(string file);
    void print_Graph();
    void print_RealWorld_Graph();

    void load_toy_efc_Graph(string line);

    Graph get_graph();


    void read_RealWorld(string nodeFile, string edgeFile);

    void load_RealWorld_Nodes(string line);
    void load_RealWorld_Edges(string line);

    bool isToy();
    void setToy(bool toy);

    bool isEFC();
    void setEFC(bool efc);
private:
    Graph graph_;
    Graph real_world_graph_;
    vector<Node> real_world_nodes_;
    bool isToy_;
    bool isEFC_;
};



#endif //HANDLER_H
