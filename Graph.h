#ifndef DA_GRAPH_H
#define DA_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#define INF std::numeric_limits<double>::max()

// Forward declaration of GraphEdge class
class GraphEdge;

class GraphNode {
public:
    /**
     * @brief Constructs a new GraphNode object.
     * @param id The unique identifier of the graph node.
     * @param code The code associated with the graph node.
     * @param available Indicates whether the node is available.
     */
    GraphNode(int id, std::string code, bool available) : id_(id), code_(std::move(code)), available(available) {}

    /**
     * @brief Gets the ID of the graph node.
     * @return The ID of the graph node.
     */
    const int& getID() const {
        return id_;
    }

    /**
     * @brief Checks if the graph node has been visited during traversal.
     * @return True if the node has been visited, false otherwise.
     */
    bool isVisited() const {
        return visited;
    }

    /**
     * @brief Sets the visit status of the graph node.
     * @param status The visit status to be set.
     */
    void setVisited(bool status) {
        visited = status;
    }

    /**
     * @brief Checks if the graph node is available.
     * @return True if the node is available, false otherwise.
     */
    virtual bool isAvailable() {
        return available;
    }

    /**
     * @brief Sets the availability status of the graph node.
     * @param a The availability status to be set.
     */
    virtual void setAvailable(bool a) {
        available = a;
    }

    /**
     * @brief Adds an edge incident on the node.
     * @param edge Pointer to the edge to be added.
     */
    void addEdge(GraphEdge* edge) {
        edges.push_back(edge);
    }

    std::vector<GraphEdge*> getAllEdges(){
        return edges;
    }

private:
    int id_; /**< The unique identifier of the graph node. */
    std::string code_; /**< The code associated with the graph node. */
    bool visited = false; /**< Indicates whether the node has been visited during traversal. */
    bool available; /**< Indicates whether the node is available. */
    std::vector<GraphEdge*> edges; /**< Vector of edges incident on the node. */
};

class GraphEdge {
public:
    /**
     * @brief Constructs a new GraphEdge object.
     * @param source The source vertex of the edge.
     * @param destination The destination vertex of the edge.
     * @param weight The weight of the edge.
     */
    GraphEdge(GraphNode* source, GraphNode* destination, double weight) : source(source), destination(destination), weight(weight) {
        source->addEdge(this);
        destination->addEdge(this);
    }

    /**
     * @brief Gets the source vertex of the edge.
     * @return The source vertex of the edge.
     */
    GraphNode* getSource() const {
        return source;
    }

    /**
     * @brief Gets the destination vertex of the edge.
     * @return The destination vertex of the edge.
     */
    GraphNode* getDestination() const {
        return destination;
    }

    /**
     * @brief Gets the weight of the edge.
     * @return The weight of the edge.
     */
    double getWeight() const {
        return weight;
    }

private:
    GraphNode* source; /**< The source vertex of the edge. */
    GraphNode* destination; /**< The destination vertex of the edge. */
    double weight; /**< The weight of the edge. */
};

/**
 * @brief The Graph class represents a graph network.
 */
class Graph {
public:
    /**
     * @brief Constructs a new Graph object with a source and a destination.
     */
    explicit Graph() {

    }

    /**
     * @brief Destroys the Graph object and deallocates memory.
     */
    ~Graph() {
        for (GraphNode* vertex : vertices){
            for (GraphEdge* edge : vertex->getAllEdges()) {
                delete edge;
            }
            delete vertex;
        }
    }

    /**
     * @brief Adds a vertex to the graph.
     *
     * @param data The vertex to add.
     * @return The added vertex.
     */
    GraphNode * addVertex(GraphNode* data) {
        vertices.push_back(data);
        return data;
    }

    /**
     * @brief Gets all vertices in the graph.
     *
     * @return A vector containing all vertices.
     */
    std::vector<GraphNode *> getAllVertex() {
        return vertices;
    }

    /**
     * @brief Restores the original availability settings of all vertices in the graph.
     */
    void restoreOriginalSettings(){
        for(auto vertex : vertices){
            vertex->setAvailable(true);
        }
    }


private:
    std::vector<GraphNode*> vertices;
};

#endif //DA_GRAPH_H
