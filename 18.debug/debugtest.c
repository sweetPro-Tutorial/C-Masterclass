#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AGES_SIZE 3

void test_memset();

int main() {
    // 포맷과 입력값의 타입이 불일치 한 경우
    printf("Name=[%s], Age=[%d], ID=[%s]\n", "Mr.Kim", 20, "99-111-4240");  // OK
    printf("Name=[%s], Age=[%d], ID=[%s]\n", "Mr.Kim", 20, "99-111-4240");

    int ages[AGES_SIZE] = { 10, 15, 20 };
    // ages[10] = 0;  // <-- bug
    int sum = 0;

    for(int i = 0; i < AGES_SIZE; i++) {
        sum += ages[i];
        printf("ages[%d] = %d --> sum = %d\n", i, ages[i], sum);
    }
    printf("sum = %d\n", sum);
    printf("average = %f\n", ( (double)sum / AGES_SIZE ) );

    test_memset();  // 강제 종료 오류 발생용

    return 0;
}


#define HEAP_SIZE  (50 * sizeof(int))  // 수식은 괄호 () 로 묶었음을 눈여겨 보세요
 
void test_memset() {
    int *heapArray = NULL;
   
    heapArray = (int *)malloc(HEAP_SIZE);  // <-- 일부러 주석 처리하였음
    printf("memset 전---------------------\n");
    printf("heapArray[0] = %d\n", heapArray[0]);
    printf("heapArray[1] = %d\n", heapArray[1]);
 
    memset(heapArray, 0, HEAP_SIZE);  // 메모리를 HEAP_SIZE 만큼 0으로 채움
   
    printf("0 으로 memset 후--------------\n");
    printf("heapArray[0] = %d\n", heapArray[0]);
    printf("heapArray[1] = %d\n", heapArray[1]);
 
    free(heapArray);
    // free(heapArray);  // <-- Segmentation 오류
}
