// FILE:   priority_queue.c
// AUTHOR: Mae Morella
// ========================

#include "priority_queue.h"

#include <assert.h>  // for assert
#include <stddef.h>  // for size_t

#include "minheap0.h"

static inline int queue_lt(queue_value a, queue_value b) {
  return queue_compare(a, b) > 0;
}
static inline int queue_lte(queue_value a, queue_value b) {
  return queue_compare(a, b) >= 0;
}

// PRECOND: If they exist, the binary trees rooted at arr[2i+1] and arr[2i+2]
// are min-heaps or leaves. and heap_size > i.
// POSTCOND: The binary tree rooted at arr[i] is a min-heap.
void priority_heapify(priority_queue *q, size_t i) {
  size_t l = 2 * i + 1;
  size_t r = 2 * i + 2;
  size_t smallest = i;
  if (l < q->size && queue_lt(q->arr[l], q->arr[smallest])) {
    smallest = l;
  }
  if (r < q->size && queue_lt(q->arr[r], q->arr[smallest])) {
    smallest = r;
  }
  if (smallest != i) {
    queue_value temp = q->arr[i];
    q->arr[i] = q->arr[smallest];
    q->arr[smallest] = temp;
    priority_heapify(q, smallest);
  }
}

// PRIORITY QUEUE FUNCTIONS
// ========================
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
  assert(q->size > 0);
  return q->arr[0];
}

void priority_queue_pop(priority_queue *q) {
  heap_extract_min(q->arr, q->size--);
}

void priority_queue_insert(priority_queue *q, queue_value key) {
  size_t i = q->size;
  q->arr[i] = key;
  while (i > 0 && queue_lt(q->arr[i], q->arr[(i + 1) / 2 - 1])) {
    heap_value temp = q->arr[i];
    q->arr[i] = q->arr[(i + 1) / 2 - 1];
    q->arr[(i + 1) / 2 - 1] = temp;
    i = (i + 1) / 2 - 1;
  }
  ++q->size;
}
