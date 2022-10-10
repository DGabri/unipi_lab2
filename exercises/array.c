#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_arr() {
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
            printf("%d \n", arr[i]);
        }
        else if ( (i != 9) && ((arr[i] < 0) && (arr[i+1] >= 0))){
            printf("%d \n", arr[i]);
        }
    }
}

void azzera() {

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

    int min = arr[0];
    int *ptr;
    int count = 0;

    for (ptr = arr; ptr < arr+10; ++ptr) {
        
        if ((*ptr) < min) {
            min = *ptr;
        }
        if (count%2 == 1) {
            *ptr = 0;
        }

        count++;
    }

    for (int i=0; i<10; i++) {
        printf("Element[%d]: %d\n", i, arr[i]);
    }
    printf("Minimum value: %d\n", min);

}

int main(int argc, char *argv[]) {
    print_arr();
    azzera();
    return 0;
}