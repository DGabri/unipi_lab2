#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void open_file(char fname[]) {
  // open file in read text mode
  // append: a, write: w,

  FILE *p = fopen(fname, "rt");
  if (p == NULL) {
    printf("Error opening file!");
    exit(1);
  }

  // close file
  if (fclose(p) == EOF) {
    puts("Error closing file");
    exit(1);
  }
}

void read_from_terminal() {
  // read value from terminal
  int number;
  int err = scanf("Insert number value %d", &number);

  if (err != 1) {
    puts("ERROR READING VALUE");
    exit(1);
  }
}

void read_from_file(char fname[]) {

  FILE *p = fopen(fname, "rt");
  if (p == NULL) {
    printf("Error opening file!");
    exit(1);
  }
  // READ FILE
  while (true) {
    int n;
    int e = fscanf(p, "%d", &n);
    if (e == EOF)
      break;
    if (e != 1) {
      puts("Contenuto illegale nel file");
      exit(1);
    }
  }

  // close file
  if (fclose(p) == EOF) {
    puts("Error closing file");
    exit(1);
  }
}

void write_to_file(char fname[]) {

  FILE *p = fopen(fname, "wt");
  if (p == NULL) {
    printf("Error opening file!");
    exit(1);
  }

  int counter = 0;

  for (int i = 0; i <= 100; i++) {

    if (counter < 20) {
      int e = fprintf(p, "%d, ", i); // scrive i nel file

      if (e < 0) {
        puts("Errore nella scrittura");
        exit(1);
      }
    } else {
      int e = fprintf(p, "%d,\n", i); // scrive i nel file

      if (e < 0) {
        puts("Errore nella scrittura");
        exit(1);
      }
      counter = 0;
    }

    counter++;
  }

  // close file
  // RETURN VALUES
  // Upon successful completion 0 is returned.  Otherwise, EOF is returned
  // fclose(p) == EOF is the same as fclose(p) != 0
  if (fclose(p) == EOF) {
    puts("Errore chiusura file");
    exit(1);
  }
  /*
  if (fclose(p) == EOF) {
    puts("Errore chiusura file");
    exit(1);
  } */
}
// fprintf()

int main(int argc, char *argv[]) {
  // argc = number of terminal parameters passed
  // argv = array of strings of the elements passed on terminal
  // argv[0] = executable name
  write_to_file(argv[1]);
}
