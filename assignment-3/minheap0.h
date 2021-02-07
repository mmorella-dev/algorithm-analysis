// FILE: minheap0.h
// AUTHOR: Mae Morella
//
// Explain here
// ============================================================================

#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for size_t

typedef int value_t;                 // the number type used inside the queue
#define MIN_HEAP_MAX_NUMBER INT_MAX  // the largest number for the above type

// PRIORITY QUEUE FUNCTIONS
// ========================

// Represents a minimum priority queue data structure of dynamic size. Maintains
// the covariant that the internal array is in min-heap order, and that
// heap_size is tracked.
typedef struct priority_queue {
  size_t capacity;  // the maximum number of elements the queue can hold
  size_t size;      // the current number of elements in the queue
  value_t arr[];    // an array of size `capacity`. [0, size)
} priority_queue;

// Creates a new priority_queue of the given capacity
// Postcondition: the priority_queue
// If allocation, prints an error message and returns a NULL ptr.
priority_queue *alloc_priority_queue(size_t capacity);

// Returns the number of elements in a priority queue
size_t priority_queue_size(priority_queue *q);

//
void priority_queue_pop_min(priority_queue *q);

void priority_queue_insert(priority_queue *q, value_t key);

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

// Returns the smallest value in the heap.
// Precondition: `a` is a min-heap with at least one element
value_t heap_minimum(value_t a[], size_t heap_size);

// Extracts the smallest value in a heap.
// Precondition: a[0...size) is a min-heap
// Postcondition: heap_size -= 1
value_t heap_extract_min(value_t a[], size_t heap_size);

// Inserts a new element into a min heap
// Precondition:  a[0...size) is a min heap. a is defined for a[0...size+1)
// Postcondition: heap_size is now increased by 1
void heap_insert(value_t a[], size_t heap_size, value_t key);
