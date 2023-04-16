// =====================================
// 사용자와 소통하는 마법 금화 계산 프로그램
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>

int main() {
    // [기본정보]
    int dailyMade = 7;  // 금화 생성량
    int dailyUsed = 3;  // 금화 소비량
    int passedDays = 30; // 경과한 기간

    // [계산식]
    int madeGolds;      // 그 동안 생성된 금화 (ⓐ) = 7개 x 30일
    int usedGolds;      // 그 동안 써버린 금화 (ⓑ) = 3개 x 30일
    // -------------------- -------------
    int sum;            // 합계 (ⓐ - ⓑ) = 120개

    printf("[마법 금화 계산 프로그램]\n");

    printf("경과한 기간(일)을 입력하세요(예: 30) : ");
    scanf("%d", &passedDays);

    madeGolds = dailyMade * passedDays; // ⓐ
    usedGolds = dailyUsed * passedDays; // ⓑ
    sum = madeGolds - usedGolds;  // ⓐ - ⓑ

    printf("경과한 시간 : %d 일\n", passedDays);
    printf("남은 금화 개수 : %d 개\n", sum);
}