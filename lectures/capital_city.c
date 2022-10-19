#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// if I inserted name under
// three variables are not initialized. Inside name there is a value that I
// shouldn't use

typedef struct {
  // char name[20]; I chose 20 bytes for each name, if the length is longer I
  // have a problem
  char *name; // pointer of 8 bytes
  double lat;
  double lon;

} capital;

// array of capitals

void print_capital(capital *a, FILE *f) {
  fprintf(f, "%20s (%f, %f)\n", (*a).name, (*a).lat, a->lon);
}

capital *create_capital(char *capital_name, double latitude, double longitude) {
  assert(capital_name != NULL);
  assert(latitude >= -90 && latitude <= 90);
  assert(latitude >= -180 && longitude <= 180);

  capital *a = malloc(sizeof(*a));
  // a->name = capital_name; possible
  a->name = strdup(capital_name); // safer
  a->lat = latitude;
  a->lon = longitude;
  return a;
}

void free_capital(capital *a) {
  free(a->name); // when
  free(a);
}

capital *read_capital(FILE *f) {
  assert(f != NULL);
  char *s;
  double lat, lon;

  int e = fscanf(f, "%ms %lf %lf", &s, &lat, &lon);

  if (e != 3) {
    return NULL;
  }

  capital *c = create_capital(s, lat, lon);
  free(s); // we created s
  return c;
}

int main(int argc, char *argv[]) {
  // array of 100 capital structs. Each component has dimension = 24 bytes
  // 1 pointer = 8 bytes, 2 x doubles of 8 bytes each = 8+16 = 24 bytes
  // not using this
  capital a[100];

  // it is not an array of 24 bytes each. It is a pointer to capital.
  // array of pointers to capital. Each capitals[i] = pointer = 8 bytes
  // b[0] is apointer to capital, uninitialized,
  capital *capitals[100];
  capitals[0] = malloc(sizeof(capital));
  // b[0].lat = 43 NOT POSSIBLE, it is now a pointer
  //(*capitals[0]).lat = 43; NOT USED FREQUENTLY
  // capitals[0]->lat = 43;

  return -1;
}