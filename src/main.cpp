/*
 * Email: abedallahamodi803@gmail.com
 * main.cpp - Demonstration of Graph and Algorithms usage
 */

#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"
#include <iostream>

using namespace graph;

void printSeparator() {
    std::cout << "\n" << std::string(50, '-') << "\n\n";
}

int main() {
    // Create a sample graph
    Graph g(6);
    
    // Add edges with weights
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    
    std::cout << "Original Graph:" << std::endl;
    g.print_graph();
    
    printSeparator();
    
    // Demonstrate BFS
    std::cout << "BFS Tree starting from vertex 0:" << std::endl;
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();
    
    printSeparator();
    
    // Demonstrate DFS
    std::cout << "DFS Tree starting from vertex 0:" << std::endl;
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();
    
    printSeparator();
    
    // Demonstrate Dijkstra's algorithm
    std::cout << "Shortest Paths Tree from vertex 0:" << std::endl;
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    dijkstraTree.print_graph();
    
    printSeparator();
    
    // Demonstrate Prim's algorithm
    std::cout << "Minimum Spanning Tree (Prim's):" << std::endl;
    Graph primTree = Algorithms::prim(g);
    primTree.print_graph();
    
    printSeparator();
    
    // Demonstrate Kruskal's algorithm
    std::cout << "Minimum Spanning Tree (Kruskal's):" << std::endl;
    Graph kruskalTree = Algorithms::kruskal(g);
    kruskalTree.print_graph();
    
    return 0;
} 