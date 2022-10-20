#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int size = 10;
  int *arr = malloc(sizeof(int) * size);
  int inserted = 0;
  int reallocs = 0;
  int idx = 0;

  if (arr == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(1);
  }

  while (idx < 90) {
    if (inserted >= size) {
      // fprintf(stderr, "OLD SIZE: %d\n", size);
      size *= 2;
      arr = realloc(arr, sizeof(int) * size);

      if (arr == NULL) {
        fprintf(stderr, "REALLOC FAILED\n");
        exit(1);
      }
      reallocs++;
      fprintf(stderr, "INSERTED NUMBER: %d\n", inserted);
      fprintf(stderr, "REALLOC NUMBER: %d\n", reallocs);
      fprintf(stderr, "NEW SIZE: %d\n", size);
      puts("=============================");
    }

    arr[inserted] = idx;
    // printf("%d,", arr[inserted]);
    inserted++;
    idx++;
    // printf("IDX: %d\n", idx);
  }

  printf("\nINSERTED: %d\n", inserted);
  printf("[");

  for (int i = 0; i < inserted; i++) {

    if (i < inserted - 1) {
      printf("%d,", arr[i]);
    } else {
      printf("%d]\n", arr[i]);
    }
  }
  return -1;
}