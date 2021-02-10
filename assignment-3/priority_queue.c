// FILE:   priority_queue.c
// AUTHOR: Mae Morella
// ========================

#include "priority_queue.h"

#include <assert.h>  // for assert
#include <stddef.h>  // for size_t

#include "minheap0.h"

// PRIORITY QUEUE FUNCTIONS
// ========================
priority_queue *alloc_priority_queue(size_t capacity) {
  priority_queue *p =
      (priority_queue *)malloc(sizeof(*p) + capacity * sizeof(queue_value_t));
  if (p) {
    p->size = 0;
    p->capacity = capacity;
  }
  return p;
}

size_t priority_queue_size(const priority_queue *q) { return q->size; }

queue_value_t priority_queue_peek(const priority_queue *q) {
  assert(q->size > 0);
  return heap_minimum(q->arr, q->size);
}

void priority_queue_pop(priority_queue *q) {
  heap_extract_min(q->arr, q->size--);
}

void priority_queue_insert(priority_queue *q, queue_value_t key) {
  assert(q->size < q->capacity);
  heap_insert(q->arr, q->size++, key);
}
