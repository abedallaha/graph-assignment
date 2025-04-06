/*
 * Email: abedallahamodi803@gmail.com
 * Graph.cpp - Implementation of the Graph class
 */

#include "../include/Graph.hpp"
#include <iostream>

namespace graph {

Graph::Graph(int vertices) : numVertices(vertices) {
    // Initialize adjacency lists
    adjacencyList = new Neighbor*[vertices];
    listSizes = new int[vertices];
    listCapacities = new int[vertices];

    for (int i = 0; i < vertices; i++) {
        adjacencyList[i] = new Neighbor[1];  // Start with capacity 1
        listSizes[i] = 0;
        listCapacities[i] = 1;
    }
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        delete[] adjacencyList[i];
    }
    delete[] adjacencyList;
    delete[] listSizes;
    delete[] listCapacities;
}

// Move constructor
Graph::Graph(Graph&& other) noexcept 
    : numVertices(other.numVertices), 
      adjacencyList(other.adjacencyList), 
      listSizes(other.listSizes), 
      listCapacities(other.listCapacities) {
    // Invalidate the other object
    other.numVertices = 0;
    other.adjacencyList = nullptr;
    other.listSizes = nullptr;
    other.listCapacities = nullptr;
}

// Move assignment operator
Graph& Graph::operator=(Graph&& other) noexcept {
    if (this != &other) {
        // Clean up current resources
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
        delete[] listSizes;
        delete[] listCapacities;
        
        // Move resources from other
        numVertices = other.numVertices;
        adjacencyList = other.adjacencyList;
        listSizes = other.listSizes;
        listCapacities = other.listCapacities;
        
        // Invalidate the other object
        other.numVertices = 0;
        other.adjacencyList = nullptr;
        other.listSizes = nullptr;
        other.listCapacities = nullptr;
    }
    return *this;
}

void Graph::resizeList(int vertex, int newCapacity) {
    Neighbor* newList = new Neighbor[newCapacity];
    for (int i = 0; i < listSizes[vertex]; i++) {
        newList[i] = adjacencyList[vertex][i];
    }
    delete[] adjacencyList[vertex];
    adjacencyList[vertex] = newList;
    listCapacities[vertex] = newCapacity;
}

bool Graph::hasEdge(int source, int dest) const {
    for (int i = 0; i < listSizes[source]; i++) {
        if (adjacencyList[source][i].vertex == dest) {
            return true;
        }
    }
    return false;
}

void Graph::addEdge(int source, int dest, int weight) {
    if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
        throw std::invalid_argument("Vertex index out of bounds");
    }
    if (source == dest) {
        throw std::invalid_argument("Cannot add edge from vertex to itself");
    }
    if (hasEdge(source, dest)) {
        throw std::invalid_argument("Edge already exists");
    }

    // Add edge in both directions (undirected graph)
    for (int v : {source, dest}) {
        if (listSizes[v] >= listCapacities[v]) {
            resizeList(v, listCapacities[v] * 2);
        }
        adjacencyList[v][listSizes[v]] = Neighbor(v == source ? dest : source, weight);
        listSizes[v]++;
    }
}

void Graph::removeFromList(int vertex, int neighbor) {
    int i = 0;
    while (i < listSizes[vertex] && adjacencyList[vertex][i].vertex != neighbor) {
        i++;
    }
    if (i < listSizes[vertex]) {
        for (int j = i; j < listSizes[vertex] - 1; j++) {
            adjacencyList[vertex][j] = adjacencyList[vertex][j + 1];
        }
        listSizes[vertex]--;
    }
}

void Graph::removeEdge(int source, int dest) {
    if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
        throw std::invalid_argument("Vertex index out of bounds");
    }
    if (!hasEdge(source, dest)) {
        throw std::invalid_argument("Edge does not exist");
    }

    removeFromList(source, dest);
    removeFromList(dest, source);
}

void Graph::print_graph() const {
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex " << i << ": ";
        for (int j = 0; j < listSizes[i]; j++) {
            std::cout << "(" << adjacencyList[i][j].vertex 
                     << ", w=" << adjacencyList[i][j].weight << ") ";
        }
        std::cout << std::endl;
    }
}

void Graph::addDirectedEdge(int source, int dest, int weight) {
    if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
        throw std::invalid_argument("Vertex index out of bounds");
    }
    if (source == dest) {
        throw std::invalid_argument("Cannot add edge from vertex to itself");
    }
    if (hasEdge(source, dest)) {
        throw std::invalid_argument("Edge already exists");
    }

    // Add edge in only one direction (directed graph)
    if (listSizes[source] >= listCapacities[source]) {
        resizeList(source, listCapacities[source] * 2);
    }
    adjacencyList[source][listSizes[source]] = Neighbor(dest, weight);
    listSizes[source]++;
}

} // namespace graph 