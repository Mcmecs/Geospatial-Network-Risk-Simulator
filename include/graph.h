#ifndef GRAPH_H
#define GRAPH_H

// ==================================================================================
// Module: Core Geospatial Graph Architecture
// Purpose: Defines the network infrastructure (Nodes, Edges, and Adjacency List)
//          used for finding best route (e.g., best flow path) and calculating the system's 
//          capacity to check for any shortfall (e.g., alternate route can meet 50% of demand).
// Note: Simple graph (no self-loop or multi-edges)
// ==================================================================================


#include <vector>
#include <unordered_map>
#include <stdexcept>


/**
 * @struct Edge
 * @brief Represents a physical directional link (pipe flow, cable, or road)
 * 
 * @note ASSUMPTIONS:
 * - weight: Represents cost of travel. Value it fixed for simplicity. Must be >= 0.0.
 *           In hydaulic simulations the "weight" would dynamically change based on flow conditions. 
 * - capacity: Represents pipe standard volumetric flowrate (or cable capacity) 
 *             measured in standard E6 cubic meter per day.
 * 
 * @todo FUTURE IMPROVEMENTS:
 * - Add an `is_active` boolean flag to toggle pipe failure during a maintenance shutdown 
 *   without needing to delete the edge from the adjacency list.
 */
struct Edge {
    int target_node; // Directed graph so need a destination
    double weight; // Distance or cost to travel - need this for Dijkstra's Algo.
    double capacity; // Maximum flow - need this to figure out shortfalls
};

/**
 * @struct Node
 * @brief Represents a physical network vertex (station, server, or city)
 * 
 * @note ASSUMPTIONS:
 * - Coordinates (x, y) represents a 2D Cartesian plane for distance calculation.
 * - demand: Postive number means the node consumes flow (e.g., city); negative
 *           number means the node supplies flow (compressor station). Fixed number for 
 *           simplicity, yet actual would vary depending on site and flow conditions.
 */
struct Node {
    int id; // This can be station or server rack
    double x; // Geographic X coordinate
    double y; // Geographic Y coordinate
    double demand; // Positive if it needs flow (city), negative if it supplies flow
};

/**
 * @class Graph
 * @brief Directed simple sparse graph architecture for geospacial network modeling.
 * 
 * @note TRADEOFF:
 * - We use std::unordered_map<int, vector<Edge>> to optimize RAM footprint for sparse physical grip where E << V^2.
 * - Map lookups O(1) average overhead per node access compared to a flat contiguous array, but allow arbitrary,
 *   non-sequential Node IDs.
 */
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