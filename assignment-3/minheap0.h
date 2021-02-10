// FILE:   minheap0.h
// AUTHOR: Mae Morella
// ===================
// Defines functions for creating and manipulating min-heaps.
// A min-heap is defined as a binary tree such that each node is smaller than
// its children. An array A contains a min-heap if for any index i in [0,
// A.size), the child elements at A[i*2+1] and A[i*2+2] are greater than A[i],
// or do not exist.

#ifndef MINHEAP0_H
#define MINHEAP0_H

#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for size_t
#include <math.h>

typedef int heap_value;       // the type used inside the heap

// DESCENDING HEAP SORT FUNCTION
// =============================

// Sorts an array in place using a min-heap.
// Precondition: `a` points to an unordered array
// Postcondition: `a` is sorted in descending order.
void heap_sort(heap_value a[], size_t length);

// MINIMUM HEAP FUNCTIONS
// ======================
// Algorithms described in the textbook for creating and manipulating minimum
// heaps. used here to implement the priority queue and heap sort functions.

// Produces a minimum-heap from an unordered input array.
// Precondition: `a` is an unsorted array
// Postcondition: a[0, size) are now in min-heap order.
void heap_build(heap_value a[], size_t length);

// Returns the smallest value in the heap.
// Precondition: `a` is a min-heap with at least one element
heap_value heap_minimum(const heap_value a[], size_t heap_size);

// Extracts the smallest value in a heap.
// Precondition: a[0...size) is a min-heap
// Postcondition: heap_size -= 1
heap_value heap_extract_min(heap_value a[], size_t heap_size);

// Inserts a new element into a min heap
// Precondition:  a[0...size) is a min heap. a is defined for a[0...size+1)
// Postcondition: heap_size is now increased by 1
void heap_insert(heap_value a[], size_t heap_size, heap_value key);

// Assigns the value at a[i] to `key` while maintaining the min-heap property.
// Precondition: `key` is smaller than the previous value at a[i].
void heap_decrease_key(heap_value a[], size_t i, heap_value key);

// Precondition: If they exist, the binary trees rooted at a[2i+1] and a[2i+2]
// are min-heaps. heap_size < i.
// Postcondition: The binary tree rooted at a[i] is a min-heap.
void heapify(heap_value a[], size_t heap_size, size_t i);

#endif /* MINHEAP0_H */
