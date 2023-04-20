// =====================================
// 상자의 용도를 결정하는 type용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================


#include <stdio.h>
#include <stdbool.h>
#include <complex.h>


int main() {
    // 정수 타입 3가지: 정수, 문자, 불리언
    // int age = 17;
    // char age = 150;
    unsigned char age = 150;
    char sex = 'M';  // 성별 : 'M' = 남성, 'F' = 여성
    bool isMarried = false;  // 결혼여부




    printf("Personal Information\n"
           "====================\n");
    printf("나이 : %u\n", age);
    printf("성별 : %c (M = 남성, F = 여성)\n", sex);
    printf("결혼 : %d (0 = 미혼, 1 = 기혼)\n", isMarried);


    // 저장 가능한 값의 범위:
    // ===================
    // char           -128 to 127
    // unsigned char     0 to 255


    // short       -32,768 to 32,767
    // unsigned short    0 to 65,535


    // int  -2,147,483,648 to 2,147,483,647
    // unsigned int      0 to 4,294,967,295


    // long      -9,223,372,036,854,775,808 to  9,223,372,036,854,775,807 또는
    //                      -2,147,483,648  to  2,147,483,647 (윈도우의 경우)
    // unsigned long                     0  to 18,446,744,073,709,551,615 또는
    //                                   0  to  4,294,967,295 (윈도우의 경우)


    // long long -9,223,372,036,854,775,808 to  9,223,372,036,854,775,807
    // unsigned long long                 0 to 18,446,744,073,709,551,615


    // bool 은 unsigned 가 없습니다.




    // unsigned 사용시 주의사항:
    //  아래 조건 변수 i 는 마이너스가 될 수 없으므로 무한 루프에 빠짐.
    // for(unsigned int i = 100; i >= 0; i--) {
    //     printf("%u\n", i);
    // }




    // 실수 타입 2가지: 실수, 복소수
    // ---------------------------
    // 실수값 저장용 타입:   double         또는 float
    // 복소수값 저장용 타입: double complex 또는 float complex
    //                     사용 시 헤더파일 <complex.h> 필요




    // 단위 변환: kilo to mile
    // ----------------------
    // 변수 선언
    // double kilo;
    // double mile;
    // double lowerLimit = 0;  // 범위 하한
    // double upperLimit = 300;  // 범위 상한
    // double step = 20;  // 범위 증가분


    // printf("[Kilometer-Mile mapping table]\n\n"
    //        " km   mile\n"
    //        "---  -----\n");


    // for(kilo = lowerLimit; kilo <= upperLimit; kilo = kilo + step) {
    //     mile = kilo * 0.621371;
    //     // printf("%3.0f %6.1f\n", kilo, mile);
    //     printf("%3.0f %6.0f\n", kilo, mile);
    // }




    // 결과값이 소수점 이하까지 나올 필요가 없는 경우:
    // -------------------------------------------
    // 방법1: 출력할 때 소수점 이하를 출력하지 않는 것입니다.
    //        printf("%3.0f %6.0f\n", kilo, mile);
    // 방법2: 실수 타입 대신 정수 타입을 사용하는 것입니다.
    int kilo;
    int mile;
    int lowerLimit = 0;  // 범위 하한
    int upperLimit = 300;  // 범위 상한
    int step = 20;  // 범위 증가분


    printf("[Kilometer-Mile mapping table]\n\n"
           " km   mile\n"
           "---  -----\n");


    for(kilo = lowerLimit; kilo <= upperLimit; kilo = kilo + step) {
        mile = kilo * 0.621371;
        // printf("%3.0f %6.1f\n", kilo, mile);
        printf("%3d %6d\n", kilo, mile);
    }




    // float 와 double 타입으로 표현 가능한 값의 범위:
    // --------------------------------------------
    // float: 4 bytes
    //   가장   큰 양수  3.402823466e38
    //   가장 작은 양수  1.175494351e–38
    //   가장   큰 음수 -1.175494351e–38
    //   가장 작은 음수 -3.402823466e38
    // double: 8 bytes
    //   가장   큰 양수  1.7976931348623158e308
    //   가장 작은 양수  2.2250738585072014e–308
    //   가장   큰 음수 -2.2250738585072014e–308
    //   가장 작은 음수 -1.7976931348623158e308




    // 실수값은 근사값 입니다.
    for(double d = 0.0; d <= 1.0; d = d + 0.1) {
        if (d == 0.3) {  // 근사값끼리 비교라 if문 실행안됨.
            printf(">>> d is 0.3\n");
        }
    }








    // 복소수 표기:
    // x + yI;


    // 복소수 사칙연산:
    // --------------
    // 변수 선언
    double complex z1 = 1.0 + 3.0 * I;  // z1 = 1 + 3i 를 나타냄. 대문자 I 에 주의
    double complex z2 = 1.0 - 5.0 * I;  // z2 = 1 - 4i 를 나타냄. 대문자 I 에 주의
    double complex sum;         // 덧셈 결과값
    double complex difference;  // 뺄셈 결과값
    double complex product;     // 곱셈 결과값
    double complex quotient;    // 나눗셈 결과값
    double complex conjugate;   // 복소켤레값


    // 사칙연산
    sum = z1 + z2;
    difference = z1 - z2;
    product = z1 * z2;
    quotient = z1 / z2;
    conjugate = conj(z1);


    printf("[복소수 사칙연산]\n\n");
    printf("초기값 :\n");
    printf("   z1 = %.2f %+.2fi\n", creal(z1), cimag(z1));
    printf("   z2 = %.2f %+.2fi\n", creal(z2), cimag(z2));
    printf("합 : z1 + z2 = %.2f %+.2fi\n", creal(sum), cimag(sum));
    printf("차 : z1 - z2 = %.2f %+.2fi\n", creal(difference), cimag(difference));
    printf("곱 : z1 x z2 = %.2f %+.2fi\n", creal(product), cimag(product));
    printf("몫 : z1 / z2 = %.2f %+.2fi\n", creal(quotient), cimag(quotient));
    printf("z1의 복소켤레값 = %.2f %+.2fi\n", creal(conjugate), cimag(conjugate));


    // 복소수를 사용할 때 주의사항:
    //   삼각함수, 지수함수, 제곱근함수와 같은 함수는 복소수용을 사용해야 함.
    // 예:
    //   csin(z1)
    //   cexp(z1 * I)
    //   csqrt(-2)


    return 0;
}
