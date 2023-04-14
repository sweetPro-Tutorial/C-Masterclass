#include <stdio.h>

int main() {
    char *myName = "thankyouC";
    myName = "YoungHee";
    int thisYear = 2022;
    thisYear = 2023;  // 상수는 값을 덮어쓸 수 없음

    printf("Hello %s %d\n", myName, thisYear);
}
