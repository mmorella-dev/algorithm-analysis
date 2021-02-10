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

#include "minheap0.h"
#include "priority_queue.h"

// Helper function to print an array
// Prints out the array elements at arr[0, size)
void print_array(heap_value_t arr[], size_t size) {
  for (int i = 0; i < size; i++) printf("%2d ", arr[i]);
  printf("\n");
}

// Helper function:
// Checks whether the given array is in heap order.
bool is_heap(heap_value_t arr[], size_t i, size_t size) {
  size_t l = 2 * i + 1;
  size_t r = 2 * i + 2;
  if (r >= size) {
    return true;
  }
  if (lte(arr[i], arr[l]) && lte(arr[i], arr[r])) {
    return is_heap(arr, l, size) && is_heap(arr, r, size);
  }
  return false;
}

// Helper function:
// Checks whether the given array is in descending order
bool is_descending(heap_value_t arr[], size_t size) {
  for (int i = 1; i < size; i++) {
    if (arr[i] > arr[i - 1]) return false;
  }
  return true;
}

int main() {
  // Initialize an unsorted array of integers:
  heap_value_t nums[] = {8, 6, 7, 5, 3, 0, 9, 80, 60, 70, 50, 30, 0, 90};
  const size_t nums_len = sizeof(nums) / sizeof(nums[0]);
  printf("- Original array: ");
  print_array(nums, nums_len);

  // Test #1: put `nums` in heap order
  printf("Test #1: Calling min_heap_build...\n");
  heap_build(nums, nums_len);
  printf(" -- Result: ");
  print_array(nums, nums_len);
  assert(is_heap(nums, 0, nums_len));
  printf("✔️ Array is in heap order.\n\n");

  // Test #2: The heapsorted array is in descending order:
  printf("Test #2: Calling min_heapsort...\n");
  heap_sort(nums, nums_len);
  printf(" -- Result: ");
  print_array(nums, nums_len);
  assert(is_descending(nums, nums_len));
  printf("✔️ Array is sorted.\n\n");

  // Test #3: Create a struct priority_queue.
  printf("Test #3: Calling alloc_priority_queue...\n");
  priority_queue *q_ptr = alloc_priority_queue(nums_len);
  assert(q_ptr != NULL && q_ptr->size == 0);
  printf("✔️ Priority queue allocated successfully.\n\n");

  printf("Test #4: Inserting random elements...\n");
  srand(time(NULL));
  for (int i = 0; i < q_ptr->capacity; i++) {
    assert(is_heap(q_ptr->arr, 0, q_ptr->size));
    int value = rand() % 100 - 9;
    printf("-- priority_queue_insert(%2d)... ", value);
    priority_queue_insert(q_ptr, value);
    print_array(q_ptr->arr, q_ptr->size);
    // rigorously test that arr[0, size) is a heap after every operation
  }
  assert(is_heap(q_ptr->arr, 0, q_ptr->size));
  printf("✔️ Priority queue is a heap.\n\n");

  printf("Test #5: Popping elements from queue...\n");
  while (q_ptr->size > 0) {
    assert(is_heap(q_ptr->arr, 0, q_ptr->size));
    printf("-- priority_queue_pop()... ");
    priority_queue_pop(q_ptr);
    print_array(q_ptr->arr, q_ptr->size);
    // rigorously test that arr[0, size) is a heap after every operation
  }
  assert(is_heap(q_ptr->arr, 0, q_ptr->size));
  printf("✔️ Priority queue is a heap.\n\n");

  return EXIT_SUCCESS;
}
