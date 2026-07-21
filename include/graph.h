#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <stdexcept>

struct Edge {
    int target_node;
    double weight;
    double capacity;
};

struct Node {
    int id;
    double x; // X coordinate
    double y; // Y coordinate
    double demand; // Positive if it needs flow (city), negative if it supplies flow
};

class Graph {
private:
    // The adjacency list - maps a Node ID to a list of its outgoing edges
    std::unordered_map<int, std::vector<Edge>> adj_list_;

    // Node ID and its data
    std::unordered_map<int, Node> nodes_;

public:
    Graph() = default;

    // Setters for building the network
    void addNode(int id, double x, double y, double demand = 0.0);
    void addEdge(int source, int target, double weight, double capacity);

    // Getters for testing
    const Node& getNode(int id) const;
    const std::vector<Edge>& getEdges(int node_id) const;
    size_t getNumNodes() const;    
};

#endif // GRAPH_H