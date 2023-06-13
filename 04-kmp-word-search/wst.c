#include <stdbool.h>  // for bool type
#include <stdio.h>
#include <stdlib.h>  //
#include <string.h>  // for strlen

#define MAX_REFERENCE_COUNT 30

void wst_main(const char* filename, const char* search);

// MAIN PROGRAM
// ============

int main(int argc, char const* argv[]) {
  // Parse command args.
  if (argc != 3) {
    printf("Usage: $ %s [file] [search]\n", argv[0]);
    return EXIT_FAILURE;
  }
  const char* args_filename = argv[1];
  const char* args_search = argv[2];

  wst_main(args_filename, args_search);
}

// KMP ALGORITHM
// =============

int* compute_prefix_function(const char* search) {
  size_t len = strlen(search);
  int* prefix =
      malloc(len * sizeof(*prefix));  // Attempt allocating a new array
  if (prefix != NULL) {
    prefix[0] = 0;
    int k = 0;
    for (int q = 1; search[q] != '\0'; q++) {
      while (k > 0 && search[k] != search[q]) k = prefix[k - 1];
      if (search[k] == search[q]) k++;
      prefix[q] = k;
    }
  }
  return prefix;
}

void kmp_matcher(FILE* file, const char* search) {
  int* prefix = compute_prefix_function(search);
  int q = 0;  // number of chars matched
  char c;
  while (file != NULL && (c = getc(file)) != EOF) {
    while (q > 0 && search[q] != c)
      q = prefix[q - 1];      // Next char does not match.
    if (search[q] == c) q++;  // The next char matches
    if (search[q] == '\0') {  // Is all of P matched?
      printf("Found /%s/\n", search);
      q = prefix[q - 1];  // Look for the next match
    }
  }
  free(prefix);
}

// Performs the inner loop of the KMP_search function only once
// Advances FILE until immediately after the last instance of search.
// Returns 1 if matched, 0 if not.
bool fseek_to_match(FILE* stream, const char* search, const int* prefix,
                    int* q) {
  char c;
  while (stream != NULL && (c = getc(stream)) != EOF) {
    while (*q > 0 && search[*q] != c) {
      *q = prefix[*q - 1];  // Next char does not match.
    }
    if (search[*q] == c) *q += 1;  // The next char matches
    if (search[*q] == '\0') {      // Is all of P matched?
      *q = prefix[*q - 1];         // Set q to search for the next instance
      return true;
    }
  }
  return false;
}

// Counts the number of items in a file.
// POSTCONDITION:
int kmp_word_count(FILE* file, const char* search) {
  int* prefix = compute_prefix_function(search);
  int count = 0;
  int q = 0;
  while (fseek_to_match(file, search, prefix, &q)) {
    count += 1;
  }
  free(prefix);
  return count;
}

// Linked file list
// ================

typedef struct FileListNode {
  struct FileListNode* next;
  char filename[];
} FileListNode;

FileListNode* create_file_list_node(const char* filename) {
  size_t l = strlen(filename);
  FileListNode* n = malloc(sizeof(*n) + l * sizeof(n->filename[0]));
  if (n == NULL) {
    perror("malloc failed in create_file_list_node");
    return NULL;
  }
  strcpy(n->filename, filename);
  return n;
}

bool file_list_contains(FileListNode* head, const char* filename) {
  FileListNode* cur = head;
  while (cur != NULL) {
    if (strcmp(cur->filename, filename) == 0) {
      return true;
    }
    cur = cur->next;
  }
  return false;
}

void free_file_list(FileListNode* head) {
  FileListNode* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

FileListNode* parse_references(const char* initial_filename, const char* reftag,
                               const int* ref_prefix) {
  FILE* f = fopen(initial_filename, "r");
  if (f == NULL || feof(f)) {
    printf("Error reading %s\n", initial_filename);
    return NULL;
  }
  // Search for first "<REFERENCE>"
  // printf("Scanning for references in %s ...\n", initial_filename);
  int q = 0;
  FileListNode* head = create_file_list_node(initial_filename);
  FileListNode* tail = head;
  while (fseek_to_match(f, reftag, ref_prefix, &q)) {
    FileListNode* n = create_file_list_node("");
    fscanf(f, "%s", n->filename);  // grab filename
    // printf("Found reference to %s\n", n->filename);
    if (file_list_contains(head->next, n->filename)) {
      free(n);
    } else {
      tail->next = n;
      tail = tail->next;
    }
  }
  fclose(f);
  return head;
}

// Adjacency matrix (just an array of linked lists)
// ================================================

typedef FileListNode** FileMatrix;

// Returns true if the matrix's "head" column already contains a node with
// `filename`.
bool file_matrix_head_contains(const FileMatrix matrix, const char* filename) {
  for (int i = 0; matrix[i] != NULL; i++) {
    if (strcmp(filename, matrix[i]->filename) == 0) {
      return true;
    }
  }
  return false;
}

FileMatrix generate_reference_matrix(const char* initial_filename,
                                     const char* reftag, size_t capacity) {
  int* ref_prefix = compute_prefix_function(reftag);
  FileMatrix matrix = malloc((capacity + 1) * sizeof(*matrix));
  matrix[0] = parse_references(initial_filename, reftag, ref_prefix);
  size_t matrix_size = 1;
  for (size_t i = 0; i < matrix_size; i++) {
    FileListNode* cur = matrix[i]->next;
    while (cur != NULL) {
      // If it doesn't already exist, add it.
      if (!file_matrix_head_contains(matrix, cur->filename)) {
        matrix[matrix_size++] =
            parse_references(cur->filename, reftag, ref_prefix);
      }
      cur = cur->next;
    }
  }
  matrix[matrix_size] = NULL;
  return matrix;
}

void print_file_matrix(const FileMatrix matrix) {
  for (int i = 0; matrix[i] != NULL; i++) {
    printf("[ %10s ]\t", matrix[i]->filename);
    FileListNode* cur = matrix[i]->next;
    while (cur != NULL) {
      printf(" -> ");
      printf("%4s", cur->filename);
      cur = cur->next;
    }
    printf("\n");
  }
}

void free_file_matrix(const FileMatrix matrix) {
  for (int i = 0; matrix[i] != NULL; i++) {
    free_file_list(matrix[i]);
  }
  free(matrix);
}

void wst_main(const char* filename, const char* search) {
  const char* reftag = "<REFERENCE> ";
  // const int* ref_prefix = compute_prefix_function(reftag);
  // Create adjacency matrix
  FileMatrix matrix = generate_reference_matrix(filename, reftag, 30);
  // print_file_matrix(matrix);
  for (int i = 0; matrix[i] != NULL; i++) {
    FILE* f = fopen(matrix[i]->filename, "r");
    int c = kmp_word_count(f, search);
    printf("%s occured %d times in %s\n", search, c, matrix[i]->filename);
    fclose(f);
  }
  free_file_matrix(matrix);
}