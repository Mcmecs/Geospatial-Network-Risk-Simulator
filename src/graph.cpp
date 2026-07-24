#include "graph.h"
#include <iostream>
#include <stdexcept>

void Graph::addNode(int id, double x, double y, double demand) {
    // Check if node already exists
    if (nodes_.find(id) != nodes_.end()) {
        throw std::invalid_argument("Node ID is already exists. Select a unique ID.");
    }

    // Create a new node and add to the node hash map
    Node newNode = {id, x, y, demand};
    nodes_[id] = newNode;
}

void Graph::addEdge(int source, int target, double weight, double capacity) {
    // Check if the Source and Target nodes exist
    if (nodes_.find(source) == nodes_.end() || nodes_.find(target) == nodes_.end()) {
        throw std::invalid_argument("Source or Target node doesn't exist.");
    }

    // Create a new edge and add it to the node's adjacency list
    Edge newEdge = {target, weight, capacity};
    adj_list_[source].push_back(newEdge);
}

const Node& Graph::getNode(int id) const {
    // .at() throws an error is ID doesn't exist
    return nodes_.at(id);
}

const std::vector<Edge>& Graph::getEdges(int node_id) const {
    return adj_list_.at(node_id);
}

size_t Graph::getNumNodes() const {
    return nodes_.size();
}