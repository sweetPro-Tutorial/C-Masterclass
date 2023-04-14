// =====================================
// 상수와 변수, 데이터 타입용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================


#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


int main() {
    printf("Hello world\n");


    // 이것은 주석입니다.
    // 주석은 사람을 위해 작성하며 설명문 역할을 합니다.
    // 슬래쉬 두개로 한줄짜리 주석을 만듭니다.
    /* 이것은 여러줄 짜리 주석입니다.
       범위로
       주석을
       만들려면
       슬래쉬 스타와 스타 슬래쉬로
       범위를 감싸면 됩니다. */
       
    // 문자열 변수 선언입니다.
    char *myName = "thankyouC";
    myName = "YoungHee";  // 변수에는 새 값을 할당할 수 있습니다.
 
    // int 변수 선언입니다.
    // 선언과 함께 초기값을 주는 것은 좋은 습관입니다.
    int thisYear = 2023;
    thisYear = 2024;  // 변수에는 새 값을 할당할 수 있습니다.


    // printf 함수는 '출력 포맷'을 사용합니다.
    // 출력 포맷은 출력할 문자열 사이에 데이터를 끼워 넣고 싶을 때 사용합니다.
    // 사용법은 % 뒤에 값의 종류를 기입합니다.
    // %s 위치에는 문자열 myName, 여기서는 "YoungHee"이 끼워 넣어지고,
    // 그 다음의 %d 에는 thisYear의 값, 여기서는 2024 이 끼워 넣어집니다.
    printf("Hello %s %d\n", myName, thisYear);
 
    // Visual Studio Code 의 'TODO TREE' 확장팩을 사용하면
    // 앞으로 해야할 일을 관리할 수 있습니다.
    // 실제 현장에서 TODO 관리는 중요합니다.
    // TODO 는 다음과 같이 주석을 사용해서 기입합니다.
    // TODO: 예외처리 로직 추가요
    // TODO: gets 함수는 향후 폐지 예정이므로 변경요
 
    int trial = 0;
    trial = 36.5;


    printf("trial = %d\n", trial);
 
    // 정수 타입들:
    // short (16 bit), int (32 bit), long (64/32 bit), long long (64 bit)
    int myShort = 300000;
    int myInt = 300000;
    long myLong = 1234567890;
    long long myLongLong = myInt;
 
    printf("myLongLong=%lld\n", myLongLong);
 
    // 정수 타입의 값의 범위:
    // short     -32,768 to 32,767
    // int       -2,147,483,648 to 2,147,483,647
    // long      -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 또는
    //           -2,147,483,648 to 2,147,483,647 (윈도우의 경우)
    // long long -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807


    // 정수 타입에 필요한 메모리 크기:
    // sizeof 연산자를 사용하면 알 수 있습니다.
    // 정수 타입 간의 크기 관계:
    // short int  ≤  int  ≤  long int  ≤  long long int
    printf("size of short=%lld bytes\n", sizeof(short));  // %lld --> 리눅스에서는 %ld
    printf("size of int=%lld bytes\n", sizeof(int));
    printf("size of long=%lld bytes\n", sizeof(long));
    printf("size of long long=%lld bytes\n", sizeof(long long));
 
    // 실수 타입들:
    // 표현 가능한 값의 범위:
    // float    -3.402823466 x 10e38 to 3.402823466 x 10e38
    // double   -1.7976931348623158 x 10e308 x 1.7976931348623158 x 10e308


    // 실수 타입을 위해 필요한 메모리 크기:
    // float (32 bit), double (64 bit), long double (128/64 bit)
    // long double 은 사용하지 마세요.
    printf("size of float = %lld bytes\n", sizeof(float));
    printf("size of double = %lld bytes\n", sizeof(double));
    printf("size of long double = %lld bytes\n", sizeof(long double));
 
    // 실수 타입의 유효 자릿수:
    // float 는 7자리. (예: 1.234567)
    // double 은 16자리. (예: 1.234567890123456)


    //
    // error sample 1:
    //
    // 저장 오차 발생
    float myFloat = 987654.321;
    printf("myFloat = %f\n", myFloat);  // 기대한 값은 987654.321


    // 계산 오차 발생
    myFloat = myFloat + 0.05;
    printf("myFloat + 0.05 = %f\n", myFloat);  // 기대한 값은 987654.371
                                               // 또는 987654.3625


    // 해결책: float --> double
    double myDouble = 987654.321;
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
    // 1) dollar3 * 100 에서 계산 오차 발생:
    //    420.0 --> 419.999969
    // 2) int pennies3 = dollar3 * 100; 에서 저장오차 발생:
    //    419.999969 --> 419
    printf("dollar3 * 100 = %f\n", dollar3 * 100);  // 419.999969
    printf("pennies1, pennies2, pennies3=%d,%d,%d\n", pennies1, pennies2, pennies3);


    // 해결책: 버림 오차 방지 위해 round 함수 사용해 반올림함.
    // 이 함수는 math.h 헤더 파일에 선언되어 있습니다.
    // math 라이브러리를 사용하기 위해 컴파일 할 때 -lm 옵션을 주었습니다.
    pennies1 = round(dollar1 * 100);
    pennies2 = round(dollar2 * 100);
    pennies3 = round(dollar3 * 100);


    printf("pennies1, pennies2, pennies3=%d,%d,%d\n", pennies1, pennies2, pennies3);


    // boolean
    bool isConnected = true;
    isConnected = false;


    // character
    char alphabetChar = 'A';
    char numberChar = '0';


    // string type의 문자열 상수
    "Hello world";


    // 문자열 상수의 값은 읽기 전용이므로 쓰기를 시도하면
    // 실행할 때 segmentation fault error 가 발생하고
    // 프로그램이 강제종료 됩니다.
    // "SweetPro"[0] = 's';  // segmentation fault error


    // 문자열의 구성요소는 대괄호와 인덱스를 사용해서 접근합니다.
    // 인덱스 0부터 시작합니다.
    // "SweetPro"[0] 은 "SweetPro" 의 첫번째 문자 'S' 를 가리키고
    // "SweetPro"[7] 은 "SweetPro" 의 마지막 문자 'o' 입니다.
    printf("1st character in string = %c\n", "SweetPro"[0]);
    printf("last character in string = %c\n", "SweetPro"[7]);


    // 문자열의 길이 계산은 자주 사용하는 기능이므로
    // C 언어는 표준 함수 strlen 을 제공합니다.
    // 함수는 string.h 헤더 파일에 선언되어 있습니다.
    int index = strlen("SweetPro") - 1;
    printf("last character in string = %c\n", "SweetPro"[index]);


    // string variable
    myName = "SweetPro";
    char firstCharInString = myName[0];  // 사용방법 동일
    printf("1st character in string = %c\n", firstCharInString);


    // myName[1] = 'x';  // segmentation fault error
}
