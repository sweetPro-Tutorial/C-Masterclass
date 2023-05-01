// =====================================
// 텍스트 파일을 더 잘 다뤄 봅시다-수정-용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>


int main() {
    // 파일 열기
    FILE *fp;
    char filename[100] = "textfile.txt";
   
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("파일 %s 을 여는데 실패했습니다\n", filename);
        return 0;
    }


    // 파일의 현재 위치 이동하는 fseek
    fseek(fp, 3L, SEEK_SET);  // 파일 맨 처음에서부터 이동
    fseek(fp, 3L, SEEK_CUR);  // 파일 현재 위치에서 이동
    fseek(fp, -3L, SEEK_END); // 파일 끝에서 이동


    // error: 파일의 범위를 넘는 이동
    int result = fseek(fp, -3L, SEEK_SET);
    printf("fseek(fp, -3L, SEEK_SET) : %d\n", result);


    // 파일의 현재 위치를 알려주는 ftell
    printf("파일의 현재 위치 = %ld\n", ftell(fp));


    // 파일 닫기;
    fclose(fp);    
 
    return 0;
}
