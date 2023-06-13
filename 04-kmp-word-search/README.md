# 4. KMP Word Search

This program [wst.c](wst.c) implements the [Knuth–Morris–Pratt algorithm](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) for string searching, as well as an adjacency matrix.

The program takes the parameters `input_file` and `search_string`, and counts all instances of `search_string` in `input_file`. Then, if the input_file contains a reference of the form `<REFERENCE> filename`, it opens `filename` and counts instances of `search_string` in there too. This process occurs recursively. References are tracked using a matrix to avoid repeated counting of the same file within the reference tree.

As an example, the files A, C, and D are included.

* A references C and D
* C references A and C
* D references C

## Usage
```sh
make
./wst [input_file] [search_string]
```

## Sample output
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