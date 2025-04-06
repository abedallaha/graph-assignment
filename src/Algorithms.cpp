/*
 * Email: abedallahamodi803@gmail.com
 * Algorithms.cpp - Implementation of the Algorithms class and its helper structures
 */

#include "../include/Algorithms.hpp"
#include <iostream>
#include <climits>  // For INT_MAX

namespace graph {

// Queue implementation
Algorithms::Queue::Queue(int cap) : front(0), rear(-1), size(0), capacity(cap) {
    data = new int[cap];
}

Algorithms::Queue::~Queue() {
    delete[] data;
}

void Algorithms::Queue::enqueue(int x) {
    if (size == capacity) {
        throw std::runtime_error("Queue is full");
    }
    rear = (rear + 1) % capacity;
    data[rear] = x;
    size++;
}

int Algorithms::Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    int x = data[front];
    front = (front + 1) % capacity;
    size--;
    return x;
}

bool Algorithms::Queue::isEmpty() const {
    return size == 0;
}

// PriorityQueue implementation
Algorithms::PriorityQueue::PriorityQueue(int cap) : size(0), capacity(cap) {
    heap = new Item[cap];
    for(int i = 0; i < cap; i++) {
        heap[i] = Item(-1, INT_MAX);  // Initialize with dummy values
    }
}

Algorithms::PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

void Algorithms::PriorityQueue::insert(int vertex, int priority) {
    if (size == capacity) {
        throw std::runtime_error("Priority queue is full");
    }
    heap[size] = Item(vertex, priority);
    int i = size;
    while (i > 0 && heap[(i-1)/2].priority > heap[i].priority) {
        std::swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
    size++;
}

int Algorithms::PriorityQueue::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    int minVertex = heap[0].vertex;
    heap[0] = heap[size-1];
    size--;
    int i = 0;
    while (true) {
        int smallest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        if (left < size && heap[left].priority < heap[smallest].priority) {
            smallest = left;
        }
        if (right < size && heap[right].priority < heap[smallest].priority) {
            smallest = right;
        }
        if (smallest == i) break;
        std::swap(heap[i], heap[smallest]);
        i = smallest;
    }
    return minVertex;
}

void Algorithms::PriorityQueue::decreaseKey(int vertex, int newPriority) {
    int i = 0;
    while (i < size && heap[i].vertex != vertex) i++;
    if (i < size) {
        heap[i].priority = newPriority;
        while (i > 0 && heap[(i-1)/2].priority > heap[i].priority) {
            std::swap(heap[i], heap[(i-1)/2]);
            i = (i-1)/2;
        }
    }
}

bool Algorithms::PriorityQueue::isEmpty() const {
    return size == 0;
}

// UnionFind implementation
Algorithms::UnionFind::UnionFind(int n) : size(n) {
    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

Algorithms::UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

int Algorithms::UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void Algorithms::UnionFind::unite(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) return;
    if (rank[px] < rank[py]) {
        parent[px] = py;
    } else if (rank[px] > rank[py]) {
        parent[py] = px;
    } else {
        parent[py] = px;
        rank[px]++;
    }
}

// Graph Algorithms Implementation
Graph Algorithms::bfs(const Graph& g, int source) {
    int n = g.getNumVertices();
    Graph result(n);
    bool* visited = new bool[n]();
    Queue q(n);
    
    visited[source] = true;
    q.enqueue(source);
    
    while (!q.isEmpty()) {
        int u = q.dequeue();
        const Neighbor* neighbors = g.getNeighbors(u);
        int neighborCount = g.getNeighborCount(u);
        
        for (int i = 0; i < neighborCount; i++) {
            int v = neighbors[i].vertex;
            if (!visited[v]) {
                visited[v] = true;
                result.addDirectedEdge(u, v, neighbors[i].weight);  // Use directed edge
                q.enqueue(v);
            }
        }
    }
    
    delete[] visited;
    return result;
}

Graph Algorithms::dfs(const Graph& g, int source) {
    int n = g.getNumVertices();
    Graph result(n);
    bool* visited = new bool[n]();
    
    struct DFSHelper {
        static void dfsVisit(const Graph& g, Graph& result, bool* visited, int u) {
            visited[u] = true;
            const Neighbor* neighbors = g.getNeighbors(u);
            int neighborCount = g.getNeighborCount(u);
            
            for (int i = 0; i < neighborCount; i++) {
                int v = neighbors[i].vertex;
                if (!visited[v]) {
                    result.addDirectedEdge(u, v, neighbors[i].weight);  // Use directed edge
                    dfsVisit(g, result, visited, v);
                }
            }
        }
    };
    
    DFSHelper::dfsVisit(g, result, visited, source);
    delete[] visited;
    return result;
}

Graph Algorithms::dijkstra(const Graph& g, int source) {
    int n = g.getNumVertices();
    Graph result(n);
    int* dist = new int[n];
    bool* visited = new bool[n]();
    
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;
    
    PriorityQueue pq(n);
    pq.insert(source, 0);
    
    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        if (visited[u]) continue;
        visited[u] = true;
        
        const Neighbor* neighbors = g.getNeighbors(u);
        int neighborCount = g.getNeighborCount(u);
        
        for (int i = 0; i < neighborCount; i++) {
            int v = neighbors[i].vertex;
            int weight = neighbors[i].weight;
            
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                result.addDirectedEdge(u, v, weight);  // Use directed edge
                pq.insert(v, dist[v]);
            }
        }
    }
    
    delete[] dist;
    delete[] visited;
    return result;
}

Graph Algorithms::prim(const Graph& g) {
    int n = g.getNumVertices();
    Graph result(n);
    int* key = new int[n];
    int* parent = new int[n];
    bool* visited = new bool[n]();
    
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0;
    
    PriorityQueue pq(n);
    pq.insert(0, 0);
    
    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        if (visited[u]) continue;
        visited[u] = true;
        
        if (parent[u] != -1) {
            result.addEdge(parent[u], u, key[u]);
        }
        
        const Neighbor* neighbors = g.getNeighbors(u);
        int neighborCount = g.getNeighborCount(u);
        
        for (int i = 0; i < neighborCount; i++) {
            int v = neighbors[i].vertex;
            int weight = neighbors[i].weight;
            
            if (!visited[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.insert(v, key[v]);
            }
        }
    }
    
    delete[] key;
    delete[] parent;
    delete[] visited;
    return result;
}

Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getNumVertices();
    Graph result(n);
    UnionFind uf(n);
    
    // Create edge list
    struct Edge {
        int u, v, weight;
        Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };
    
    // Collect all edges
    Edge** edges = new Edge*[n * n];
    int edgeCount = 0;
    
    for (int u = 0; u < n; u++) {
        const Neighbor* neighbors = g.getNeighbors(u);
        int neighborCount = g.getNeighborCount(u);
        
        for (int i = 0; i < neighborCount; i++) {
            int v = neighbors[i].vertex;
            if (u < v) {  // Avoid duplicate edges
                edges[edgeCount] = new Edge(u, v, neighbors[i].weight);
                edgeCount++;
            }
        }
    }
    
    // Sort edges
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j]->weight > edges[j + 1]->weight) {
                std::swap(edges[j], edges[j + 1]);
            }
        }
    }
    
    // Process edges
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i]->u;
        int v = edges[i]->v;
        
        if (uf.find(u) != uf.find(v)) {
            result.addEdge(u, v, edges[i]->weight);
            uf.unite(u, v);
        }
    }
    
    // Clean up
    for (int i = 0; i < edgeCount; i++) {
        delete edges[i];
    }
    delete[] edges;
    
    return result;
}

} // namespace graph 