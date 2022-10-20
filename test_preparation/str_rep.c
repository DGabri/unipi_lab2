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
      if (inserted >= size) {
        size *= 2;
        result = realloc(result, sizeof(char) * size);
        if (result == NULL) {
          puts("CAN'T REALLOCATE STRING");
          exit(1);
        }
      }

      result[inserted++] = *stringa;
      stringa++;
    } /* while */

    printf("\n=======\n");
    stringa = tmp;
  }

  stringa = result;

  while (*stringa != '\0') {
    printf("%c", *stringa);
    stringa++;
  }
  printf("\n");

  result = realloc(result, sizeof(char) * (inserted + 1));
  if (result == NULL) {
    puts("CAN'T REALLOCATE STRING");
    exit(1);
  }
  return result;
}

char *product2(char str[], int times) {
  int len = strlen(str);
  int tot_len = times * len + 1;
  char *out = malloc(tot_len);
  int i, j, pos;

  for (i = 0, pos = 0; i < times; i++) {
    for (j = 0; j < len; j++) {
      out[pos++] = str[j];
    }
  }

  out[pos] = '\0';

  printf("%s\n", out);

  return (out);
}

int main(int argc, char *argv[]) {
  // char str[1000];
  // int k;

  // scanf("%s", str);
  // scanf("%d", &k);
  char *test = product2("ciao", 5);

  free(test);
  return -1;
}
