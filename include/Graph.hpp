/*
 * Email: abedallahamodi803@gmail.com
 * Graph class for storing graph data
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph {

// stores info about a neighbor
struct Neighbor {
    int vertex;     // vertex number
    int weight;     // edge weight

    Neighbor(int v = 0, int w = 1) : vertex(v), weight(w) {}
};

class Graph {
private:
    int numVertices;                    // number of vertices
    Neighbor** adjacencyList;           // array of adjacency lists
    int* listSizes;                     // size of each list
    int* listCapacities;                // capacity of each list

    // helper functions
    void resizeList(int vertex, int newCapacity);
    bool hasEdge(int source, int dest) const;
    void removeFromList(int vertex, int neighbor);

public:
    // constructor
    explicit Graph(int vertices);
    
    // destructor
    ~Graph();

    // cant copy graphs
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;
    
    // can move graphs
    Graph(Graph&& other) noexcept;
    Graph& operator=(Graph&& other) noexcept;

    // main functions
    void addEdge(int source, int dest, int weight = 1);
    void addDirectedEdge(int source, int dest, int weight = 1);
    void removeEdge(int source, int dest);
    void print_graph() const;
    
    // getters
    int getNumVertices() const { return numVertices; }
    const Neighbor* getNeighbors(int vertex) const { return adjacencyList[vertex]; }
    int getNeighborCount(int vertex) const { return listSizes[vertex]; }
};

} // namespace graph

#endif // GRAPH_HPP 