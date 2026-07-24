#include <gtest/gtest.h>
#include "graph.h"
#include <utility>

// Fixture setup
class GraphTest : public ::testing::Test {
protected:
    Graph g;

    void SetUp() override {
        g.addNode(1, 0.0, 0.0, 100.0);
        g.addNode(2, 10.0, 10.0, 0.0);

        g.addEdge(1, 2, 15.0, 50.0);
    }

};

TEST_F(GraphTest, VerifyNodeAndEdgeCreation) {
    // Verify number of nodes
    EXPECT_EQ(g.getNumNodes(), 2);

    // Verify Node's data
    const Node& n1 = g.getNode(1);
    EXPECT_EQ(n1.demand, 100.0);

    // Verify Edge's data
    const auto& edges = g.getEdges(1);
    EXPECT_EQ(edges.size(), 1);
    EXPECT_EQ(edges[0].target_node, 2);
    EXPECT_DOUBLE_EQ(edges[0].capacity, 50.0);
}

