#ifndef QUAD_TREE_H
#define QUAD_TREE_H

// ==================================================================================
// Module: Core Geospatial Quadtree Architecture
// Purpose: Defines the data strucutre that can hold infrastrucutre information (e.g., basic station info)
//          that's spreadout in an area (like a map) in an optimal way where only when it's necesary.
// Note: 
// ==================================================================================

#include <vector>
#include <memory>
#include "graph.h"

/**
 * @struct BoundingBox
 * @brief Represents 2D area of a Quadtree node (e.g., a section in a map)
 * 
 * @note ASSUMPTIONS:
 * - x_center and y_center: Represents the center coordinate of the bounding box.
 * - half_width and half_height: Represents the dimensions of the bounding box from side to center.
 * - contains: Returns if the coordinate (x, y) are inside the box in question.
 * - 
 */
struct BoundingBox {
    double x_center;
    double y_center;
    double half_width;
    double half_height;

    /**
     * @brief Checks if a given coordinate lies with the bounding box.
     */
    bool contains(double x, double y) const {
        return (x >= x_center - half_width && x <= x_center + half_width &&
                y >= y_center - half_height && y <= y_center + half_height);
    }
    
    /**
     * @brief Checks if this bounding boc overlaps with another bounding box.
     */
    bool intersects(const BoundingBox& range) const {
        return !(range.x_center - range.half_width > x_center + half_width ||
                 range.x_center + range.half_width < x_center - half_width ||
                 range.y_center - range.half_height > y_center + half_height ||
                 range.y_center + range.half_height < y_center - half_height);
    }
};

/**
 * @struct QuadNode
 * @brief Represents a node stored in the Quadtree referening Graph nodes
 * 
 * @note ASSUMPTIONS:
 * - id: ID of the Graph node
 * - coordinate (x, y): x and y coordinates of a 2D area
 */
struct QuadNode {
    int id;
    double x;
    double y;
};


/**
 * @class Quadtree
 * @brief Spatial quadtree architecture for geospatial network modeling.
 * 
 */
class Quadtree {
private:
    BoundingBox boundary_;
    int capacity_; // Max nodes a quadrant can hold before splitting
    bool divided_;

    std::vector<QuadNode> nodes_;

    // Children quadrants (NW, NE, SW, SE)
    std::unique_ptr<Quadtree> northwest_;
    std::unique_ptr<Quadtree> northeast_;
    std::unique_ptr<Quadtree> southwest_;
    std::unique_ptr<Quadtree> southeast_;

    void subdivide();

public:
    Quadtree(BoundingBox boundary, int capacity);

    // Insert a node's coordinates into the spatial index
    bool insert(int id, double x, double y);

    // Query all node IDs within a specific geographic range or radius
    void queryRange(const BoundingBox range, std::vector<int>& found_ids) const;
};

#endif // QUAD_TREE_H