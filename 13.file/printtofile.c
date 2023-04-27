// =====================================
// fprintf로 파일을 다루는 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

int main() {
    // 파일 열기
    FILE *stream;  
    char filename[100] = "myfirstfile.txt";
    stream = fopen(filename, "w");

    // 파일에 출력
    fprintf(stream, "Hello world!\n");

    // 파일 닫기
    fclose(stream);
}