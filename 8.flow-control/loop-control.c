// =====================================
// loop control용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>


// 5개의 숫자를 입력 받아 합을 계산
int sum5(void);

// 팩토리얼 : ① 반복형태로 개발할 경우
int factorialRepeat(int n);

// 팩토리얼 : ② 재귀형태로 개발할 경우
//   algorithm:
//     0!    = 1
//     n!    = n x (n - 1)!
int factorial(int n);


int main() {
/*
    while 문 사용법:
    ==============
    조건 초기화;
    while(조건식이 참이면) {
        실행할 명령문;
        조건 변화식;
    }

    무한반복:
    =======
    while(true) {
        실행할 명령문;
    }
 
*/

    char key;
    int counter = 0;

    printf("[Character Counter]\n");
    printf("입력 후 Enter 키를 누르세요 : ");
    while(true) {
        key = getchar();
        ++counter;  // 문자 하나를 읽어올 때마다 카운터 1 씩 증가

        if(key == '\n') {  // 탈출조건 확인
            break;
        }
    }
    printf(">>> 문자 수 = %d\n", counter);


    // continue test:
    printf("[5개의 숫자를 입력 받아 합을 계산]\n");
    printf(">>> 합계 = %d\n", sum5());


/*
    do while 문 사용법:
    =================
    do {
        실행할 명령문;
    } while(조건식이 참이면);  
*/

    // 1 ~ 10 까지의 수를 더하는 while 반복문:
    int i = 1;
    int sum = 0;
    while(i <= 10) {
        sum = sum + i;
        i++;
    }
    printf("sum,i = %d,%d\n", sum, i);

    // 1 ~ 10 까지의 수를 더하는 do while 반복문:
    i = 1;
    sum = 0;
    do {
        sum = sum + i;
        i++;
    } while(i <= 10);
    printf("sum,i = %d,%d\n", sum, i);

//     // goto 로 루프 만들기
// LABLE:
//     실행할 명령문;
//     goto LABLE;


    // 팩토리얼
    int n = 3;
    printf("[팩토리얼 계산기]\n"
           "계산할 팩토리얼을 입력하세요 (예: 3) : ");
    scanf("%d", &n);
    printf(">>> %d! = %d\n", n, factorialRepeat(n));
    printf(">>> %d! = %d\n", n, factorial(n));

    return 0;
}

// 팩토리얼 : ② 재귀형태로 개발할 경우
//   algorithm:
//     0!    = 1
//     n!    = n x (n - 1)!
int factorial(int n) {
    int result = 1;
    if(n == 0) {
        return 1;
    }
    else {
        result = n * factorial(n - 1);
    }
    return result;
}

// 팩토리얼 : ① 반복형태로 개발할 경우
int factorialRepeat(int n) {
    int result = 1;
   
    for(int i = n; i > 0; i--) {
        result = result * i;
    }
    return result;
}


// 5개의 숫자를 입력 받아 합을 계산
int sum5(void) {
    int i = 1;
    int number;
    int sum = 0;

    while(i <= 5) {
        printf("%d 번째 숫자를 입력하세요 : ", i);
        scanf("%d", &number);

        i++;
        // if(number == 0) { continue; }  // 입력값 0 은 건너 뜀
        if(number != 0) {
            sum = sum + number;
        }
    }

    return sum;
}

