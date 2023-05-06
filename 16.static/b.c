#include <stdio.h>

extern char *globalVariable;  // 외부 변수 사용하기

void test() {
    globalVariable = "string from test function";  // 전역변수 값 변경
}
