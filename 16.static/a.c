#include <stdio.h>
#include "common.h"
// #include "b.h"

char *globalVariable;  // 전역변수

// b.c 의 함수 선언문
extern void test(void);




// static 변수 테스트용 함수
void testStaticInFunction() {
    int localVariable = 10;
    static int staticLocalVariable = 10;

    localVariable += 5;
    staticLocalVariable += 5;

    printf(">>> [localVariable, staticLocalVariable] = [%d, %d]\n",
        localVariable, staticLocalVariable);
}

int main() {
    globalVariable = "string from main function";

    printf(">>> before call test(): globalVariable --> %s\n", globalVariable);
    test();
    printf(">>> after  call test(): globalVariable --> %s\n", globalVariable);

    printf("test Static Local Variable in Function:\n");
    for(int i = 0; i < 10; i++) {
        testStaticInFunction();
    }

    // static 사용 예시1: 정상적으로 작동하는 예
    char today[ITEM_SIZE] = { 0, };
    char *filename;
    strcpy(today, getTimeString(YYYYMMDD_HHmmSS));
    filename = getMasterFilename(today);
    printf("master file name=[%s]\n", filename);

    // static 사용 예시2: 비정상적으로 작동하는 예
    filename = getMasterFilename(getTimeString(YYYYMMDD_HH));
    printf("master file name=[%s]\n", filename);

    // 적절한 해결책
    char today2[ITEM_SIZE] = { 0, };
    char filename2[ITEM_SIZE] = { 0, };
    getMasterFilename_O( filename2, ITEM_SIZE, getTimeString_O(today2, ITEM_SIZE, YYYYMMDD_HH) );
    printf("master file name=[%s]\n", filename2);

    return 0;
}
