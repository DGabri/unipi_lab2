#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *product(char str[], int times) {
  int size = 1000;
  int inserted = 0;
  char *tmp = str;
  char *stringa = str;
  char *result = malloc(sizeof(char) * size);

  if (result == NULL) {
    puts("CAN'T ALLOCATE STRING");
    exit(1);
  }

  for (int i = 0; i < times; i++) {
    while (*stringa != '\0') {
      printf("%c", *stringa);
      if (inserted < size) {
        result[inserted++] = *stringa;
        stringa++;
      } else {
        size *= 2;
        result = malloc(sizeof(char) * size);
        if (result == NULL) {
          puts("CAN'T REALLOCATE STRING");
          exit(1);
        }
        result[inserted++] = *stringa;
        stringa++;
      }
    }

    printf("\n=======\n");
    *stringa = *tmp;
  }

  *stringa = *result;

  while (*stringa != '\0') {
    printf("%c", *stringa);
    stringa++;
  }

  result = realloc(result, inserted);
  if (result == NULL) {
    puts("CAN'T REALLOCATE STRING");
    exit(1);
  }
  return result;
}

int main(int argc, char *argv[]) {
  char str[1000];
  int k;

  // scanf("%s", str);
  // scanf("%d", &k);
  char *test = product("ciao", 5);

  free(test);
  return -1;
}