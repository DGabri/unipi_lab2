#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// different data types can be inserted
// if I pass these structs to a function

struct test {
  int first;
  int second;
  double temperature;
  char *name;
};

//
typedef struct test1 {
  int first;
  int second;
  double temperature;
  char *name;
} struct_test;

// redefine the type int to integer
typedef int integer;

// If I create a variable of type pointer_to_int it is a pointer
typedef int *pointer_to_int;

// I can change the values inside the struct
struct test switch_values(struct test d) {
  int tmp = d.first;
  d.first = d.second;
  d.second = tmp;

  return d;
}

void print_couple(struct test1 *a, FILE *f) {
  fprintf(f, "(%f, %f)\n", (*a).first, (*a).second);
}