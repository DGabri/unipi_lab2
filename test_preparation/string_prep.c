#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strcat1(char *s1, char *s2) {

  char *result = malloc(sizeof(char) * 1000);
  int inserted = 0;
  if (result == NULL) {
    puts("CAN'T ALLOCATE STRING");
    exit(1);
  }

  while (*s1 != '\0') {
    result[inserted++] = *s1;
    s1++;
  }
  while (*s2 != '\0') {
    result[inserted++] = *s2;
    s2++;
  }

  result = realloc(result, inserted);
  if (result == NULL) {
    puts("CAN'T REALLOCATE STRING");
    exit(1);
  }

  char *s = result;

  while (*s != '\0') {
    printf("%c", *s);
    s++;
  }
  return result;
}

char *product(char str[], int times) {

  char *result = malloc(sizeof(char) * 5000);
  int inserted = 0;
  if (result == NULL) {
    puts("CAN'T ALLOCATE STRING");
    exit(1);
  }

  for (int i = 0; i < times; i++) {
    while (*str != '\0') {
      result[inserted++] = *str;
      str++;
    }
  }

  result = realloc(result, inserted);
  if (result == NULL) {
    puts("CAN'T REALLOCATE STRING");
    exit(1);
  }
  return result;
}

int main(int argc, char *argv[]) {
  char first[1000];
  char second[1000];

  scanf("%s", first);
  scanf("%s", second);
  char *test = my_strcat1(first, second);

  free(test);
  return -1;
}
