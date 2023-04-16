// =====================================
// warming up project : 홀짝 Game
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Guess It 게임 규칙:
    // -----------------
    // 컴퓨터가 임의로 생성한 숫자가
    // 짝수인지 홀수인지 여러분이 알아 맞추는 게임입니다.
    // 맞추면 여러분의 승리, 못 맞추면 컴퓨터의 승리!

    // ①. 컴퓨터는   "임의의 숫자를 생성" 합니다.
    int randomNumber;

    srand(time(NULL));  // set seed
    randomNumber = rand();
    // printf("컴퓨터가 생성한 수 = %d\n", randomNumber);
    // printf("RAND_MAX = %d\n", RAND_MAX);

    // ②. 플레이어는 "그 숫자가 짝수인지 홀수인지 예측을 입력" 합니다.
    int guess = 0;

    printf("[홀수 짝수 게임]\n");
    printf("당신의 추측은? (입력 예: 0 은 짝수, 1 은 홀수) : ");
    scanf("%d", &guess);

    // ③. 컴퓨터는   "누가 승리했는지 판단" 합니다.
    int answer = randomNumber % 2;  // 홀짝 판단 : 0 이면 짝수, 1 이면 홀수

    printf("컴퓨터가 생성한 수 = %d\n", randomNumber);
    if(guess == answer) {
        printf(">>> You win!\n");
    } else {
        printf(">>> Computer win!\n");
    }
}
