// =====================================
// 사칙연산용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
 
int main() {
    // 10.0 % 2.0;  // compile error


    double G = 6.67428e-11;  // 중력 상수 G
    double mass1 = 0;  // m1 의 질량
    double mass2 = 0;  // m2 의 질량
    double distance = 0;  // m1 과 m2 사이의 거리 r
    double force = 0;  // m1 과 m2 사이에 작용하는 인력 f
 
    printf("[만유인력 계산 프로그램]\n\n");
    // m1, m2, r 입력받기
    printf("물체1의 질량은(단위: 킬로그램) ?\n");
    scanf("%lf", &mass1);
    printf("물체2의 질량은(단위: 킬로그램) ?\n");
    scanf("%lf", &mass2);
    printf("두 물체 사이의 거리는(단위:미터) ?\n");
    scanf("%lf", &distance);
 
    // 만유인력 계산식
    // f = G * ( (m1 * m2) / (r * r) );  // better
    force = G * ( (mass1 * mass2) / (distance * distance) );
 
    // 결과 출력하기
    printf("----------------------------------------\n");
    printf("물체1의 질량 : %f kg\n", mass1);
    printf("물체2의 질량 : %f kg\n", mass2);
    printf("물체 간 거리 : %f m\n", distance);
    printf("----------------------------------------\n");
    printf("물체 간 인력 : %f N(뉴튼)\n", force);



    // 0이 너무 많으면, "과학계산용" 표기로 표현하는게 편함.
    const double h = 6.62607015e-34;  // Planck constant
    printf("h = %.45f\n", h);  // 포맷 문자 '%' 와 변환 문자 'f' 사이에
                               // 표시하고 싶은 자릿수를 지정합니다.
    printf("h = %e\n", h);     // 'e' 는 과학계산용 표기로 표시합니다.


    // 10 + 2 x 3 - 8 ÷ 4
    int result = 10 + (2 * 3) - (8 / 4);  // 계산 우선순위는 괄호로 명확화.


    int number1 = 100;
    int number2 = 100;


    // 연산자 줄여쓰기1:
    // ---------------
    // number1 = number1 + 1;  // 실행결과 변수 number1 에 101 이 저장됨
    number1++;  // 101
    ++number1;  // 102
    // number2 = number2 - 1;  // 실행결과 변수 number2 에 99  가 저장됨
    number2--;  // 99
    --number2;  // 98


    int year = 2999;
    int next_year;
    // 증감연산자 사용 시 주의:
    //   year 의 값인 2999 를 이 명령문에서 사용함.
    //   사용한 후(명령문이 끝난 후)에 year 값은 1 만큼 증가됨.
    // next_year = year++;
    //  
    // 증감연산자는 아래와 같이 권장 형태(단독 명령어)로 사용하면
    // 예측한대로 동작함:
    year++;
    next_year = year;
   
    printf("year = %d\n", year);
    printf("next_year = %d\n", next_year);




    // int a = 10;
    // int b = 2;


    // 줄여쓰기 연산자2:
    // ---------------
    // a = a + b;  // a += b;  로 줄여 쓸 수 있음
    // a = a - b;  // a -= b;  로 줄여 쓸 수 있음
    // a = a * b;  // a *= b;  로 줄여 쓸 수 있음
    // a = a / b;  // a /= b;  로 줄여 쓸 수 있음
    // a = a % b;  // a %= b;  로 줄여 쓸 수 있음


    // Code Smell : 읽기 힘든 Bad Smell 코드
    // ------------------------------------
    int a = 10;
    int b;


    // a *= 2 + 5;  // 도대체 무슨 의미인가?
    a = a * (2 + 5);
    printf("a *= 2 + 5 의 계산 결과 a 는 %d\n", a);  // 출력되는 값은 70


    // a *= b = 3;  // 도대체 무슨 의미인가?
    b = 3;
    a = a * b;
    printf("a *= b = 3 의 계산 결과 a 는 %d\n", a);  // 출력되는 값은 210
}
