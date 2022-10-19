#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


void print_array(int arr[], int len) {
  printf("[");
  for (int i = 0; i < len; i++) { 
    if (i < len-1) {
        printf("%d,", arr[i]);
    }
    else {
        printf("%d", arr[i]);
    }
  }
  printf("]\n");
}

void read_numbers() {
    int num;
    int sum = 0;
    int i = 1;
    
    while (i) {
        //puts("insert number(break with 0): ");
        //printf("i:%d\n", i);

        int err = scanf("%d", &num);

        if (err != 1) {exit(1);}
        if (num == 0) {
            i = 0;
        }
        sum += num;
    }
    printf("%d\n", sum);
}

void print_delete() {
    int arr[10];
    int counter = 0;

    while (counter < 10) {
        int err = scanf("%d", &arr[counter]);
        
        if (err != 1) {
            puts("error");
            exit(1);
        }
        
        counter++;
    }
    
    for (int i = 0; i < 10; i++) {
        if ((arr[i] >= 0) && (arr[i] % 2 == 0)) {
            printf("%d\n", arr[i]);
        }
        else if ( (i != 9) && ((arr[i] < 0) && (arr[i+1] >= 0))){
            printf("%d\n", arr[i]);
        }
    }

}

void cats() {
    int code;
    int age;
    float weight;
    //0: kibble, 1:scatoletta, 2:tuna
    int food;
}

int is_prime(int k) {

  if(k%2==0) {
    return k==2?1:0;
  }

  for(int i=3; i<k; i+=2 ) {
    if(k%i==0) return 0;
    if(i*i>k) break;
  }
  return 1;
}

void prime() {
    int num = 0;
    int err = scanf("%d", &num);
    if (err != 1) {
        exit(1);
    }
    printf("%d", is_prime(num));
}

void factorial() {
    int num = 0;
    int i = 0;
    int fact = 1;
    int err = scanf("%d", &num);
    if (err != 1) {
        exit(1);
    }

    while (i <= num) {
        if (i == 1 || i == 0) {
            fact *= 1;
        }
        else {
            fact *= i;
        }
    }
    printf("%d", fact);
}

void invert_arr() {
    int num = 0;
    int *arr;
    int i = 0;
    int left = 0;
    int right = num;

    int err = scanf("%d\n", &num);
    if (err != 1) {
        exit(1);
    }

    arr = malloc(sizeof(int)*(num+1));
    if (arr == NULL) {
        exit(1);
    }

    while (i < num) {
        int err = scanf("%d\n", &arr[i]);
        if (err != 1) {
            exit(1);
        }   
        i++;
    }

    while (left < right) {
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;
    }
}

int array_condition() {
  int arr[10];
  int counter = 0;
  int index = -1;
  while (counter < 10) {
    int err = scanf("%d", &arr[counter]);

    if (err != 1) {
      puts("error");
      exit(1);
    }

    counter++;
  }

  for (int i = 1; i < 9; i++) {
    if (arr[i] == (arr[i + 1] - arr[i - 1])) {
      index = i;
    }
  }
  return index;
}

int main(int argc, char *argv[]) { 
    //read_numbers();
    int arr[5] = {5, 12, 34, 67, 89};
    int arr1[5] = {13, 25, 38, 62, 10};
    int res[5] = {0,0,0,0,0};
    printf("[");
    for (int i=0; i<5; i++) {
        if (i!=4) {
            printf("%d,", arr[i]);
            res[i] = arr[i];
        }
        else {
            printf("%d", arr[i]);
        }
    }
    printf("]");

    printf("[");
    for (int j=0; j<5; j++) {
        if (j!=4) {
            printf("%d,", arr1[j]);
            res[j] += arr1[j];
        }
        else {
            printf("%d", arr1[j]);
        }
    }
    printf("]");

    printf("[");
    for (int k=0; k<5; k++) {
        if (k!=4) {
            printf("%d,", res[k]);
        }
        else {
            printf("%d", arr[k]);
        }
    }
    printf("]");
    return -1;
}