// =====================================
// App1 : 문자용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdio.h>

// 눈에 보이지 않는 문자
#define BELL 7
#define TAB  9
#define LF   10

int main() {
    char c1, c2, c3, c4, c5;
    c1 = 'E';
    c2 = 'l';
    c3 = 'i';
    c4 = 'z';
    c5 = 'a';

    // 보이는 문자
    printf("친구이름(문자) = %c %c %c %c %c\n", c1, c2, c3, c4, c5);
    printf("        (숫자) = %d %d %d %d %d\n", c1, c2, c3, c4, c5);

    // 문에 보이지 않는 제어문자
    printf("줄바꿈이나 %c 텝은 %c 눈에 보이지 않는 문자입니다.\n", LF, TAB);
    printf("%c%c%c\n", BELL, BELL, BELL);  // 컴퓨터 내장 스피커에서 삑 소리 세 번

    // C 언어의 내장문자:
    // ================
    printf("Keep track of your character, for it becomes your future.\n");
    // \n 출력 예: Keep track of your character, for it becomes your future.

    printf("Keep track of your character,\0 for it becomes your future.\n");
    // \0 출력 예: Keep track of your character,

    printf("Keep track of your character,\t for it becomes your future.\n");
    // \t 출력 예: Keep track of your character,       for it becomes your future.

    printf("Keep track of your character,\r for it becomes your future.\n");
    // \r 출력 예:  for it becomes your future.,

    printf("Keep track of your character,\\ for it becomes your future.\n");
    printf("Keep track of your character,\" for it becomes your future.\n");
    printf("Keep track of your character,\' for it becomes your future.\n");
    // \\ 출력 예: Keep track of your character,\ for it becomes your future.
    // \" 출력 예: Keep track of your character," for it becomes your future.
    // \' 출력 예: Keep track of your character,' for it becomes your future.


    // 입력한 문자를 아스키 코드로 보여주는 프로그램
    // =========================================
    char ch;
    const char enterKey = '\n';

    printf("[ 키보드에서 입력한 문자의 아스키 코드를 보여주는 프로그램 ]\n");
    printf("문자를 입력 후 Enter 키를 누르세요 : ");
    ch = getchar();
    while(ch != enterKey) {
        printf("'%c' = [%3d] [0x%02X]\n", ch, ch, ch);
        ch = getchar();
    }
    printf("마지막 문자는 Enter 키 = [%d] [0x%02X]\n", ch, ch);    

}
