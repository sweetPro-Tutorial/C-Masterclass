// =====================================
// typecasting용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

#define PI  3.14

int main() {
    int i = 10;
    double d;

    printf("[변환 전]\n");
    printf("정수 i 의 값은 %d\n", i);
    printf("상수 PI 의 값은 %.2f\n", PI);

    // 타입 변환은 "임시 변환" 임:
    printf("\n[타입 변환]\n");
    d = (double)i;
    printf(">>> 명령문 d = (double)i; 수행결과 d 에 저장되는 값은 %.1f\n", d);
    i = (int)PI;
    printf(">>> 명령문 i = (int)PI; 수행결과 i 에 저장되는 값은 %d\n", i);
    printf(">>> (int)12345.6789 --> 값이 %d 으로 임시 변환됨\n", (int)12345.6789);

    printf("\n[변환 후]\n");
    printf("정수 i 의 값은 %d\n", i);
    printf("상수 PI 의 값은 %.2f\n", PI);

    // 타입 변환의 예외: l-value 는 타입 변환 불가능
    // l-value   r-value
    // -------   ---
            i  =  PI;
    // (double)i  =  PI;  // compile error

    return 0;
}
