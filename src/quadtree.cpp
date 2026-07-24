#include "quadtree.h"
#include <iostream>
#include <stdexcept>
#include <memory>

Quadtree::Quadtree(BoundingBox boundary, int capacity) : boundary_(boundary), capacity_(capacity), divided_(false) { 

}

bool Quadtree::insert(int id, double x, double y) {
    // Base case 1: coord (x, y) not in the boundary stops 
    if (!boundary_.contains(x, y)) return false;

    // When Quadtree can hold more nodes and not divided_; adds new QuadNode in nodes_
    if (nodes_.size() < capacity_ && !divided_) {
        QuadNode newQuadNode = {id, x, y};
        nodes_.push_back(newQuadNode);
        return true;
    }

    // Recursive: When nodes_ is full but not divided_; subdivide and distribute
    if (!divided_) {
        subdivide();
    }

    // Recursive: distributes to one of the quadrants
    if (northwest_->insert(id, x, y)) return true;
    if (northeast_->insert(id, x, y)) return true;
    if (southwest_->insert(id, x, y)) return true;
    if (southeast_->insert(id, x, y)) return true;
    
    // This shouldn't occur if boundaries align perfectly
    return false;
}

void Quadtree::queryRange(const BoundingBox range, std::vector<int>& found_ids) const {

}

void Quadtree::subdivide() {
    double w = boundary_.half_width / 2.0;
    double h = boundary_.half_height / 2.0;
    double x = boundary_.x_center;
    double y = boundary_.y_center;

    // Create children boundaries (Cartesian coordinates: Positive x moves right, postive y moves up)
    BoundingBox nw_boundary = {x - w, y + h, w, h};
    BoundingBox ne_boundary = {x + w, y + h, w, h};
    BoundingBox sw_boundary = {x - w, y - h, w, h};
    BoundingBox se_boundary = {x + w, y - h, w, h};

    // Create new boundary boxes
    northwest_ = std::make_unique<Quadtree>(nw_boundary, capacity_);
    northeast_ = std::make_unique<Quadtree>(ne_boundary, capacity_);
    southwest_ = std::make_unique<Quadtree>(sw_boundary, capacity_);
    southeast_ = std::make_unique<Quadtree>(se_boundary, capacity_);

    // Distribute the nodes to its children
    for (const auto& node : nodes_) {
        if (northwest_->insert(node.id, node.x, node.y)) continue;
        if (northeast_->insert(node.id, node.x, node.y)) continue;
        if (southwest_->insert(node.id, node.x, node.y)) continue;
        if (southeast_->insert(node.id, node.x, node.y)) continue;
    }

    // Empty the nodes_
    this->nodes_.clear();
    divided_ = true;
}