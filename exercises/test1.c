#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int arr[], int arr_len) {
  printf("[");
  for (int i = 0; i < arr_len; i++) {
    if (i < arr_len - 1) {
      printf("%d,", arr[i]);
    } else {
      printf("%d", arr[i]);
    }
  }
  printf("]\n");
}

int *create_array_multiple_of_3(int a, int b, int *n) {
  assert(a < b);

  int *result;
  int inserted = 0;
  result = malloc(sizeof(int) * b);

  if (result == NULL) {
    exit(1);
  }

  for (int i = a; i <= b; i++) {
    if (i % 3 == 0) {
      printf("inserted[%d]: %d\n", inserted, i);
      result[inserted++] = i;
    }
  }

  result = realloc(result, inserted);

  *n = inserted;
  return result;
}

char *clean_str(char s[]) {
  char *result;
  int length = strlen(s) + 1;
  int inserted = 0;

  result = malloc(sizeof(char) * length);

  if (result == NULL) {
    puts("can't allocate string");
    exit(1);
  }

  for (int i = 0; i < length; i++) {
    if (s[i] != 'e' && s[i] != 'a') {
      result[inserted] = s[i];
      printf("%c", s[i]);
      // printf("%c", result[inserted]);
    }
  }

  for (int i = 0; i <= inserted; i++) {
    printf("%c", result[i]);
  }
  return result;
}

void clean_string_driver(int len, char *argument_arr[]) {

  for (int i = 1; i < len; i++) {
    char *new_str = clean_str(argument_arr[i]);
    for (int j = 0; new_str[j] != '\0'; j++) {
      printf("%c", new_str[j]);
    }
    printf("\n");
    free(new_str);
  }
}

char *multiply(char s[], int n) {

  char *result = malloc(strlen(s) + (n + 1));
  result[0] = '*';
  int inserted = 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; s[j] != '\0'; j++) {
      result[inserted++] = s[j];
    }
    result[inserted++] = '*';
  }

  for (int i = 0; result[i] != '\0'; i++) {
    printf("%c", result[i]);
  }
  return result;
}

int *filtra(FILE *fin, FILE *fout, int limite, int *n) {
  // first n odd integers where n = limite
  int *numbers_arr = malloc(sizeof(int) * limite);
  int inserted = 0;
  int i = 0;
  int val = 0;

  if (numbers_arr == NULL) {
    puts("CAN'T ALLOCATE ARRAY");
    exit(1);
  }

  while (true) {

    int e = fscanf(fin, "%d", &val);

    if (e != 1) {
      puts("ERROR READING FILE");
      exit(1);
    }

    if ((val % 2 == 1) && (inserted)) {
      numbers_arr[inserted++] = val;
    } else {
      fprintf(fout, "%d\n", val);
    }
  }
  // check if no element was inserted, return NULL if so
  if (inserted == 0) {
    free(numbers_arr);
    numbers_arr = NULL;
  } else {
    numbers_arr = realloc(numbers_arr, inserted);
    if (numbers_arr == NULL) {
      puts("REALLOC FAILED");
      exit(1);
    }
  }

  *n = inserted;
  return numbers_arr;
}

int main(int argc, char *argv[]) {
  int *test;
  int len = 60;
  test = create_array_multiple_of_3(1, 60, &len);
  /*
    //######### 1 ###########
    print_array(test, len);
    free(test);
    //######### 2 ###########
    // char *test_string = clean_str(argv[2]);
    // printf("%s", test_string);
    //######### 3 ###########
    // char test[5] = "casa";
    // char *test_string = multiply(test, 4);
    //######### 4 ###########
    */

  return -1;
}