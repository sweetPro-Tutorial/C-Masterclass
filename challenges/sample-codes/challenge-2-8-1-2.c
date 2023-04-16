// =====================================
// 도전과제 2.8.1의 샘플 코드 2
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

int main() {
    int number1 = 0;
    int number2 = 0;

    printf("[두 수를 읽은 후 이를 더하는 프로그램]\n");
    printf("두 개의 수를 입력하세요 (예: 1 99) : ");
    scanf("%d %d", &number1, &number2);

    printf(">>> %d + %d = %d\n", number1, number2, (number1 + number2) );
}
