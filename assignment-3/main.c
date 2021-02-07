#include <stddef.h>
#include <stdio.h>

#include "minheap0.h"
// #include "priorityqueue.h"

void print_array(int a[], size_t size) {
  for (int i = 0; i < size; i++) printf("%d ", a[i]);
  printf("\n");
}

int main() {
  int nums[] = {8, 6, 7, 5, 3, 0, 9, 80, 60, 70, 50, 30, 0, 90};
  const size_t nums_size = sizeof(nums) / sizeof(nums[0]);
  print_array(nums, nums_size);

  // build_min_heap(nums, nums_size);
  min_heapsort(nums, nums_size);
  print_array(nums, nums_size);

  build_min_heap(nums, nums_size);
  int heap_size = nums_size;
  while (--heap_size > 0) {
    printf("%d\n", heap_extract_min(nums, heap_size));
  }
}
