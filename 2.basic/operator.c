#include <stdio.h>
int main()
{
    // 일상생활의 사칙연산자: +, -, x, / 또는 ÷
    // 10 + 3
    // 10 - 3
    // 10 x 3
    // 10 / 3 또는 10 ÷ 3


    // C 언어의 사칙연산자:  +, -, *, /, %


    int x = 10;
    // x x 2; // 잘못 쓴 계산식
    printf("계산 전: 용돈 = %d\n", x);
    // x * 2;
    x = x * 2;  // <<< 수정
    printf("계산 후: 용돈 = %d\n", x);


    // 값의 종류(변환문자):
    //   정수: d = short 및 int 값용, ld = long 값용, lld = long long 값용
    //   실수: f = float 및 double 값용, Lf = long double 값용
    //   문자: c = char 값용
    //   문자열: s = 문자열 값용


    // 사칙연산
    printf("[ 계산식 출력 예제 프로그램 ]\n");
    printf("10 + 3 의 결과값은 %d 입니다\n", 10 + 3);
    printf("10 - 3 의 결과값은 %d 입니다\n", 10 - 3);
    printf("10 * 3 의 결과값은 %d 입니다\n", 10 * 3);
    printf("10 / 3 의 결과값은 %f 입니다\n", 10 / 3);  // 포맷문자와 불일치


    printf("10 / 3 의 결과값은 %f 입니다\n", 10.0 / 3.0);  // %f에 일치


    // 실수의 나누기
    printf("21.0 / 5.0 의 결과값은 %f 입니다\n", 21.0 / 5.0);
    printf("21.0 / 5   의 결과값은 %f 입니다\n", 21.0 / 5);
    printf("21   / 5.0 의 결과값은 %f 입니다\n", 21 / 5.0);


    // 정수의 나누기
    printf("21   / 5   의 결과값은 %d 입니다\n", 21 / 5);


    // 정수의 나누기: 몫과 나머지 연산자 /, %
    printf("21   / 5   의 몫은 %d, 나머지는 %d 입니다\n", 21 / 5, 21 % 5);
}
