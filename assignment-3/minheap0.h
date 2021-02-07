// FILE:   minheap0.h
// AUTHOR: Mae Morella
// ===================
// Defines functions for creating and manipulating min-heaps.
// A min-heap is defined as a binary tree such that each node is smaller than
// its children. An array A contains a min-heap if for any index i in [0,
// A.size), the child elements at A[i*2+1] and A[i*2+2] are greater than A[i],
// or do not exist.

#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for size_t

typedef int value_t;                 // the number type used inside the queue
#define MIN_HEAP_MAX_NUMBER INT_MAX  // the largest number for the above type

// DESCENDING HEAP SORT FUNCTION
// =============================

// Sorts an array in place using a min-heap.
// Precondition: `a` points to an unordered array
// Postcondition: `a` is sorted in descending order.
void min_heapsort(value_t a[], size_t length);

// MINIMUM HEAP FUNCTIONS
// ======================
// Algorithms described in the textbook for creating and manipulating minimum
// heaps. used here to implement the priority queue and heap sort functions.

// Produces a minimum-heap from an unordered input array.
// Precondition: `a` is an unsorted array
// Postcondition: a[0, size) are now in min-heap order.
void min_heap_build(value_t a[], size_t length);

// Returns the smallest value in the heap.
// Precondition: `a` is a min-heap with at least one element
value_t min_heap_minimum(const value_t a[], size_t heap_size);

// Extracts the smallest value in a heap.
// Precondition: a[0...size) is a min-heap
// Postcondition: heap_size -= 1
value_t min_heap_extract_min(value_t a[], size_t heap_size);

// Inserts a new element into a min heap
// Precondition:  a[0...size) is a min heap. a is defined for a[0...size+1)
// Postcondition: heap_size is now increased by 1
void min_heap_insert(value_t a[], size_t heap_size, value_t key);

// Assigns the value at a[i] to `key` while maintaining the min-heap property.
// Precondition: `key` is smaller than the previous value at a[i].
void heap_decrease_key(value_t a[], size_t i, value_t key);

// Precondition: If they exist, the binary trees rooted at a[2i+1] and a[2i+2]
// are min-heaps. heap_size < i.
// Postcondition: The binary tree rooted at a[i] is a min-heap.
void min_heapify(value_t a[], size_t heap_size, size_t i);
