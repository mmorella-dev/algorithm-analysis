// FILE:   priority_queue.h
// AUTHOR: Mae Morella
// ========================
// An ADT representing a priority queue, a variable-size data
// structure whose highest priority element can be accessed in O(1).
// The insert and pop operations execute in O(log n).

// queue_value, and the operations which determine its

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdlib.h>  // for size_t

// PRIORITY DEFINITION
// ===================

typedef int queue_value;  // The type stored in the queue.

// Returns a positive number if a has greater priority than b
// Returns a negative number if a has less priority than b
// Returns 0 if a and b have the same priority.
static inline int queue_compare(queue_value a, queue_value b) {
  return (a < b) ? 1 : (a == b) ? 0 : -1;
}

// PRIORITY QUEUE DATA STRUCTURE
// =============================

// Represents a priority queue data structure of dynamic size.
// If the queue is only modified by the given functions, its internal array arr
// will maintain the min-heap property for the elements [0, size)
typedef struct priority_queue {
  size_t capacity;    // maximum num of elements
  size_t size;        // current num of elements in queue
  queue_value arr[];  // a dynamic array with indices [0, capacity)
} priority_queue;

// Creates a new priority_queue of the given capacity
// Precondition: capacity > 0
// Postcondition: the return value points to a priority_queue, or is NULL
priority_queue *alloc_priority_queue(size_t capacity);

// Returns the smallest element in the queue.
// Precondition: q.size != 0 (the queue is not empty)
queue_value priority_queue_peek(const priority_queue *q);

// Returns the number of elements in a priority queue
// Equivalent to accessing q.size
size_t priority_queue_size(const priority_queue *q);

// Removes the highest priority element in the queue.
// Precondition: the queue
// Postcondition: queue size is smaller by 1.
void priority_queue_pop(priority_queue *q);

// Adds a new element to the queue.
// Precondition: q.size != q.capacity (the queue is not full)
void priority_queue_insert(priority_queue *q, queue_value key);

#endif /* PRIORITY_QUEUE_H */
