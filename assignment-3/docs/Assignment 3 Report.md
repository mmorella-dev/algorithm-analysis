# Assignment 3: Priority Queue

KSU College of Computing and Software Engineering<br>
CS 4306 - Algorithm Analysis


## Problem Statement

1. Implement a priority queue using a heap data structure.

## Appendix B: Screenshot of execution

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

## Appendix A: C Code

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
