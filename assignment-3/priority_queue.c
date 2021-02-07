// FILE:   priority_queue.c
// AUTHOR: Mae Morella
// ========================

#include "minheap0.h"

#include "priority_queue.h"

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