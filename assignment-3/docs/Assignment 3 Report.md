# Assignment 3: Priority Queue

KSU College of Computing and Software Engineering<br>
CS 4306 - Algorithm Analysis

Mae Morella ([mmorella@students.kennesaw](mailto:mmorella@students.kennesaw))
Feb 12, 2021

## Problem Statement

1. Implement a priority queue using a heap data structure, including the **Heapsort(A)**, **Heapify(A, i)** and **Heap-Extract-Min(A)** algorithms shown in Chapter 6 of the Cormen, Leiserson, Rivest & Stein textbook.
2. Analyze the time complexity of the heapsort algorithm.

## Algorithms

### Definining the types

#### The priority queue object

The textbook defines a heap as an array object $A$ with properties $A.length$ and $A.heap\_size$. In the C language, defining such an object is most easily done using a structure:

```c
struct priority_queue {
  size_t capacity;      // maximum num of elements
  size_t size;          // current num of elements in queue
  queue_value arr[];    // a dynamic array with indices [0, capacity)
}
```

#### Queue element type

```c
typedef int queue_value; // the type stored in the queue
```

Note the use of the custom type `queue_value`. In C, creating generic data structures is not very easy, but I wanted to create an implementation which could contain any object, at least theoretically.

The implementation is currently defined to use integers, but this can easily be changed to any type just by modifying this part of the code, and the next.

#### Queue comparison function

To support ordering elements based on any property (not just the `>` and `<` operators on numbers), I also declared an inline function for comparing the priority of two elements. Because I'm implementing a **minimum-heap**, the lesser of two integers gets "higher" priority. If this property were reversed, the implementation would become a max-heap.

```c
// Returns a positive number if a has greater priority than b
// Returns a negative number if a has less priority than b
// Returns 0 if a and b have the same priority.
static inline int queue_compare(queue_value a, queue_value b) {
  return (a < b) ? 1 : (a == b) ? 0 : -1;
}
```

From the pseudocode, comparisons like $A[i] > A[\text{Left}(i)]$ will be implemented as something like `queue_compare(A[i], A[left(i)]) < 0`.

In a min-heap, `comp(a, b) < 0` means "a is greater than b" and thus "a has higher priority than b" and belongs first in the array. It's easy to get these comparisons confused, so the test program (shown later) is very important to making sure the algorithms are actually doing what it's supposed to. In the actual implementation I created more inline functions to make such comparisons more readable.

#### Arrays starting at 0, not 1

I should also note that while the textbook defines $A$ as being indexed starting with one, arrays in C are indexed from zero. Therefore, any time the pseudocode asks for $\text{Left}(i) \rightarrow 2i$, I use `2 * i + 1`, and $\text{Right}(i) \rightarrow$ becomes `2 * i + 2`.

With the above definitions, it should be fairly trivial to begin translating pseudocode into C functions.

### 1: $\text{Heapify}(A, i)$

```c
// PRECOND: The nodes at arr[2i+1] and a[2i+2], if they exist, are min-heaps.
// PRECOND: heap_size > i.
// POSTCOND: The binary tree rooted at a[i] is a min-heap.
void priority_heapify(priority_queue *q, size_t i) {
  // Find the smallest node, between the current node and its children
  size_t smallest = i;
  size_t l = 2 * i + 1;
  if (l < q->size && queue_lt(q->arr[l], q->arr[smallest]))
    smallest = l;
  size_t r = 2 * i + 2;
  if (r < q->size && queue_lt(q->arr[r], q->arr[smallest]))
    smallest = r;
  // If a[i] is not smaller than its children, swap and recurse
  if (smallest != i) {
    queue_value temp = q->arr[i];
    q->arr[i] = q->arr[smallest];
    q->arr[smallest] = temp;
    priority_heapify(q, smallest);
  }
}
```

###

## Appendices

### Appendix A: Screenshots of execution

![](scr-c.png)

### Output

```sh
$ ./a.out

-- Original array:  8  6  7  5  3  0  9 80 60 70 50 30  0 90
Test #1: Calling min_heap_build...
-- Result:  0  3  0  5  6  7  9 80 60 70 50 30  8 90
✔️ Array is in heap order.

Test #2: Calling min_heapsort...
-- Result: 90 80 70 60 50 30  9  8  7  6  5  3  0  0
✔️ Array is sorted.

Test #3: Calling alloc_priority_queue...
✔️ Priority queue allocated successfully.

Test #4: Inserting random elements...
-- priority_queue_insert(65)... 65
-- priority_queue_insert(38)... 38 65
-- priority_queue_insert(24)... 24 65 38
-- priority_queue_insert(78)... 24 65 38 78
-- priority_queue_insert(86)... 24 65 38 78 86
-- priority_queue_insert(14)... 14 65 24 78 86 38
-- priority_queue_insert(55)... 14 65 24 78 86 38 55
-- priority_queue_insert(39)... 14 39 24 65 86 38 55 78
-- priority_queue_insert(76)... 14 39 24 65 86 38 55 78 76
-- priority_queue_insert(66)... 14 39 24 65 66 38 55 78 76 86
-- priority_queue_insert(50)... 14 39 24 65 50 38 55 78 76 86 66
-- priority_queue_insert(36)... 14 39 24 65 50 36 55 78 76 86 66 38
-- priority_queue_insert(67)... 14 39 24 65 50 36 55 78 76 86 66 38 67
-- priority_queue_insert(47)... 14 39 24 65 50 36 47 78 76 86 66 38 67 55
✔️ Priority queue is a heap.

Test #5: Popping elements from queue...
-- priority_queue_pop()... 24 39 36 65 50 38 47 78 76 86 66 67 67
-- priority_queue_pop()... 36 39 38 65 50 67 47 78 76 86 66 67
-- priority_queue_pop()... 38 39 47 65 50 67 66 78 76 86 66
-- priority_queue_pop()... 39 50 47 65 86 67 66 78 76 86
-- priority_queue_pop()... 47 50 66 65 86 67 76 78 76
-- priority_queue_pop()... 50 65 66 78 86 67 76 78
-- priority_queue_pop()... 65 76 66 78 86 67 76
-- priority_queue_pop()... 66 76 67 78 86 67
-- priority_queue_pop()... 67 76 86 78 86
-- priority_queue_pop()... 76 78 86 78
-- priority_queue_pop()... 78 86 86
-- priority_queue_pop()... 86 86
-- priority_queue_pop()... 86
-- priority_queue_pop()...
✔️ Priority queue is a heap.
```

### Appendix B: Source code

### `main.c`

```c
```

### `minheap0.h`

```c
// paste in later
```

### `minheap0.c`

```c
// paste in later
```

### `priority_queue.h`

```c
```

### `priority_queue.c`

```c
```
