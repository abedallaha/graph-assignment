# Graph Implementation with Adjacency List

This project implements an undirected graph using an adjacency list representation, along with various graph algorithms including BFS, DFS, Dijkstra's shortest path, Prim's minimum spanning tree, and Kruskal's minimum spanning tree.

## Project Structure

```
.
├── include/
│   ├── Graph.hpp       # Graph class declaration
│   └── Algorithms.hpp  # Algorithms class declaration
├── src/
│   ├── Graph.cpp      # Graph class implementation
│   ├── Algorithms.cpp # Algorithms class implementation
│   └── main.cpp       # Demonstration program
├── test/
│   └── test_graph.cpp # Unit tests
└── Makefile          # Build configuration
```

## Implementation Details

### Graph Class
- Uses adjacency list representation
- Each vertex maintains a list of neighbors with edge weights
- Supports adding and removing edges
- Implements proper memory management
- No STL usage (custom dynamic arrays)

### Algorithms Class
Implements the following graph algorithms:
1. Breadth-First Search (BFS)
2. Depth-First Search (DFS)
3. Dijkstra's Shortest Path
4. Prim's Minimum Spanning Tree
5. Kruskal's Minimum Spanning Tree

### Helper Data Structures
Custom implementations of:
- Queue (for BFS)
- Priority Queue (for Dijkstra and Prim)
- Union-Find (for Kruskal)

## Building and Testing

The project uses a Makefile with the following commands:

- `make` - Build all executables
- `make main` - Build and run the demonstration program
- `make test` - Build and run unit tests
- `make valgrind` - Check for memory leaks
- `make clean` - Clean build files

## Requirements

- C++17 compatible compiler (clang++ recommended)
- doctest for unit testing
- valgrind for memory leak detection

## Memory Management

- All memory is properly managed using new/delete
- No memory leaks (verified with valgrind)
- Proper cleanup in destructors

## Error Handling

- Input validation for all operations
- Appropriate exception throwing for invalid operations
- Edge cases handled properly

## Testing

Unit tests cover:
- Basic graph operations
- Edge cases and error conditions
- All implemented algorithms
- Memory management

