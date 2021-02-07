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
void min_heapify(value_t a[], size_t heap_size, size_t i) {
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
    value_t temp = a[i];
    a[i] = a[smallest];
    a[smallest] = temp;
    min_heapify(a, heap_size, smallest);
  }
}

// FUNCTION IMPLEMENTATIONS
// ========================

void min_heap_build(value_t a[], size_t length) {
  for (int i = length / 2; 0 <= i; --i) {
    min_heapify(a, length, i);
  }
}

void min_heapsort(value_t a[], size_t length) {
  min_heap_build(a, length);
  for (int i = length; 2 <= i; --i) {
    value_t temp = a[i - 1];
    a[i - 1] = a[0];
    a[0] = temp;
    length--;
    min_heapify(a, length, 0);
  }
}

// Helper function for inserting a new node
// Precondition: `key` is smaller than the value at a[i].
void heap_decrease_key(value_t a[], size_t i, value_t key) {
  assert(a[i] >= key);
  a[i] = key;
  while (i > 0 && a[parent(i)] > a[i]) {
    value_t temp = a[i];
    a[i] = a[parent(i)];
    a[parent(i)] = temp;
    i = parent(i);
  }
}

value_t min_heap_minimum(const value_t a[], size_t heap_size) { return a[0]; }

value_t min_heap_extract_min(value_t a[], size_t heap_size) {
  assert(heap_size > 0);
  value_t min = a[0];
  a[0] = a[--heap_size - 1];
  min_heapify(a, heap_size, 0);
  return min;
}

void min_heap_insert(value_t a[], size_t heap_size, value_t key) {
  a[heap_size] = MIN_HEAP_MAX_NUMBER;
  heap_decrease_key(a, heap_size, key);
}

// PRIORITY QUEUE FUNCTIONS
// ========================
priority_queue *alloc_priority_queue(size_t capacity) {
  priority_queue *p =
      (priority_queue *)malloc(sizeof(*p) + capacity * sizeof(value_t));
  if (p) {
    p->size = 0;
    p->capacity = capacity;
  }
  return p;
}

size_t priority_queue_size(const priority_queue *q) { return q->size; }

value_t priority_queue_peek_min(const priority_queue *q) {
  assert(q->size > 0);
  return min_heap_minimum(q->arr, q->size);
}

void priority_queue_pop_min(priority_queue *q) {
  min_heap_extract_min(q->arr, q->size--);
}

void priority_queue_insert(priority_queue *q, value_t key) {
  assert(q->size < q->capacity);
  min_heap_insert(q->arr, q->size++, key);
}
