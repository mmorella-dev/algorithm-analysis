// FILE:   priority_queue.h
// AUTHOR: Mae Morella
// ========================

// An ADT representing a priority queue, a variable-size data
// structure whose smallest element can be accessed in O(1). The insert and
// pop_min operations execute in O(log n).

// queue_value_t, and the operations which determine its 

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdlib.h>  // for size_t

#include "minheap0.h"  // for heap_value_t

typedef heap_value_t queue_value_t;  // The numeric type stored in the queue.

// PRIORITY QUEUE DATA STRUCTURE
// =============================

// Represents a priority queue data structure of dynamic size.
// If the queue is only modified by the given functions, its internal array arr
// will maintain the min-heap property for the elements [0, size)
typedef struct priority_queue {
  size_t capacity;      // the maximum number of elements the queue can hold
  size_t size;          // the current number of elements in the queue
  queue_value_t arr[];  // an array of size `capacity`. [0, size)
} priority_queue;

// Creates a new priority_queue of the given capacity
// Precondition: capacity > 0
// Postcondition: the return value points to a priority_queue, or is NULL
priority_queue *alloc_priority_queue(size_t capacity);

// Returns the smallest element in the queue.
// Precondition: q.size != 0 (the queue is not empty)
queue_value_t priority_queue_peek(const priority_queue *q);

// Returns the number of elements in a priority queue
// Equivalent to accessing q.size
size_t priority_queue_size(const priority_queue *q);

// Removes the smallest element in the queue.
// Postcondition: queue size is smaller by 1.
void priority_queue_pop(priority_queue *q);

// Adds a new element to the queue.
// Precondition: q.size != q.capacity (the queue is not full)
void priority_queue_insert(priority_queue *q, queue_value_t key);

#endif /* PRIORITY_QUEUE_H */
