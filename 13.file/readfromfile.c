// =====================================
// fscanf 로 파일을 다루는 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

int main() {
    int salary = 0;  // 달러 $
    double bonus = 0.0;
    char name[100] = { 0, };
    double total = 0.0;

    // 파일 열기
    FILE *fp;
    char filename[100] = "data.txt";
   
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("파일 %s 을 여는데 실패했습니다\n", filename);
        return 0;
    }

    // printf("월급 보너스 이름을 입력하세요 (예: 10000  0.2  Eliza) : ");
    // scanf("%d %lf %s", &salary, &bonus, name);
    // fscanf(stdin, "%d %lf %s", &salary, &bonus, name);
    // fscanf(fp, "%d %lf %s", &salary, &bonus, name);
    while( fscanf(fp, "%d %lf %s", &salary, &bonus, name) > 0 ) {
        total = salary + (salary * bonus);  // 월급 + 보너스금액
        printf("%10s 의 총 수입 : $ %10.2lf\n", name, total);
    }

    // 파일 닫기;
    fclose(fp);    

    return 0;
}

