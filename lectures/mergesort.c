#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge_sort(int a[], int len) {
  assert(a != NULL);
  assert(len > 0);

  // base case
  if (len == 1) {
    return;
  }

  int sx = len / 2;  // len of first part (sx)
  int dx = len - sx; // len of second part (dx)

  merge_sort(a, sx);      // first part of the array
  merge_sort(&a[sx], dx); // second part of the array &a[sx] is the same as a+sx

  // the first two parts are sorted and i need to merge
  int *result = malloc(sizeof(int) * len); // sizeof(*result) is dynamic
  int *second_part = &a[sx];
  int index_a = 0, index_b = 0, index_c = 0;

  if (result == NULL) {
    exit(1);
  }

  for (index_b = 0; index_b < len; index_b++) {
    // check if index_a == sx
    if (index_a == sx) {
      result[index_b] = second_part[index_c++]; // increment index of read value
    }

    else if (index_c == dx) {
      result[index_b] = a[index_a++]; // increment index of read value
    }

    else {
      if (a[index_a] < second_part[index_c]) {
        result[index_b] = a[index_a++]; // increment index of read value

      } else {
        result[index_b] =
            second_part[index_c++]; // increment index of read value
      }
    }
    assert(index_a == sx);
    assert(index_c == dx);
  }
}

int main(int argc, char *argv[]) {}