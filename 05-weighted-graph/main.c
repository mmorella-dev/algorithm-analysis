// FILE: main.c
// AUTHOR: Mae Morella

#include <stdio.h>   // ???
#include <stdlib.h>  // for EXIT_SUCCESS

#include "graph.h"

void print_distances_array(const double* dist, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%g ", dist[i]);
  }
  printf("\n");
}

int main() {
  Graph* g = construct_graph(6);  // define a graph with vertices 0 thru 5
  graph_add_edge(g, 0, 1, 10.0);  // add edge from 0 -> 1, with weight 10.0
  graph_add_edge(g, 0, 2, 10.0);
  graph_add_edge(g, 1, 3, 10.0);
  graph_add_edge(g, 1, 4, 10.0);
  graph_add_edge(g, 2, 3, 10.0);
  graph_add_edge(g, 3, 5, 10.0);
  graph_add_edge(g, 4, 5, 10.0);
  graph_add_edge(g, 5, 3, 10.0);

  printf("Calling print_graph...\n");
  print_graph(g);
  printf("Calling depth_first_traversal...\n");
  graph_depth_first_traversal(g);
  printf("Calling find_articulation_points...\n");
  graph_find_articulation_points(g);

  double dist[g->size];
  printf("Diameter: %g\n", graph_diameter(g));
  free_graph(g);
  return EXIT_SUCCESS;
}