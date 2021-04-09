// FILE: graph.c
// AUTHOR: Mae Morella

#include "graph.h"

#include <math.h>    // for HUGE_VAL
#include <stdio.h>   // for printf
#include <stdlib.h>  // for EXIT_FAILURE

// ELEMENTARY GRAPH OPERATIONS
// ===========================

Graph *construct_graph(size_t size) {
  // Allocate graph struct
  Graph *g = malloc(sizeof(*g) + size * sizeof(g->graph[0]));
  if (!g) {  // Exit on malloc fail
    printf("Error: malloc failed in construct_graph(%zu)\n", size);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < size; i++) {
    g->graph[i] = NULL;
  }
  g->size = size;
  return g;
}

GraphEdge *__g_construct_edge(vertex_t v2, double weight) {
  GraphEdge *e = malloc(sizeof(*e));
  if (!e) {
    printf("Error: malloc failed in __g_construct_edge\n");
    exit(EXIT_FAILURE);
  }
  e->vertex = v2;
  e->link = NULL;
  e->weight = weight;
  return e;
}

void graph_add_edge(Graph *g, vertex_t v1, vertex_t v2, double weight) {
  GraphEdge *e = __g_construct_edge(v2, weight);
  if (g->graph[v1] == NULL) {
    g->graph[v1] = e;
    return;
  }
  GraphEdge *cur = g->graph[v1];
  // Get the last node in the linked list
  while (cur->link != NULL) {
    // Check if edge already exists
    if (cur->vertex == v2) {
      cur->weight = weight;  // If so, update weight and stop.
      return;
    }
    // Otherwise, keep searching
    cur = cur->link;
  }
  cur->link = e;
}

void graph_remove_edge(Graph *g, vertex_t v1, vertex_t v2) {
  GraphEdge *cur = g->graph[v1];
  if (cur == NULL) {
    return;
  }
  if (cur->vertex == v2) {
    g->graph[v1] = cur->link;
    free(cur);
    return;
  }
  // Get the last node in the linked list
  while (cur->link != NULL) {
    // Check if edge already exists
    if (cur->link->vertex == v2) {
      GraphEdge *temp = cur->link;
      cur->link = temp->link;
      free(temp);
      return;
    }
    // Otherwise, keep searching
    cur = cur->link;
  }
}

void graph_disconnect_all(Graph *g) {
  GraphEdge **arr = g->graph;
  for (int i = 0; i < g->size; i++) {
    while (arr[i] != NULL) {
      GraphEdge *temp = arr[i];
      arr[i] = arr[i]->link;
      free(temp);
    }
  }
}

void free_graph(Graph *g) {
  // Free every pointer in the adjacency list
  graph_disconnect_all(g);
  // Free the graph, including the flexible array.
  free(g);
}

void print_graph(const Graph *g) {
  GraphEdge *const *arr = g->graph;
  for (int i = 0; i < g->size; i++) {
    // Print index, representing the first node
    printf("[%d] -> ", i);
    // Iterate over adjacency list
    const GraphEdge *cur = arr[i];
    while (cur != NULL) {
      printf("%d", cur->vertex);
      if (cur->link) {
        printf(", ");
      }
      cur = cur->link;
    }
    printf("\n");
  }
}

// GRAPH DEPTH FIRST TRAVERSAL
// ===========================

// Performs a depth-first traversal starting at the given vertex
// Visited is an array of g->size elements
void __g_dft(const Graph *g, vertex_t v, bool *visited) {
  printf("%d", v);
  visited[v] = true;
  for (GraphEdge *cur = g->graph[v]; cur != NULL; cur = cur->link) {
    if (!visited[cur->vertex]) {
      printf(" -> ");
      __g_dft(g, cur->vertex, visited);
    }
  }
}

void graph_depth_first_traversal(const Graph *g) {
  bool *visited = calloc(g->size, sizeof(*visited));
  for (int i = 0; i < g->size; i++) {
    if (!visited[i]) {
      __g_dft(g, i, visited);
      printf("\t");
    }
  }
  printf("\n");
  free(visited);
}

void dft_at_vertex(const Graph *g, vertex_t vertex) {
  bool *visited = calloc(g->size, sizeof(*visited));
  __g_dft(g, vertex, visited);
  printf("\n");
  free(visited);
}

// ARTICULATION POINT ALGORITHM
// ============================

// Determines whether the vertex v is a root
bool __g_is_root_node(const Graph *g, vertex_t v) {
  for (int i = 0; i < g->size; i++) {
      for (GraphEdge *c2 = g->graph[v]; c2; c2 = c2->link) {
        if (c2->vertex == v) {
          return false;
        }
      }
  }
  return true;
}

// Recursive function which finds articulation points in a graph
// PRECOND: depth[], low[], int[] are all arrays with g->size elements
void __g_articulation(const Graph *g, vertex_t v, int d, bool *visited,
                      int *low, int *depth, bool *pts) {
  depth[v] = d;
  low[v] = d;
  visited[v] = true;
  for (GraphEdge *cur = g->graph[v]; cur; cur = cur->link) {
    int k = cur->vertex;
    if (visited[cur->vertex] == false) {
      __g_articulation(g, cur->vertex, d + 1, visited, low, depth, pts);
    }
    low[v] = low[v] < low[k] ? low[v] : low[k];
    if (low[k] >= depth[v]) {
      // TODO: check if g is not a root node

      // Else:
      if (!__g_is_root_node(g, v) || g->graph[v] && g->graph[v]->link) {
        pts[v] = true;
      }
    }
  }
}

void graph_find_articulation_points(const Graph *g) {
  // Allocate arrays
  bool pts[g->size];
  bool visited[g->size];
  int low[g->size], depth[g->size];
  // Call recursive function
  __g_articulation(g, 0, 0, visited, low, depth, pts);
  printf("Articulation points: ");
  for (int i = 0; i < g->size; i++) {
    if (pts[i]) printf("%d ", i);
  }
  printf("\n");
}

// VRISKA'S SHORTEST PATH ALGORITHM
// ================================

// From the set of vectors not yet in spt, returns the one with
// the smallest distance value.
int __pick_min_distance_vertex(const Graph *g, const double *dist,
                               const bool *spt) {
  // Initialize min value
  double min = HUGE_VAL;
  int min_index;

  for (int i = 0; i < g->size; i++) {
    if (!spt[i] && dist[i] <= min) {
      min = dist[i];
      min_index = i;
    }
  }
  return min_index;
}

void graph_shortest_distance(const Graph *g, vertex_t v, double *dist) {
  bool spt[g->size];
  // Initialize dist[] array
  for (int i = 0; i < g->size; i++) {
    dist[i] = HUGE_VAL;  // infinity
  }
  dist[v] = 0;

  for (int i = 0; i < g->size; i++) {
    int u = __pick_min_distance_vertex(g, dist, spt);
    spt[u] = true;
    for (GraphEdge *cur = g->graph[u]; cur; cur = cur->link) {
      vertex_t v = cur->vertex;
      double d = dist[u] + cur->weight;
      if (!spt[v] && dist[u] != HUGE_VAL && d < dist[v]) {
        dist[v] = d;
      }
    }
  }
}

// Finds the largest of the shortest-paths.
double graph_diameter(const Graph *g) {
  double largest = 0.0;
  double dist[g->size];
  for (vertex_t v = 0; v < g->size; v++) {
    graph_shortest_distance(g, v, dist);
    printf("Dists from v #%d: ", v);
    for (int i = 0; i < g->size; i++) {
      printf("%g ", dist[i]);
      if (dist[i] != HUGE_VAL && dist[i] > largest) largest = dist[i];
    }
    printf("\n");
  }
  return largest;
}