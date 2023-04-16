// =====================================
// 반복 설명용 sample code
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>


int main() {
    //
    // while sample 1:
    //
    // "While there's life, there's hope."
    // "삶이 있는 한 희망은 있다."
    // =======================
    // while(살아있다)
    // begin
    //     희망은 있다.
    // end


    bool isLiving = true;
    int age = 1;


    while(isLiving == true) {
        printf("현재 나이 : %d", age);


        printf("\t>>>희망은 있다\n");  // 반복 대상


        // 탈출조건 처리:
        age = age + 1;  // 반복할 때마다 나이를 한살씩 더 먹습니다.
        if (age > 100) {
            isLiving = false;
        }
    }
    printf("삶이 끝나다\n");


    //
    // while sample 2:
    //
    int counter = 1;
    int sum = 0;

    while(counter <= 10) {  
        sum = sum + counter;  // 반복할 명령문
        counter = counter + 1;  // 탈출조건 처리용
    }
    printf("sum = %d\n", sum);


    //
    // for 문의 사용법:
    //     for(조건변수초기화; 조건식; 조건변화식)
    //     {
    //         실행할 명령문;
    //     }
    //
    // while sample 2 를 for 문으로 바꾸면:
    for (int counter = 1, sum = 0 ; counter <= 10; counter = counter + 1) {  // 조건변화식 --> 증감식
        sum = sum + counter;
    }
    printf("sum = %d\n", sum);


    //
    // 무한 반복!!!
    //
    // sample1:
    // 아래 printf 명령문 무한 반복됨. Ctrl + C 눌러 강제종료 하세요!
    //
    // for ( ; ; ) {
    //     printf("%d ", rand());
    // }


    // sample2:
    // 아래 printf 명령문 무한 반복됨. Ctrl + C 눌러 강제종료 하세요!
    //
    // while(true) {
    //     printf("%d ", rand());
    // }
}