// =====================================
// App1 : UP and DOWN Game
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdlib.h> // rand, srand 의 함수 선언이 들어 있음
#include <time.h>   // time 의 함수 선언이 들어 있음

int main() {
    int tries;   // 시도 횟수
    int number;  // 컴퓨터의 값
    int guess;   // 추측 값

    tries = 0;
    guess = 0;
    
    // 1 : 임의로 값을 하나 선택
    srand(time(NULL));
    number = ( rand() % 100 ) + 1;  // 난수 생성 [1 ~ 100]

    while(guess != number) {
        // 2 : 추측 값을 입력
        printf("추측한 값을 입력하세요 (1~100) : ");
        scanf("%d", &guess);

        tries = tries + 1;

        // 3 : 비교 결과 출력
        if(guess > number) {
            printf("UP\n\n");
        }
        else if(guess < number) {
            printf("DOWN\n\n");
        }
        else {
            printf(">>> 축하합니다! 맞췄습니다. 총 시도 횟수 [%d]회\n", tries);
        }
    }

    return 0;
}
