// FILE:   priority_queue.h
// AUTHOR: Mae Morella
// ========================
// An ADT representing a priority queue, a variable-size data
// structure whose highest priority element can be accessed in O(1).
// The insert and pop operations execute in O(log n).

// queue_value, and the operations which determine its

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>  // for bool
#include <stdlib.h>   // for size_t

// TYPE DEFINITIONS
// ================

typedef int queue_value;  // The type stored in the queue.

// Compares the priority of two queue elements
// Returns 0 if a and b have equal priority
// Returns positive if a has greater priority than b
// Returns negative if a has less priority than b
static inline int compare_queue_values(const queue_value *a,
                                       const queue_value *b) {
  return (*a < *b) - (*a > *b);  // min-heap property.
}

// PRIORITY QUEUE DATA STRUCTURE
// =============================

// Represents a priority queue data structure of dynamic size.
// If the queue is only modified by the given functions, its internal array
// arr will maintain the min-heap property for the elements [0, size)
typedef struct priority_queue {
  size_t capacity;    // maximum num of elements
  size_t size;        // current num of elements in queue
  queue_value arr[];  // a dynamic array with indices [0, capacity)
} priority_queue;

// Creates a new priority_queue of the given capacity
// Precondition: capacity > 0
// Postcondition: the return value points to a priority_queue, or is NULL
priority_queue *alloc_priority_queue(size_t capacity);

// Returns the number of elements in a priority queue
// Equivalent to accessing q.size
size_t priority_queue_size(const priority_queue *q);

// Returns the smallest element in the queue.
// Precondition: q.size != 0 (the queue is not empty)
queue_value priority_queue_peek(const priority_queue *q);

// Removes the highest priority element in the queue.
// If the queue is empty, this function fails silently.
void priority_queue_pop(priority_queue *q);

// Adds a new element to the queue.
// Postcondition: If the queue is full, this function fails silently and the
// queue remains unchanged.
void priority_queue_insert(priority_queue *q, queue_value key);

// HEAP SORT FUNCTION
// ==================

// Sorts an array in place, using heaps
// Precondition:  a[] is an unordered array
// Postcondition: The elements in range a[0, size) are sorted with their keys in
//           ascending order
void heap_sort(queue_value a[], size_t size);

// TESTING METHODS
// ===============

bool _prq_is_heap(const queue_value a[], size_t size, size_t i);

bool _prq_is_sorted(const queue_value a[], size_t size);

#endif /* PRIORITY_QUEUE_H */
