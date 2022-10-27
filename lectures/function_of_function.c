#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int applica(int x, int y, int (*f)(int, int)) {
  int z = f(x, y);
  return z;
}

int main(int argc, char *argv[]) {
  int a = 12;
  int b = 1;
  // int c = applica(a, b,  y, int (*f)(int, int))

  return -1;
}
