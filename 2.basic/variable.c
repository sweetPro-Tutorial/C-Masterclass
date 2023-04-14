#include <stdio.h>
#include <math.h>

int main() {
/* 
    char *myName = "thankyouC";
    myName = "YoungHee";
    int thisYear = 2022;
    thisYear = 2023;  // 상수는 값을 덮어쓸 수 없음

    printf("Hello %s %d\n", myName, thisYear);
*/

    // 정수 integer, 실수 real number
    int trial = 36.5;  // 시도 횟수
    printf("trial = %d\n", trial);

    printf("size of int = %lld bytes\n", sizeof(int));

    int myShort = 300000;  // 2001 => 300000    
    int myInt = 300000;
    // long myLong = 1234567890;
    long long myLongLong = myInt;
    printf("myShort = %d\n", myShort);
    printf("myLongLong = %lld\n", myLongLong);

    // 정수 타입들: 
    // short (16 bit), int (32 bit), long (64 bit), long long (64 bit)
    printf("Size of short int = %lld bytes\n", sizeof(short int));
    printf("Size of int = %lld bytes\n", sizeof(int));
    printf("Size of long int = %lld bytes\n", sizeof(long int));
    printf("Size of long long int = %lld bytes\n", sizeof(long long int));

    // short     -32,768 to 32,767
    // int       -2,147,483,648 to 2,147,483,647
    // long      -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 또는
    //           -2,147,483,648 to 2,147,483,647 (윈도우의 경우)
    // long long -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807




    printf("size of float = %lld bytes\n", sizeof(float));
    printf("size of double = %lld bytes\n", sizeof(double));
    printf("size of long double = %lld bytes\n", sizeof(long double));

    float myFloat = 36.1;
    double myDouble = 3.14159265359;
    long double myLongDouble = 3.14159265359;

    // float    -3.402823466 x 10e38 to 3.402823466 x 10e38
    // double   -1.7976931348623158 x 10e308 x 1.7976931348623158 x 10e308

    // 유효 자릿수:
    // float    -3.402823466 x 10e38 to 3.402823466 x 10e38
    // double   -1.7976931348623158 x 10e308 x 1.7976931348623158 x 10e308


    // 저장 오차 발생
    myFloat = 987654.321;
    printf("myFloat = %f\n", myFloat);  // 기대한 값은 987654.321

    // 계산 오차 발생
    myFloat = myFloat + 0.05;
    printf("myFloat + 0.05 = %f\n", myFloat);  // 기대한 값은 987654.371
                                               // 또는 987654.3625

    // 해결책: float --> double
    myDouble = 987654.321;
    printf("myDouble  = %f\n", myDouble);

    myDouble = myDouble + 0.05;
    printf("myDouble + 0.05 = %f\n", myDouble);


    //
    // error sample 2:
    //
    float dollar1 = 0.99;
    float dollar2 = 1.23;
    float dollar3 = 4.20;
    int pennies1 = dollar1 * 100;
    int pennies2 = dollar2 * 100;
    int pennies3 = dollar3 * 100;  

    printf("dollar3 * 100 = %f\n", dollar3 * 100);  // 419.999969
    // printf("pennies1, pennies2, pennies3=%d,%d,%d\n", pennies1, pennies2, pennies3);


    // 해결책: 버림 오차 방지 위해 round 함수 사용해 반올림함.
    pennies1 = round(dollar1 * 100);
    pennies2 = round(dollar2 * 100);
    pennies3 = round(dollar3 * 100);
    printf("pennies1, pennies2, pennies3=%d,%d,%d\n", pennies1, pennies2, pennies3);


}
