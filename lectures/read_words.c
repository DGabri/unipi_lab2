#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int a = 1;
  char s[12];
  char z[12];

  /*
  NOT a good way to trunc strings because if I insert longer strings they get
truncated puts("INSERT ONE NUMBER AND TWO STRINGS");
// UNSAFE, READS ALL AVAILABLE CHARACTERS
// int error = scanf("%d %s %s", &a, s, z);

// SAFE, STOPS AFTER N CHARACTERS GIVEN IN THE FORMATTER
// MAX %LENGHT-1 (BECAUSE OF '\0')
int error = scanf("%d %11s %11s", &a, s, z);
if (error != 3) {
  exit(1);
}

// if I insert s or z longer than their allocated size I get buffer overflow
printf("a = %d, s = %s, z = %s", a, s, z);
  */

  puts("INSERT ONE NUMBER AND TWO STRINGS");
  // UNSAFE, READS ALL AVAILABLE CHARACTERS
  // int error = scanf("%d %s %s", &a, s, z);

  // SAFE, STOPS AFTER N CHARACTERS GIVEN IN THE FORMATTER
  // MAX %LENGHT-1 (BECAUSE OF '\0')
  int error = scanf("%d %ms %ms", &a, s, z);
  if (error != 3) {
    exit(1);
  }

  // if I insert s or z longer than their allocated size I get buffer overflow
  printf("a = %d, s = %s, z = %s", a, s, z);

  return -1;
}