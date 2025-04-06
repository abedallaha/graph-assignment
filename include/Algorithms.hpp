/*
 * Email: abedallahamodi803@gmail.com
 * has all the graph algorithms we need
 */

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <climits>  // for INT_MAX

namespace graph {

class Algorithms {
private:
    // for BFS
    struct Queue {
        int* data;
        int front;
        int rear;
        int size;
        int capacity;

        Queue(int cap);
        ~Queue();
        void enqueue(int x);
        int dequeue();
        bool isEmpty() const;
    };

    // for Dijkstra
    struct PriorityQueue {
        struct Item {
            int vertex;
            int priority;
            Item() : vertex(-1), priority(INT_MAX) {}
            Item(int v, int p) : vertex(v), priority(p) {}
        };
        Item* heap;
        int size;
        int capacity;

        PriorityQueue(int cap);
        ~PriorityQueue();
        void insert(int vertex, int priority);
        int extractMin();
        void decreaseKey(int vertex, int newPriority);
        bool isEmpty() const;
    };

    // for Kruskal
    struct UnionFind {
        int* parent;
        int* rank;
        int size;

        UnionFind(int n);
        ~UnionFind();
        int find(int x);
        void unite(int x, int y);
    };

public:
    static Graph bfs(const Graph& g, int source);
    static Graph dfs(const Graph& g, int source);
    static Graph dijkstra(const Graph& g, int source);
    static Graph prim(const Graph& g);
    static Graph kruskal(const Graph& g);
};

} // namespace graph

#endif // ALGORITHMS_HPP 