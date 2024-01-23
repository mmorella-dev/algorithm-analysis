# algorithms

This repository contains my responses to assignments in CS 4306 Algorithm Analysis in C/C++.

## Conway's Game of Life

[game_of_life.cpp](game_of_life.cpp) contains a simple C++ implementation of the "Game of Life" cellular automata.

It takes a square grid of 1 and 0 cells, and produces the first 50 iterations of the automata.

See my [full report](docs/assignment-1.md) for discussion of its time complexity.

### Usage

1. `cd 01-conways-game-of-life`
1. Run `make` to compile.
2. Invoke as `cat input1.txt | ./game_of_life`

#### Sample input

```txt
13
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 1 1 1 0 0 0 0
0 0 0 0 1 1 1 1 1 0 0 0 0
0 0 0 0 1 1 1 1 1 0 0 0 0
0 0 0 0 1 1 1 1 1 0 0 0 0
0 0 0 0 1 1 1 1 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
```

#### Sample output
```txt
Iteration #50:
0 0 0 0 0 0 1 0 0 0 0 0 0 
0 0 0 0 0 1 0 1 0 0 0 0 0 
0 0 0 0 0 1 0 1 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 1 1 0 
1 0 0 1 0 0 0 0 0 1 0 0 1 
0 1 1 0 0 0 0 0 0 0 1 1 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 0 0 0 
0 0 0 0 0 1 0 1 0 0 0 0 0 
0 0 0 0 0 1 0 1 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 0 0 0 
50 iterations took 6.171 ms
```
## 2. Basic Array Operations

This assignment consists of the simple task of rewriting Exercise2.java (a single Java class containing some elementary array operations) into C and C++.

I created two solutions:

* [ex2.c](ex2.c) – a simple C implementation
* [exercise2.cpp](exercise2.cpp) – a C++14 implementation, making use of STL containers and algorithms.

See my [full report](docs/assignment-2-response.md).

### Usage

```sh
cd 02-intro-to-cpp
make # Compile
java Exercise2  # Java implementation
./ex2           # C implementation
./exercise2     # C++ implementation
```

#### Sample output

```txt
The highest number: 15
The average of the numbers: 10.5
The original array: 10 5 15 12 
The reverse array: 12 15 5 10 
The prime numbers in the array: 5
```
## 3. Heapsort (with Priority Queue)

This assignment consists of a C implementation a heap-based priority queue similar to the C++ std::priority_queue.

* [priority_queue.h](priority_queue.h) – Defines the `priority_queue` struct and the `_size`, `_peek`, `_pop`, and `_insert` functions to operate on it. Also defines `heap_sort`.
* [priority_queue.c](priority_queue.c) – Implements the above and other heap manipulation functions
* [main.c](main.c) – A test program for the _peek _pop and _insert functions.

### Usage

```sh
cd 03-priority-queue
make
./priority_queue
```

#### Sample output

```txt
- Original array: -2 40 64 49 21 63 35 69 14  0 
Test #1: Calling min_heapsort...
-- Result: 69 64 63 49 40 35 21 14  0 -2 
✔️ Array is sorted.

Test #2: Calling alloc_priority_queue...
✔️ Priority queue allocated successfully.

Test #3: Inserting random elements...
-- priority_queue_insert(57)... 57 
-- priority_queue_insert(86)... 57 86 
-- priority_queue_insert( 9)...  9 86 57 
-- priority_queue_insert(72)...  9 72 57 86 
-- priority_queue_insert(-9)... -9  9 57 86 72 
-- priority_queue_insert(31)... -9  9 31 86 72 57 
-- priority_queue_insert( 9)... -9  9  9 86 72 57 31 
-- priority_queue_insert(12)... -9  9  9 12 72 57 31 86 
-- priority_queue_insert(16)... -9  9  9 12 72 57 31 86 16 
-- priority_queue_insert(58)... -9  9  9 12 58 57 31 86 16 72 
✔️ Priority queue is a heap.

Test #4: Popping elements from queue...
-- priority_queue_pop()...  9 12  9 16 58 57 31 86 16 
-- priority_queue_pop()...  9 12 31 16 58 57 86 86 
-- priority_queue_pop()... 12 16 31 86 58 57 86 
-- priority_queue_pop()... 16 57 31 86 58 57 
-- priority_queue_pop()... 31 57 58 86 58 
-- priority_queue_pop()... 57 86 58 86 
-- priority_queue_pop()... 58 86 58 
-- priority_queue_pop()... 86 86 
-- priority_queue_pop()... 86 
-- priority_queue_pop()... 
✔️ Priority queue is a heap.
```
## 4. KMP Word Search

This program [wst.c](wst.c) implements the [Knuth–Morris–Pratt algorithm](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) for string searching, as well as an adjacency matrix.

The program takes the parameters `input_file` and `search_string`, and counts all instances of `search_string` in `input_file`. Then, if the input_file contains a reference of the form `<REFERENCE> filename`, it opens `filename` and counts instances of `search_string` in there too. This process occurs recursively. References are tracked using a matrix to avoid repeated counting of the same file within the reference tree.

As an example, the files A, C, and D are included.

* A references C and D
* C references A and C
* D references C

### Usage
```sh
cd 04-kmp-word-search
make
./wst [input_file] [search_string]
```

### Sample output
```txt
$ ./wst A.in textstr
textstr occured 99 times in A.in
textstr occured 10 times in C.in
textstr occured 100 times in D.in

$ ./wst C.in textstr
textstr occured 10 times in C.in
textstr occured 99 times in A.in
textstr occured 100 times in D.in

$ ./wst D.in textstr
textstr occured 100 times in D.in
textstr occured 10 times in C.in
textstr occured 99 times in A.in
```
## 5. Graph Algorithm

The files [graph.h](graph.h) and [graph.c](graph.c) implement a Graph data structure, along with an algorithm to find articulation points, and Dijkstra’s algorithm for finding the shortest distance between two vertices.

### Usage

```sh
cd 05-weighted-graph
make
./graph
```

#### Input

![The graph being used](graph.png)

The graph data to use is hard-coded in [main.c](main.c):
```c
Graph* g = construct_graph(6);  // define a graph with vertices 0 thru 5
graph_add_edge(g, 0, 1, 10.0);  // add edge from 0 -> 1, with weight 10.0
graph_add_edge(g, 0, 2, 10.0);
graph_add_edge(g, 1, 3, 10.0);
graph_add_edge(g, 1, 4, 10.0);
graph_add_edge(g, 2, 3, 10.0);
graph_add_edge(g, 3, 5, 10.0);
graph_add_edge(g, 4, 5, 10.0);
graph_add_edge(g, 5, 3, 10.0);
```

#### Sample output

```txt
Calling print_graph...
[0] -> 1, 2
[1] -> 3, 4
[2] -> 3
[3] -> 5
[4] -> 5
[5] -> 3
Calling depth_first_traversal...
0 -> 1 -> 3 -> 5 -> 4 -> 2
Calling find_articulation_points...
Articulation points: 0 1 
Dists from v #0: 0 10 10 20 20 30 
Dists from v #1: inf 0 inf 10 10 20 
Dists from v #2: inf inf 0 10 inf 20 
Dists from v #3: inf inf inf 0 inf 10 
Dists from v #4: inf inf inf 20 0 10 
Dists from v #5: inf inf inf 10 inf 0 
Diameter: 30
```
## 6. RSA algorithm

The program [rsa.c](rsa.c) implements the RSA algorithm for small messages (consisting of a single `unsigned long`).

### Usage

```sh
cd 06-rsa-multiplication
make
./rsa
```

## Disclaimer

This repository contains solutions to school-assigned homework and lab assignments, and should be used only for reference and educational purposes by ***persons who are not currently enrolled students of Kennesaw State University or taking a similar class.*** Plagiarism or uncredited copying of this code is in violation of university policy, and is harshly discouraged.

***Under no circumstances should any of these files be copied or submitted as your own work.***

## License

MIT © 2021, 2023, 2024 Mae Morella
