// =====================================
// 배열 정렬용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
  
#define DATA_SIZE   10
 
// 숫자를 쭉 보면서 그 중에 가장 작은 것을 찾는 기능
int findSmallest(int *data, int start);
void swap(int *data, int start, int found);
void printData(int *data);
 
int main() {
    // sorting 예:
    // ----------
    int data[DATA_SIZE] = { 3, 5, 7, 2, 4, 9, 10, 8, 1, 6 };
 
    printf("정렬 전 data:\n");
    printData(data);
   
    // 총 n - 1 회 반복합니다:
    for(int i = 0, foundIndex = 0; i < (DATA_SIZE - 1); i++) {
        //   교체된 앞의 값들을 제외한 나머지 값들을 쭉 보면서
        //   그 중에 "가장 작은 것"을 찾아
        foundIndex = findSmallest(data, i);
        //   "맨 앞 자리와 교체" 합니다.
        swap(data, i, foundIndex);
    }


    // // 총 n - 1 회 반복합니다:
    // for(int i = 0, foundIndex = 0; i < (DATA_SIZE - 1); i++) {
    //     //   교체된 앞의 값들을 제외한 나머지 값들을 쭉 보면서
    //     //   그 중에 "가장 작은 것"을 찾아
    //     foundIndex = i;
    //     for(int j = i + 1; j < DATA_SIZE; j++) {
    //         if(data[foundIndex] > data[j]) {
    //             foundIndex = j;
    //         }
    //     }
    //     //   "맨 앞 자리와 교체" 합니다.
    //     swap(data, i, foundIndex);
    // }
 
    printf("정렬 후 data:\n");
    printData(data);
 
    return 0;
}
 
void swap(int *data, int start, int found) {
    int smallestValue = data[found];
    data[found] = data[start];
    data[start] = smallestValue;
}
 
// 숫자를 쭉 보면서 그 중에 가장 작은 것을 찾는 기능
int findSmallest(int *data, int start) {
    int smallest = start;
 
    for(int index = start + 1; index < DATA_SIZE; index++) {
        if(data[smallest] > data[index]) {
            smallest = index;
        }
    }
    return smallest;
}
 
void printData(int *data) {
    for(int i = 0; i < DATA_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

