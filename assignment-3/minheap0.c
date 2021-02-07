// FILE: minheap0.c
// AUTHOR: Mae Morella
//
// Implements the algorithms defined in minheap0.h
// ============================================================================

#include "minheap0.h"

#include <stdio.h>
#include <stdlib.h>  // for size_t

// HELPER FUNCTIONS
// ================

static inline size_t left(size_t i) { return i << 1; }
static inline size_t right(size_t i) { return (i << 1) + 1; }
static inline size_t parent(size_t i) { return (i >> 1); }

// Helper function which recursively maintains the heap property
void min_heapify(value_t a[], size_t heap_size, size_t i) {
  size_t l = left(i);
  size_t r = right(i);
  size_t smallest = i;
  if (l <= heap_size && a[l - 1] < a[smallest - 1]) {
    smallest = l;
  }
  if (r <= heap_size && a[r - 1] < a[smallest - 1]) {
    smallest = r;
  }
  if (smallest != i) {
    value_t temp = a[i - 1];
    a[i - 1] = a[smallest - 1];
    a[smallest - 1] = temp;
    min_heapify(a, heap_size, smallest);
  }
}

// Helper function for inserting a new node
void heap_decrease_key(value_t heap[], size_t i, value_t key) {
  if (key > heap[i - 1]) {
    fprintf(stderr, "Error: new key is greater than current key");
    return;
  }
  heap[i - 1] = key;
  while (i > 1 && heap[parent(i) - 1] < heap[i - 1]) {
    value_t temp = heap[i - 1];
    heap[i - 1] = heap[parent(i) - 1];
    heap[parent(i) - 1] = temp;
    i = i / 2;
  }
}

// FUNCTION IMPLEMENTATIONS
// ========================

void build_min_heap(value_t a[], size_t length) {
  for (int i = length / 2; 1 <= i; --i) {
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
    min_heapify(a, length, 1);
  }
}

value_t heap_minimum(value_t heap[], size_t size) {
  return heap[0];
}

value_t heap_extract_min(value_t heap[], size_t size) {
  if (size < 1) {
    fprintf(stderr, "Error: heap underflow. Exiting...");
    exit(EXIT_FAILURE);
  }
  value_t min = heap[0];
  heap[0] = heap[--size - 1];
  min_heapify(heap, size, 1);
  return min;
}

void heap_insert(value_t heap[], size_t size, value_t key) {
  size++;
  heap[size - 1] = MIN_HEAP_MAX_NUMBER;
  heap_decrease_key(heap, size, key);
}
