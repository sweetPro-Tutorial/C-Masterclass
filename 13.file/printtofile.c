// =====================================
// fprintf로 파일을 다루는 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

int main() {
    printf("Hello world!\n");
    fprintf(stdout, "Hello world!\n");

    // 파일 열기
    FILE *stream;  // 파일 포인터용 변수 선언
    char filename[100] = "myfirstfile.txt";
    stream = fopen(filename, "w");
    // 예외 처리 로직
    if(stream == NULL) {
        printf("파일 %s 을 여는데 실패했습니다\n", filename);
        return 0;
    }

    // 파일에 출력
    fprintf(stream, "Hello world!\n");

    // 파일 닫기
    fclose(stream);

    return 0;
}
