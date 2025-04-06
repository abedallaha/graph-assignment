/*
 * Email: abedallahamodi803@gmail.com
 * testing the graph stuff
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./doctest.h"
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"

using namespace graph;

// testing basic stuff
TEST_CASE("Graph Basic Operations") {
    Graph g(5);
    
    SUBCASE("Adding edges") {
        g.addEdge(0, 1, 2);
        g.addEdge(1, 2, 3);
        
        CHECK(g.getNeighborCount(0) == 1);
        CHECK(g.getNeighborCount(1) == 2);
        CHECK(g.getNeighborCount(2) == 1);
        
        const Neighbor* neighbors = g.getNeighbors(0);
        CHECK(neighbors[0].vertex == 1);
        CHECK(neighbors[0].weight == 2);
    }
    
    SUBCASE("Removing edges") {
        g.addEdge(0, 1, 2);
        g.removeEdge(0, 1);
        
        CHECK(g.getNeighborCount(0) == 0);
        CHECK(g.getNeighborCount(1) == 0);
    }
    
    SUBCASE("Invalid operations") {
        CHECK_THROWS_AS(g.addEdge(0, 0, 1), std::invalid_argument);
        CHECK_THROWS_AS(g.addEdge(0, 5, 1), std::invalid_argument);
        CHECK_THROWS_AS(g.removeEdge(0, 1), std::invalid_argument);
    }
}

// testing the algorithms
TEST_CASE("Graph Algorithms") {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    
    SUBCASE("BFS") {
        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getNeighborCount(0) > 0);
        CHECK(bfsTree.getNeighborCount(5) == 0);
    }
    
    SUBCASE("DFS") {
        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNeighborCount(0) > 0);
        CHECK(dfsTree.getNeighborCount(5) == 0);
    }
    
    SUBCASE("Dijkstra") {
        Graph dijkstraTree = Algorithms::dijkstra(g, 0);
        CHECK(dijkstraTree.getNeighborCount(0) > 0);
        CHECK(dijkstraTree.getNeighborCount(5) == 0);
    }
    
    SUBCASE("Prim") {
        Graph primTree = Algorithms::prim(g);
        int totalEdges = 0;
        for (int i = 0; i < primTree.getNumVertices(); i++) {
            totalEdges += primTree.getNeighborCount(i);
        }
        CHECK(totalEdges == 2 * (primTree.getNumVertices() - 1));
    }
    
    SUBCASE("Kruskal") {
        Graph kruskalTree = Algorithms::kruskal(g);
        int totalEdges = 0;
        for (int i = 0; i < kruskalTree.getNumVertices(); i++) {
            totalEdges += kruskalTree.getNeighborCount(i);
        }
        CHECK(totalEdges == 2 * (kruskalTree.getNumVertices() - 1));
    }
} 