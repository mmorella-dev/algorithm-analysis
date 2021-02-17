// FILE:   main.c
// AUTHOR: Mae Morella
// ===================

// Implements a test program for the min_heap and priority_queue data structures
// defined in minheap0.h

#include <assert.h>   // for assert
#include <stdbool.h>  // for boolean type
#include <stdio.h>    // for printf function
#include <stdlib.h>   // for size_t, rand, EXIT_SUCCESS
#include <time.h>     // for time

#include "priority_queue.h"

// Helper function to print an array
// Prints out the array elements at arr[0, size)
void print_array(queue_value arr[], size_t size) {
  for (int i = 0; i < size; i++) printf("%2d ", arr[i]);
  printf("\n");
}

int main() {
  // Initialize an unsorted array of integers:
  queue_value nums[10];
  const size_t nums_len = sizeof(nums) / sizeof(nums[0]);
  for (int i = 0; i < nums_len; i++) {
    nums[i] = rand() % 100 - 9;
  }
  printf("- Original array: ");
  print_array(nums, nums_len);

  // Test #2: The heapsorted array is in descending order:
  printf("Test #2: Calling min_heapsort...\n");
  heap_sort(nums, nums_len);
  printf("-- Result: ");
  print_array(nums, nums_len);
  assert(_prq_is_sorted(nums, nums_len));
  printf("✔️ Array is sorted.\n\n");

  // Test #3: Create a struct priority_queue.
  printf("Test #3: Calling alloc_priority_queue...\n");
  priority_queue *q_ptr = alloc_priority_queue(nums_len);
  assert(q_ptr != NULL && q_ptr->size == 0);
  printf("✔️ Priority queue allocated successfully.\n\n");

  printf("Test #4: Inserting random elements...\n");
  srand(time(NULL));
  for (int i = 0; i < q_ptr->capacity; i++) {
    assert(_prq_is_heap(q_ptr->arr, q_ptr->size, 0));
    int value = rand() % 100 - 9;
    printf("-- priority_queue_insert(%2d)... ", value);
    priority_queue_insert(q_ptr, value);
    print_array(q_ptr->arr, q_ptr->size);
    // rigorously test that arr[0, size) is a heap after every operation
  }
  assert(_prq_is_heap(q_ptr->arr, q_ptr->size, 0));
  printf("✔️ Priority queue is a heap.\n\n");

  printf("Test #5: Popping elements from queue...\n");
  while (q_ptr->size > 0) {
    assert(_prq_is_heap(q_ptr->arr, q_ptr->size, 0));
    printf("-- priority_queue_pop()... ");
    priority_queue_pop(q_ptr);
    print_array(q_ptr->arr, q_ptr->size);
    // rigorously test that arr[0, size) is a heap after every operation
  }
  assert(_prq_is_heap(q_ptr->arr, q_ptr->size, 0));
  printf("✔️ Priority queue is a heap.\n\n");

  free(q_ptr);
  return EXIT_SUCCESS;
}
