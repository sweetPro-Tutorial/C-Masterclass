// =====================================
// 텍스트 파일을 더 잘 다뤄 봅시다-읽기-용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    // 파일 열기
    FILE *fp;
    char filename[100] = "data.txt";
   
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("파일 %s 을 여는데 실패했습니다\n", filename);
        return 0;
    }


    // // fscanf 사용 예:
    // double left  = 0.0;
    // double right = 0.0;
    // char name[100] = { 0, };
 
    // while( fscanf(fp, "%lf %lf %s", &left, &right, name) > 0 ) {
    //     printf("%10s 의 시력 = [%4.1f, %4.1f]\n", name, left, right);
    // }


    // // fgets 사용 예:
    // char line[BUFFER_SIZE] = { 0, };  // 버퍼용
    // while( fgets(line, BUFFER_SIZE, fp) != NULL ) {
    //     printf("%s", line);  
    //     memset(line, 0x00, BUFFER_SIZE);
    // }


    // fread 사용 예:
    char buffer[BUFFER_SIZE] = { 0, };  // 버퍼용
    while( fread(buffer, 1, BUFFER_SIZE - 1, fp) > 0 ) {
        printf("%s", buffer);  
        memset(buffer, 0x00, BUFFER_SIZE); // 사용 후 버퍼 청소
    }


    // 파일 닫기;
    fclose(fp);    
 
    return 0;
}
