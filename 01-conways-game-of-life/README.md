# 1. Conway's Game of Life

[game_of_life.cpp](game_of_life.cpp) contains a simple C++ implementation of the "Game of Life" cellular automata.

It takes a square grid of 1 and 0 cells, and produces the first 50 iterations of the automata.

See my [full report](docs/assignment-1.md) for discussion of its time complexity.

## Usage

1. Run `make` to compile.
2. Invoke as `cat input1.txt | ./game_of_life`

### Sample input

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

### Sample output
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