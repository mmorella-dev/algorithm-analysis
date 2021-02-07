// FILE: heap0.h
// AUTHOR: Mae Morella
//
// Explain here
// ============================================================================

#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for size_t

typedef int value_t;  // the number type
#define MIN_HEAP_MAX_NUMBER INT_MAX

// MINIMUM HEAP FUNCTIONS
// ======================

// Produces a minimum-heap from an unordered input array.
// Precondition: `a` is an unsorted array
// Postcondition: `a` is now in min heap order.
void build_min_heap(value_t a[], size_t length);

// Sorts an array in descending order using a min-heap.
// Precondition: `a` points to an unordered array
// Postcondition: `a` is now sorted in place.
void min_heapsort(value_t a[], size_t length);

// MIN-PRIORITY QUEUE FUNCTIONS
// ============================

// Precondition: `a` is a min-heap with at least one element
value_t heap_minimum(value_t heap[], size_t size);

// Extracts the smallest value in the heap.
// Precondition: `heap` is a min-heap with at least one element
// Postcondition: heap_size -= 1
value_t heap_extract_min(value_t heap[], size_t size);

// Inserts a new element into a min heap
// Precondition: heap[] is a min heap, with a capacity of at least size + 1
void heap_insert(value_t heap[], size_t size, value_t key);
