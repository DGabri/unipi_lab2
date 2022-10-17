#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **read_strings(FILE *f, int *num) {
  assert(f != NULL);
  int size = 10;
  int inserted = 0;
  char **arr = malloc(sizeof(char *) * size);

  if (arr == NULL) {
    exit(1);
  }

  while (true) {
    char *b;
    int error = fscanf(f, "%ms", &b);

    if (error == EOF)
      break;

    if (inserted == size) {
      // increase array size
      size *= 2;
      arr = realloc(arr, size);

      if (arr == NULL) {
        puts("REALLOC FAILED");
        exit(1);
      }
    }

    assert(inserted < size);
    arr[inserted] = b;
    inserted += 1;
  }

  size = inserted;
  arr = realloc(arr, sizeof(char *) * size);
  if (arr == NULL) {
    puts("REALLOC FAILED");
    exit(1);
  }

  // update number of inserted strings
  *num = inserted;
  return arr;
}

int main(int argc, char *argv[]) {
  FILE *f = fopen(argv[1], "rt");
  if (f == NULL) {
    exit(1);
  }

  // copy strings in array
  int n;
  // **char because string is an array so this is a pointer to string
  char **arr = read_strings(f, &n); //**char

  if (fclose(f) != 0) {
  }
  return -1;
}