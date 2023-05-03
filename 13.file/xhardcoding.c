// =====================================
// 피해야할 습관, 하드코딩 설명용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char **argv) {
    // 공통 코드: 파일 열기
    FILE *fp;
    char filename[100] = { 0, };

    if(argc < 2) {  // 입력한 문자열의 개수 확인
        printf(">>> 옵션을 입력하세요\n");
        return 0;
    }
    strcpy(filename, argv[1]);
   
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("파일 %s 을 여는데 실패했습니다\n", filename);
        return 0;
    }

    // fgets 사용 예:
    char line[BUFFER_SIZE] = { 0, };  // 버퍼용
    while( fgets(line, BUFFER_SIZE, fp) != NULL ) {
        printf("%s", line);  
        memset(line, 0x00, BUFFER_SIZE);
    }

    // 공통 코드: 파일 닫기
    fclose(fp);    
 
    return 0;
}
