// =====================================
// if 와 논리 표현용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>

int main() {
    // "아침에 일찍 일어나기" 수행 절차:
    // ------------------------------
    // if(자명종이 울리면) then
    // begin
    //     if(컨디션이 좋으면) then
    //     begin
    //         일어난다.
    //     end
    //     else
    //     begin
    //         자명종을 끈다.
    //         30분 더 잔다.
    //     end
    // end


    // 기본정보
    const char GOOD = 'y';  // 'n' = not good, 'y' = good
    char condition = 'n';
    char alarm = 'n';


    // 알람 정보 입력받기
    printf("자명종이 울리고 있습니까? (yes 또는 no 입력) : ");
    scanf(" %c", &alarm);      // 입력한 문자열에서 한 문자만 읽어옴
    while(getchar() != '\n');  // 다음 입력을 받기 위해 키보드 버퍼를 깨끗이 비움


    // 컨디션 정보 입력받기
    printf("당신의 컨디션은 좋습니까? (yes 또는 no 입력) : ");
    scanf(" %c", &condition);  // 입력한 문자열에서 한 글자를 읽어옴


    // 알람이 울리고 && 컨디션도 좋으면 --> "일어난다"
    bool isAlarmRinging = (alarm == 'y' || alarm == 'Y');
    bool isConditionGood = (condition == GOOD || condition == 'Y');


    if ( isAlarmRinging && isConditionGood ) {
        printf(">>> 일어난다.\n");
    }
    // 알람이 울리고 && 컨디션이 좋지 않으면 --> "알람을 끄고 30분 더 잔다"
    if ( isAlarmRinging && !isConditionGood ) {
        printf(">>> 자명종을 끈다\n");
        printf(">>> 30분 더 잔다\n");
    }




    // if (alarm == 'y') {
    //     if (condition == GOOD) {
    //         printf(">>> 일어난다.\n");
    //     } else {
    //         printf(">>> 자명종을 끈다\n");
    //         printf(">>> 30분 더 잔다\n");
    //     }
    // }


   






   


    // if(조건식이 참이면)
    // {
    //     실행할 명령문;
    // }


    // 일상에서 사용하는 비교문의 형태:
    // -----------------------------
    (10 > 3); // 10 > 3  -->  10은 3보다 큰가?          답은 참.
    (10 < 3); // 10 < 3  -->  10은 3보다 작나?          답은 거짓.


    (10 == 3); // 10 = 3  -->  10과 3은 같은가?          답은 거짓.
    (10 != 3); // 10 ≠ 3  -->  10과 3은 다른가?          답은 참.
   
    (10 >= 3); // 10 ≥ 3  -->  10은 3보다 크거나 같은가?  답은 참.
    (10 <= 3); // 10 ≤ 3  -->  10은 3보다 작거나 같은가?  답은 거짓.


    int x = 10;
    if (x == 3) {  // (x = 3) 는 오류
        printf("x의 값은 3 입니다.\n");
    } else {
        printf("x의 값은 3 이 아닙니다.\n");
    }
}
