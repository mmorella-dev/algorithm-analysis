// FILE: minheap0.c
// AUTHOR: Mae Morella
//
// Implements the algorithms defined in minheap0.h
// ============================================================================

#include "minheap0.h"

#include <stdio.h>
#include <stdlib.h>  // for size_t

// HEAP FUNCTIONS
// ================

static inline size_t left(size_t i) { return i << 1; }
static inline size_t right(size_t i) { return (i << 1) + 1; }
static inline size_t parent(size_t i) { return (i >> 1); }

// Helper function which recursively maintains the heap property
void min_heapify(value_t a[], size_t heap_size, size_t i) {
  size_t l = (i << 1) + 1;
  size_t r = (i << 1) + 2;
  size_t smallest = i;
  if (l < heap_size && a[l] < a[smallest]) {
    smallest = l;
  }
  if (r < heap_size && a[r] < a[smallest]) {
    smallest = r;
  }
  if (smallest != i) {
    value_t temp = a[i];
    a[i] = a[smallest];
    a[smallest] = temp;
    min_heapify(a, heap_size, smallest);
  }
}

// FUNCTION IMPLEMENTATIONS
// ========================

void build_min_heap(value_t a[], size_t length) {
  for (int i = length / 2; 0 <= i; --i) {
    min_heapify(a, length, i);
  }
}

void min_heapsort(value_t a[], size_t length) {
  build_min_heap(a, length);
  for (int i = length; 2 <= i; --i) {
    value_t temp = a[i - 1];
    a[i - 1] = a[0];
    a[0] = temp;
    length--;
    min_heapify(a, length, 0);
  }
}

// Helper function for inserting a new node
void heap_decrease_key(value_t a[], size_t i, value_t key) {
  if (key > a[i]) {
    fprintf(stderr, "Error: new key is greater than current key");
    return;
  }
  a[i] = key;
  while (i > 0 && a[(i + 1) / 2 - 1] > a[i]) {
    size_t parent = (i + 1) / 2 - 1;
    value_t temp = a[i];
    a[i] = a[parent];
    a[parent] = temp;
    i = parent;
  }
}

value_t heap_minimum(value_t a[], size_t heap_size) { return a[0]; }

value_t heap_extract_min(value_t a[], size_t heap_size) {
  if (heap_size < 1) {
    fprintf(stderr, "Error: heap underflow. Exiting...\n");
    exit(EXIT_FAILURE);
  }
  value_t min = a[0];
  a[0] = a[--heap_size - 1];
  min_heapify(a, heap_size, 0);
  return min;
}

void heap_insert(value_t a[], size_t heap_size, value_t key) {
  a[heap_size] = MIN_HEAP_MAX_NUMBER;
  heap_decrease_key(a, heap_size, key);
}
