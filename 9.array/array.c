// =====================================
// array용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>

#define LIST_SIZE 3


int makeAverage(int *ageList);   // better
// int makeAverage(int ageList[]);  // 사용 가능

int getEndOfMonth(int year, int month);  // 그 달의 마지막 날을 반환
bool isLeapYear(int year);  // 윤년인지 확인


int main() {
    // 일반 변수를 사용 시:
    int age1 = 70;
    int age2 = 57;
    int age3 = 88;

    printf("[평균 계산기]\n");
    printf(">>> 평균 = %4.1f\n", ( (age1 + age2 + age3) / 3.0) );

    // 배열 변수를 사용 시:
    int ageList[LIST_SIZE] = { 70, 57, 88 };
    printf(">>> 평균 = %4.1f\n", ( (ageList[0] + ageList[1] + ageList[2]) / 3.0) );

    // 배열과 루프를 사용 시:
    int sum = 0;
    for(int i = 0; i < LIST_SIZE; i++) {
        sum = sum + ageList[i];
    }
    printf(">>> 평균 = %4.1f\n", (sum / 3.0) );


    // 선언하면서 초기값 주기:
    // --------------------
    // ① 배열크기에 맞게 준 경우:
    // int scores[3] = { 4, 3, 5 };
    //   구성요소별로 초기화된 값:
    //     scores[0] = 4
    //     scores[1] = 3
    //     scores[2] = 5


    // ② 배열크기보다 적게 준 경우:
    // int scores[3] = { 4, };
    //   구성요소별로 초기화된 값:
    //     scores[0] = 4
    //     scores[1] = 0
    //     scores[2] = 0    
    // 전부 0 으로 초기화 하기 싶을 경우:
    // int scores[3] = { 0, };


    // ③ 배열크기보다 많이 준 경우:
    // int scores[3] = { 4, 3, 5, 9 };  // <<< warning excess elements in array...


    // ④ 배열크기 없이 초기값을 준 경우:
    int scores[] = { 4, 3, 5 };
    //   구성요소별로 초기화된 값:
    //     scores[0] = 4
    //     scores[1] = 3
    //     scores[2] = 5    


    // 배열을 사용할 때 초기값을 준 경우:
    int days[13] = { 0, };  // 참고: 맨 첫번째 구성요소(days[0])는 사용안함
    int year = 2024;


    for(int month = 1; month <= 12; month++) {
        days[month] = getEndOfMonth(year, month);
        printf(">>> [%d]: days of month %2d = %d\n", year, month, days[month]);
    }


    // array name:
    // ==========
    // 배열 이름은 배열의 시작위치 주소값:
    printf("배열 이름 ageList                    = 0x%p\n", ageList);
    printf("첫번째 구성요소의 주소 &(ageList[0]) = 0x%p\n", &ageList[0]);


    // 배열의 두번째 구성요소의 값을 바꾸는 코드:
    //   From 사람이 작성한 코드:
    ageList[1] = 20;
    //   To 컴파일러가 바꾼 코드:
    *(ageList + 1) = 20;


    // 배열 이름에 간접연산자 * 적용하기:
    printf("ageList가 가리키는 곳의 값      = %d\n", *ageList);
    printf("첫번째 구성요소의 값 ageList[0] = %d\n", ageList[0]);


    // 배열 이름에 덧셈연산자 + 적용하기:
    printf("ageList + 1 이 가리키는 곳의 값 = %d\n", *(ageList + 1) );
    printf("두번째 구성요소의 값 ageList[1] = %d\n", ageList[1]);


    // 배열 이름에 sizeof 연산자 적용하기:
    printf("ageList 에 할당된 전체 메모리 = %d Byte\n", sizeof(ageList));
    printf("ageList 의 구성요소 하나의 크기 = %d Byte\n", sizeof(ageList[0]));


    // 배열 이름에 주소연산자 & 적용하기:
    printf("&ageList 의 값 = 0x%p\n", &ageList);


    // 배열 이름을 함수의 입력값으로 사용하기:
    // ===================================
    int bigArray[10000] = { 0, };


    int average = makeAverage(ageList);
    printf("average of ageList = %d\n", average);

}


int makeAverage(int *ageList) {
    int sum = 0;

    for (int i = 0; i < LIST_SIZE; i++) {
        printf(">>> ageList[%d] = %d\n", i, ageList[i]);
        sum = sum + ageList[i];
    }
   
    return (sum / LIST_SIZE);
}


int getEndOfMonth(int year, int month) {  // 그 달의 마지막 날을 반환
    int endOfMonth[13] = {
        0,  // 참고: 맨 첫번째 구성요소(days[0])는 사용안함
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if(month != 2) { return endOfMonth[month]; }
   
    return isLeapYear(year) ? endOfMonth[month] + 1 : endOfMonth[month];
}


bool isLeapYear(int year) {  // 윤년인지 확인
    if( (year % 400) == 0 ) { return true; }
    if( (year % 4) == 0  &&  (year % 100) != 0 ) { return true; }


    return false;
}
