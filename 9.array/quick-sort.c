// =====================================
// 표준함수 qsort용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdlib.h>
  
#define DATA_SIZE   10
 
int compare(const void * a, const void * b);  // qsort용 비교 함수
void printData(int *data);
 
int main() {
    // sorting 예:
    // ----------
    int data[DATA_SIZE] = { 3, 5, 7, 2, 4, 9, 10, 8, 1, 6 };
 
    printf("정렬 전 data:\n");
    printData(data);
   
    // qsort usage example:
    // -------------------
    qsort(data, DATA_SIZE, sizeof(int), compare);

    printf("정렬 후 data:\n");
    printData(data);
 
    return 0;
}

// qsort용 비교 함수
int compare(const void * a, const void * b) {
    int value1 = *(int*)a;  // *( (int*)a );
    int value2 = *(int*)b;
    // int compareRule = value1 - value2;  // 오름차순용
    int compareRule = value2 - value1;  // 내림차순용
    printf(">>> compare result: %d,%d --> %d\n", value1, value2, compareRule);  // test log
 
    return compareRule;
}

void printData(int *data) {
    for(int i = 0; i < DATA_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

