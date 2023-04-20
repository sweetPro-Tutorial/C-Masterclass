// =====================================
// '상수를 더 잘 다뤄봅시다'용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================


#include <stdio.h>
#include <math.h>


// // 심볼릭 상수(Symbolic constant):
// #define PI 3.14


// #define LIGHT_SPEED 300000000.0
#define LIGHT_SPEED 299792458.0


const double lightSpeed = 299792458.0;


int main() {
    // 상수의 3가지 종류:
    // "리터럴 상수"(literal), "변수 상수"(variable constant), "심볼릭 상수"(Symbolic constant)


    // // 리터럴(literal) 상수:
    // int yourScore = 100;  // 값을 그대로 사용했음 (100은 정수 리터럴)
    // double pi = 3.14;  // 값을 그대로 사용했음 (3.14 는 실수 리터럴)
    // char grade = 'A';  // 학점 'A' 는 문자 리터럴
    // char *name = "thankyouC";  // "thankyouC" 는 문자열 리터럴


    // // 변수 상수(variable constant):
    // const double pi = 3.14;  // const 키워드를 사용했음


    // double circleArea = PI * (r * r);
   


    // 질량을 에너지로 변환하는 프로그램
    // ------------------------------
    double mass = 0;
    double energy = 0;


    printf("[질량을 에너지로 변환하는 프로그램]\n\n");
    printf("질량을 입력하세요 (단위 kg) : ");
    scanf("%lf", &mass);
    if(mass <= 0) {
        printf(">>> 질량은 양수 값을 입력해야 합니다\n");
        return 0;
    }


    // energy = mass * (300000000.0 * 300000000.0);  // 광속도 300000000 m/s, e = m * (c * c)
    // energy = mass * (LIGHT_SPEED * LIGHT_SPEED);
    energy = mass * (lightSpeed * lightSpeed);
    printf("%.2f kg 의 질량으로 발생되는 에너지 = %.2f J(줄)\n", mass, energy);


    lightSpeed = lightSpeed + 1.0;  // compile error


}
