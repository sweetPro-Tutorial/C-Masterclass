// =====================================
// 변수의 영역다툼 Scope용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================


#include <stdio.h>


int globalVar = 1;  // 전역변수: main 함수의 블록 밖에 선언했음


int main() {  // <<< main 블록 시작
    int mainBlockVar = 10;

    {  // <<< inner 블록 시작
        int innerBlockVar;

        innerBlockVar = mainBlockVar * 10;
        printf("main block variable = %d\n", mainBlockVar);   // 사용가능 : 여기도 main 블록 내부임
        printf("inner block variable = %d\n", innerBlockVar); // 사용가능 : inner 블록 내부임
    }  // <<< inner 블록 종료

    printf("main block variable = %d\n", mainBlockVar);   // 사용가능 : main 블록 내부임
    // printf("inner block variable = %d\n", innerBlockVar); // 에러 : 선언된 블록 밖임

}  // <<< main 블록 종료