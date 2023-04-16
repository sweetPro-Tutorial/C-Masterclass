// =====================================
// 도전과제 2.7.2의 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

int main() {
    double fahrenheit = 0.0;
    double celsius = 200.;

    // 계산식: celsius --> fahrenheit
    fahrenheit = ( celsius * (9.0 / 5.0) ) + 32;
    printf("Celsius %6.1f --> Fahrenheit %6.1f\n", celsius, fahrenheit);

    return 0;
}
