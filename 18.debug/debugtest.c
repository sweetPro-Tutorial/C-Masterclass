#include <stdio.h>

#define AGES_SIZE 3

int main() {
    int ages[AGES_SIZE] = { 10, 15, 20 };
    int sum = 0;

    for(int i = 0; i < AGES_SIZE; i++) {
        sum += ages[i];
        printf("ages[%d] = %d --> sum = %d\n", i, ages[i], sum);
    }
    printf("sum = %d\n", sum);

    return 0;
}
