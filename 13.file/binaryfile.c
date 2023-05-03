// =====================================
// binary file용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <string.h>
 
#define BUFFER_SIZE 1024  // 1KB

// 메모리에 저장된 내용을 헥사 값으로 출력하는 함수
void hexdump(char *memory, int size);

 
int main(int argc, char **argv) {
    // 옵션 공통 코드: 옵션의 개수 확인
    if(argc < 2) {  
        printf(">>> 옵션으로 <파일이름>을 입력하세요.\n");
        return 0;
    }
 
    // 파일 공통 코드: 파일 열기
    FILE *fp;
    char *filename = argv[1];
    fp = fopen(filename, "rb");
    if(fp == NULL) {
        printf("파일 %s 을 여는데 실패했습니다\n", filename);
        return 0;
    }


    // 파일 내용 읽기:
    int size;
    char buffer[BUFFER_SIZE] = { 0, };
    while( (size = fread(buffer, 1, BUFFER_SIZE, fp)) > 0 ) {
        hexdump(buffer, size);
    }
    printf("\n");

   
    // int hex      = 0x0a;  // hexadecimal digit code
    // int decimal  = 10;    // decimal digit code
    // int octal    = 012;   // octal digit code

 
 
    // 파일 공통 코드: 파일 닫기
    fclose(fp);    
 
    return 0;
}


// 메모리에 저장된 내용을 헥사 값으로 출력하는 함수
#define HEXDUMP_COLS  16

void hexdump(char *memory, int size) {
    for(int i = 0; i < size; i++) {
        // part1: 오프셋 출력 부분
        if(i % HEXDUMP_COLS == 0) {
            printf("%07x: ", i);
        }

        // part2: 헥사 데이터 출력 부분
        unsigned char ch = memory[i];
        printf("%02X ", ch);
       
        // part3: 16 바이트 출력 후 줄 바꿈 부분
        if( (i % HEXDUMP_COLS) == (HEXDUMP_COLS - 1) ) {
            printf("\n");
        }
    }
}
