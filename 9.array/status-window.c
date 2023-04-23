// =====================================
// array example1 - 용사의 상태창용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

/*
실행 예:
[ 상태창 STATUS ]
레벨    생명    체력    방어    지능    민첩    골드
----    ----    ----    ----    ----    ----    ----
1       100     22      23      21      23      10
*/
 
#include <stdio.h>
#include <string.h>
 
#define STATES_SIZE 7
#define NAME_LENGTH 14
#define DATA_SIZE   10


// 이름 입력용
void inputName(char *herosName);

void printData(int *data);
 
int main() {
    // 상태 초기화: 각각의 상태값은
    //   차례로 레벨, 생명, 체력, 방어, 지능, 민첩, 골드
    int states[STATES_SIZE] = { 1, 100, 22, 23, 21, 23, 10 };  
    // 문자열은 사용전에 0 으로 초기화
    char herosName[NAME_LENGTH + 1] = { 0, };  

    strcpy(herosName, "Gil Dong");
    printf(">>> herosName = %s\n", herosName);

    // 용사의 이름 입력
    inputName(herosName);
 
    // 상태창 출력
    printf( "[ 상태창 STATUS ]\n"
            "=================\n");
    printf("이름\n");
    printf("----\n");
    printf("%s\n\n", herosName);

    printf( "레벨\t생명\t체력\t방어\t지능\t민첩\t골드\n"
            "----\t----\t----\t----\t----\t----\t----\n" );
    for(int i = 0; i < STATES_SIZE; i++) {
        printf("%d\t", states[i]);
    }
    printf("\n");
 
   
    // C 언어가 제공하는 표준 파일 포인터 3가지:
    // -------------------------------------
    //   stdin  : 표준 입력장치로부터(예: 키보드) 입력용 파일 포인터
    //   stdout : 표준 출력장치로(예: 모니터) 출력용 파일 포인터
    //   stderr : 표준 오류출력장치로(예: 모니터) 출력용 파일 포인터


    // fgets 함수가 읽은 문자열을 반환하는 기준:
    // --------------------------------------
    // ? 줄 바꿈(LF: Line Feed) 을 발견하면 읽기를 멈춤.
    // ? 파일 끝(EOF: End Of File) 에 도달하면 멈춤.
    // ? 버퍼의 크기 - 1 (예: NAME_LENGTH - 1) 개의 문자를 읽고 난 후에 멈춤.
    //   이때 나머지 1 바이트는 널 문자 저장용임.


    return 0;
}

void printData(int *data) {
    for(int i = 0; i < DATA_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}


// 이름 입력용
void inputName(char *herosName) {
    printf("이름을 입력하고 enter 키를 누르세요(예: Hannibal) : ");
    fgets(herosName, NAME_LENGTH + 1, stdin);
    herosName[strlen(herosName) - 1] = '\0';
}
