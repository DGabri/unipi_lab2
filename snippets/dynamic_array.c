#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  // create dynamic array
  int *array;
  int array_length = 10;
  array = malloc(sizeof(int) * array_length);

  // ERROR HANDLING
  // check if the array was allocated and if there was space
  if (array == NULL) {
    printf("COULDN'T ALLOCATE ARRAY");
    exit(1);
  }

  // REALLOCATE ARRAY SIZE
  // length decreased

  array_length -= 4;
  array = realloc(array, array_length);

  if (array == NULL) {
    printf("COULDN'T REALLOCATE ARRAY");
    exit(1);
  }

  // free the allocated array
  free(array);
}