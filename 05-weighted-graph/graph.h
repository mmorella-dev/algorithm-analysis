// GRAPH.H
// AUTHOR: Mae Morella
// ===================
// Implements elementary graph algorithms, as well as an algorithm to find
// articulation points, and Dijkstra’S algorithm for finding the shortest
// distance between two vertices
//
// This graph implementation uses a fixed number of vertices.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>  // for bool
#include <stdlib.h>   // for size_t

// VERTEX INDEX TYPE
// =================
// Represents the identifier for a vertex in a graph.
typedef int vertex_t;

// GRAPH EDGE TYPE
// ===============
// Node in adjacency matrix, representing an edge in a weighted, directed
// graph
typedef struct GraphEdge {
  // The identifier of the vertex this edge points to.
  vertex_t vertex;
  // The weight represented by this edge.
  // In a unweighted graph, this value is 1.0
  double weight;  // represents the weight of this edge
  // A link to another node in this list.
  struct GraphEdge *link;  // another node in the list
} GraphEdge;

// GRAPH TYPE
// ==========
// A fixed-size adjacency matrix.
typedef struct Graph {
  // The number of vertices in the graph
  // All vertices with indexes in [0, size) are defined.
  size_t size;
  // An array of linked lists.
  // graph[v] points to the list of edges originating from the vector v.
  GraphEdge *graph[];
} Graph;

// GRAPH CONSTRUCTION
// ==================

// Constructs a new empty graph object
// POSTCOND: size = 0; max_size = size;
//                graph is an array of pointers to linked lists
Graph *construct_graph(size_t size);

// If it doesn't already exist, creates an edge directed from v1 to v2.
// PRECOND:   v1 and v2 are less than size
// POSTCOND:  An edge points between v1 -> v2 with the given weight
void graph_add_edge(Graph *g, vertex_t v1, vertex_t v2, double weight);

// Remove all edges from the graph and free the memory used on them
void graph_disconnect_all(Graph *g);

// Destruct the graph object, and deallocate storage
void free_graph(Graph *g);

// Prints the graph
void print_graph(const Graph *g);

// Perfrom a depth-first traversal, printing each vertex
// POSTCOND: the vertices have been printed in the order they were traversed
void graph_depth_first_traversal(const Graph *g);

// Perform a depth-first traversal starting at the parameter vertex
// POSTCOND: the vertices have been printed in the order they were traversed
void dft_at_vertex(const Graph *g, vertex_t vertex);

// Finds all articulation points in the graph
// PRECOND: g is a connected graph
void graph_find_articulation_points(const Graph *g);

// Traces the distance from a source vertex to each other vertex
// PRECOND: v < g->size, dist is an array with size g->size
// POSTCOND: dist[i] now contains the distance from v to i
void graph_shortest_distance(const Graph *g, vertex_t v, double *dist);

double graph_diameter(const Graph *g);
#endif  // !GRAPH_H