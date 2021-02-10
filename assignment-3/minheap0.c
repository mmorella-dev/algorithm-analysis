// FILE:   minheap0.c
// AUTHOR: Mae Morella
// ===================
//
// Implements the algorithms defined in minheap0.h

#include "minheap0.h"

#include <stdio.h>
#include <stdlib.h>  // for size_t
#include <assert.h>

// HEAP FUNCTIONS
// ================

// Helper functions for heap indexes
size_t left(size_t i) { return i * 2 + 1; }
size_t right(size_t i) { return i * 2 + 2; }
size_t parent(size_t i) { return (i + 1) / 2 - 1; }

// Helper function which recursively maintains the heap property
void heapify(heap_value a[], size_t heap_size, size_t i) {
  size_t l = left(i);
  size_t r = right(i);
  size_t smallest = i;
  if (l < heap_size && a[l] < a[smallest]) {
    smallest = l;
  }
  if (r < heap_size && a[r] < a[smallest]) {
    smallest = r;
  }
  if (smallest != i) {
    heap_value temp = a[i];
    a[i] = a[smallest];
    a[smallest] = temp;
    heapify(a, heap_size, smallest);
  }
}

// FUNCTION IMPLEMENTATIONS
// ========================

void heap_build(heap_value a[], size_t length) {
  for (int i = length / 2; 0 <= i; --i) {
    heapify(a, length, i);
  }
}

void heap_sort(heap_value a[], size_t length) {
  heap_build(a, length);
  for (int i = length; 2 <= i; --i) {
    heap_value temp = a[i - 1];
    a[i - 1] = a[0];
    a[0] = temp;
    length--;
    heapify(a, length, 0);
  }
}

// Helper function for inserting a new node
// Precondition: `key` is not greater than the value at a[i].
void heap_decrease_key(heap_value a[], size_t i, heap_value key) {
  // assert(lte(key, a[i]));
  a[i] = key;
  while (i > 0 && a[i] < a[parent(i)]) {
    heap_value temp = a[i];
    a[i] = a[parent(i)];
    a[parent(i)] = temp;
    i = parent(i);
  }
}

heap_value heap_minimum(const heap_value a[], size_t heap_size) { return a[0]; }

heap_value heap_extract_min(heap_value a[], size_t heap_size) {
  assert(heap_size > 0);
  heap_value min = a[0];
  a[0] = a[--heap_size - 1];
  heapify(a, heap_size, 0);
  return min;
}

void heap_insert(heap_value a[], size_t heap_size, heap_value key) {
  // a[heap_size] = HEAP_VALUE_MAX;
  heap_decrease_key(a, heap_size, key);
}
