// game-of-life.cpp
// AUTHOR: mae morella
#include <cmath>
#include <ctime>
#include <iostream>
#include <queue>
#include <random>
#include <stdexcept>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

typedef bool cell_t;
typedef vector<cell_t> row_t;
typedef vector<row_t> grid_t;

// Constructs an empty grid of the given size.
grid_t generate_grid(grid_t::size_type rows, row_t::size_type cols) {
  // initalize all values with 0
  return grid_t(rows, row_t(cols, 0));
}

// Prompt the user to input values to construct a grid of a given size.
grid_t generate_grid_from_cin() {
  std::cout << "Enter grid size: ";
  int size;
  std::cin >> size;
  grid_t grid = generate_grid(size, size);
  std::cout << "Enter input grid:\n";
  for (int i = 0; i < size; i++) std::cout << "_ ";
  std::cout << "\n";
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      cell_t c;
      std::cin >> c;  // read from user input
      grid[i][j] = c;
    }
  }
  return grid;
}

// Constructs a boad of the given size populated with random cells.
grid_t generate_grid_from_random(grid_t::size_type size) {
  grid_t grid = generate_grid(size, size);
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      grid[i][j] = (bool)(random() % 2);
    }
  }
  return grid;
}

// Check whether the cell at row r, col c is alive.
// All cells outside of the grid are dead.
bool is_cell_alive(const grid_t &grid, int r, int c) {
  if (0 <= r && r < grid.size() && 0 <= c && c < grid[r].size()) {
    return grid[r][c];
  } else {
    return 0;
  }
}

// For the cell at row r, col c, count how many neighboring cells are alive
unsigned int count_neighbors(const grid_t &grid, int r, int c) {
  unsigned int neighbors = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i != 0 || j != 0)  // exclude the current cell
        neighbors += is_cell_alive(grid, r + i, c + j);
      if (neighbors > 3) {
        return neighbors;
      }
    }
  }
  return neighbors;
}

// Overload the << operator to print the given grid to stdout
std::ostream &operator<<(std::ostream &out, const grid_t &grid) {
  for (auto it = grid.begin(); it != grid.end(); it++) {
    for (auto jt = it->begin(); jt != it->end(); jt++) {
      // swap these characters for prettier output
      out << (*jt ? "1" : "0") << " ";
    }
    out << '\n';
  }
  return out;
}

// Determines the next state for the cell at the given coordinates.
// This function encodes the rules for the cellular automata
bool cell_will_live(const grid_t &grid, int r, int c) {
  bool alive = is_cell_alive(grid, r, c);
  int neighbors = count_neighbors(grid, r, c);
  // alive cells with lt 2 or gt 3 neighbors become dead.
  if (alive && (neighbors < 2 || 3 < neighbors)) return false;
  // Dead cells with 3 neighbors become alive.
  if (!alive && neighbors == 3) return true;
  return alive;
}

// Given a grid, return a new grid with the next state.
grid_t next_grid(const grid_t &grid) {
  // generate an empty grid of the same size as the last one.
  grid_t next_grid = grid_t(grid.size(), row_t(grid[0].size(), 0));
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      next_grid[i][j] = cell_will_live(grid, i, j);
    }
  }
  return next_grid;
}

// Given a grid, print out several iterations of it.
void simulate(grid_t &grid, unsigned int iteration_count) {
  for (int i = 0; i <= iteration_count; i++) {
    std::cout << "Iteration #" << i << ":\n";
    std::cout << grid;
    grid = next_grid(grid);
  }
}

// Main program
int main() {
  int MAX_ITERATIONS = 50;

  // grid_t grid = generate_grid_from_random(800);
  grid_t grid = generate_grid_from_cin();
  clock_t start = clock();
  simulate(grid, MAX_ITERATIONS);
  clock_t end = clock();
  // std::cout << grid;
  double milliseconds = 1000 * (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << MAX_ITERATIONS << " iterations took " << milliseconds << " ms\n";
  return EXIT_SUCCESS;
}