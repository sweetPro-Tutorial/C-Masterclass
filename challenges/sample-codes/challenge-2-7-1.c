// =====================================
// 도전과제 2.7.1의 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

int main() {
    double fahrenheit = 400.0;
    double celsius = 0.0;

    // 계산식: fahrenheit --> celsius
    celsius = (fahrenheit - 32.0) * (5.0 / 9.0);
    printf("Fahrenheit %6.1f --> Celsius %6.1f\n", fahrenheit, celsius);

    return 0;
}
