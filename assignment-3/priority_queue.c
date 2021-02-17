// FILE:   priority_queue.c
// AUTHOR: Mae Morella
// ========================

#include "priority_queue.h"

#include <assert.h>   // for assert
#include <stdbool.h>  // for bool
#include <stddef.h>   // for size_t

// HELPER FUNCTIONS
// ================

// For the node at a[i], returns the index of the right child.
static inline size_t _prq_left(size_t i) { return i * 2 + 1; }

// For the node at a[i], returns the index of the right child
static inline size_t _prq_right(size_t i) { return i * 2 + 2; }

// For the node at a[i], returns the index of the parent node
static inline size_t _prq_parent(size_t i) { return (i + 1) / 2 - 1; }

// Returns whether a has greater priority than b
static inline bool _prq_gt(queue_value a, queue_value b) {
  return compare_queue_values(&a, &b) > 0;
}

// Returns whether a's priority is greater or equal to b's
static inline bool _prq_gte(queue_value a, queue_value b) {
  return compare_queue_values(&a, &b) >= 0;
}

// HEAP ALGORITHM IMPLEMENTATIONS
// ==============================

// Recursively maintains the heap property
// PRECOND: The binary trees rooted at a[left(i)] and a[right(i)] are heaps or
//    nonexistent.
// POSTCOND:  The binary tree rooted at a[i] is correctly ordered.
void _prq_heapify(queue_value a[], size_t size, size_t i) {
  size_t l = _prq_left(i);
  size_t r = _prq_right(i);
  assert(_prq_is_heap(a, l, size));
  assert(_prq_is_heap(a, r, size));
  size_t largest = i;
  if (l < size && _prq_gt(a[l], a[largest])) {
    largest = l;
  }
  if (r < size && _prq_gt(a[r], a[largest])) {
    largest = r;
  }
  if (largest != i) {
    queue_value temp = a[i];
    a[i] = a[largest];
    a[largest] = temp;
    _prq_heapify(a, size, largest);
  }
  assert(_prq_is_heap(a, size, i));  // verify postcondition
}

// Builds a heap
// PRECOND:  a[] is an unordered array
// POSTCOND: The elements in range a[0, size) are now a heap.
void _prq_heap_build(queue_value a[], size_t size) {
  for (int i = (size - 1) / 2; 0 <= i; --i) {
    _prq_heapify(a, size, i);
  }
  assert(_prq_is_heap(a, size, 0));  // verify postcondition
}

// Sorts an array using heaps
// PRECOND:  a[] is an unordered array
// POSTCOND: The elements in range a[0, size) are sorted with their keys in
//           ascending order
void heap_sort(queue_value a[], size_t size) {
  _prq_heap_build(a, size);
  for (int i = size; 2 <= i; --i) {
    queue_value temp = a[i - 1];
    a[i - 1] = a[0];
    a[0] = temp;
    size--;
    _prq_heapify(a, size, 0);
  }
  assert(_prq_is_sorted(a, size));  // verify postcondition
}

// Returns the element with the largest key
// PRECOND: size != 0
queue_value _prq_heap_peek(const queue_value a[], size_t size) {
  assert(size != 0);  // verify precondition
  return a[0];
}

// Removes the element with the largest key
// PRECOND:  size != 0
// POSTCOND: size = size - 1
queue_value _prq_heap_extract(queue_value a[], size_t *size) {
  assert(*size > 0);  // verify precondition
  queue_value min = a[0];
  --(*size);
  a[0] = a[*size - 1];
  _prq_heapify(a, *size, 0);
  return min;
}

// Modifies the value at a[i] while maintaining heap property
// PRECOND: The binary tree rooted at a[i] is a heap, or nonexistent
// PRECOND: The key of input `k` is larger than the key of a[i]
// POSTCOND: The
void _prq_heap_change_key(queue_value a[], size_t i, queue_value k) {
  a[i] = k;
  while (i > 0 && _prq_gt(a[i], a[_prq_parent(i)])) {
    queue_value temp = a[i];
    a[i] = a[_prq_parent(i)];
    a[_prq_parent(i)] = temp;
    i = _prq_parent(i);
  }
}

void _prq_heap_insert(queue_value a[], size_t *size, queue_value key) {
  assert(_prq_is_heap(a, *size, 0));
  _prq_heap_change_key(a, *size, key);
  ++(*size);
  assert(_prq_is_heap(a, *size, 0));
}

// TESTING METHODS
// ===============

bool _prq_is_heap(const queue_value a[], size_t size, size_t i) {
  size_t l = _prq_left(i);
  size_t r = _prq_right(i);
  if (r >= size) {
    return true;
  }
  if (_prq_gte(a[i], a[l]) && _prq_gte(a[i], a[r])) {
    return _prq_is_heap(a, size, l) && _prq_is_heap(a, size, r);
  }
  return false;
}

bool _prq_is_sorted(const queue_value a[], size_t size) {
  for (int i = 1; i < size; i++) {
    if (!_prq_gte(a[i], a[i - 1])) {
      return false;
    }
  }
  return true;
}

// PRIORITY QUEUE PUBLIC FUNCTIONS
// ===============================

priority_queue *alloc_priority_queue(size_t capacity) {
  priority_queue *p =
      malloc(sizeof(priority_queue) + sizeof(queue_value[capacity]));
  if (p) {
    p->size = 0;
    p->capacity = capacity;
  }
  return p;
}

size_t priority_queue_size(const priority_queue *q) { return q->size; }

queue_value priority_queue_peek(const priority_queue *q) {
  return _prq_heap_peek(q->arr, q->size);
}

void priority_queue_pop(priority_queue *q) {
  if (q->size > 0) {
    _prq_heap_extract(q->arr, &q->size);
  }
}

void priority_queue_insert(priority_queue *q, queue_value v) {
  if (q->size != q->capacity) {
    _prq_heap_insert(q->arr, &q->size, v);
  }
}
