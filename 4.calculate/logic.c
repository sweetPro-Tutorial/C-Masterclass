// =====================================
// 비교연산, 논리연산용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>

int main( ) {
    // C 컴파일러에게 거짓은 0, 참은 0 이외의 정수값 이므로,
    // 아래 if 문의 블록은 항상 실행됨.
    if ( 10 / 3 ) {
        printf("( 10 / 3 ) = true\n");
    }


    // 조건식의 결과값은 참일 경우 1, 거짓일 경우 0
    int myAge = 10;
    int yourAge = 20;

    printf("나의 나이 : %d 세\n", myAge);
    printf("너의 나이 : %d 세\n", yourAge);
    printf("(%d == %d) 는 거짓 : 결과값은 %d\n",
        myAge, yourAge, (myAge == yourAge) );
    printf("(%d < %d)  는 참   : 결과값은 %d\n",
        myAge, yourAge, (myAge < yourAge) );


    true;  // stdbool.h 에 1 로 정의되어 있음. 1 byes 크기임.
    false; //              0 으로 정의되 있음. 1 byes 크기임.


    // "조건식이 참이면" 의 여러가지 표현:
    // -------------------------------
    //     (조건식)
    // 또는
    //     ( (조건식) == 1 )
    // 또는
    //     ( (조건식) == true  )
    //
    int guess = 99;
    int number = 60;
   
    if(guess > number) {   // <<< 간명한 표현을 사용 추천함.
        printf("UP\n");
    }

    if( (guess > number) == 1 ) {
        printf("UP\n");
    }

    if( (guess > number) == true ) {
        printf("UP\n");
    }

    // De Morgan’s Laws:
    // ----------------
    // case1:
    //   !(a && b && c) 와 (!a || !b || !c) 는 결과값이 같음
    //
    // case2:
    //   !(a || b || c) 와 (!a && !b && !c) 는 결과값이 같음

   
    // if 문을 단순하게 만들기 1:
    //   가독성을 해치지 않는다면, 쉽게 단순화 할 수 있는 것은 단순화하는 것이 좋습니다.
    // -----------------------
    int a = 1;

    if(a != 0) {  // 원래의 조건문
    }
    if(a) {  // 단순화된 조건문
    }

    if(a == 0) {  // 원래의 조건문
    }
    if(!a) {  // 단순화된 조건문
    }

    // if 문을 단순하게 만들기 2:
    //   조건식을 Divide and Conquer 하였습니다.
    //   Divide and Conquer 는 가독성이 좋아질 때까지 하면 됩니다.
    // -----------------------
    int age = 7;
    bool with_parent = true;
    // // 원래 소스
    // if ( (age > 7) || ( (age == 7)  && (with_parent) ) ) {
    //     if(age == 7) {
    //         printf("discount_age();\n");
    //     }
    //     printf("process_entrance();\n");
 
    //     return  1;
    // }
    // else {
    //     return  0;
    // }

    // 수정된 소스
    if (age < 7) { return  0; }
 
    if (age == 7) {
        if(with_parent) {
            printf("discount_age();\n");
        }
        else {
            return  0;
        }
    }
 
    printf("process_entrance();\n");
    return  1;
}


// if 문의 조건식에 (isPhoneInfoExist == 1) 대신 isPhoneInfoExist 를 사용했음:
//
// void processCCCloseMessage(CCClose_t *message, char *XML, int threadIndex) {
//     ...
//     bool isPhoneInfoExist;
//     isPhoneInfoExist = getPhoneInfo(&(call.phone), call.CaseID);   // 해당 콜의 폰 정보
//     ...
//     if( isPhoneInfoExist && (phone.RecordStartOnCCOpen_flag == 'Y') ) {
//         kind = 6;  // user종류: CCOpen 시 녹취시작 대상자용
//     }
//     ...
// }


// 드 모르간의 법칙(De Morgan’s Laws) 을 사용해서 부정 논리를 긍정 논리로 변환했음:
//
// static int check_permitted_alphabet_11(const void *sptr) {
//     /* The underlying type is VisibleString */
//     ...
//     for(; ch < end; ch++) {
//         unsigned char cv = *ch;
//         // 출력가능한 문자가 아니면 -1 반환: 아래의 두 줄은 같은 동작을 함.
//         // 부정 논리보다는
//         if( !( (cv >= 32) && (cv <= 126) ) ) { return -1; }  
//         // 긍정의 논리가 더 읽기 좋음
//         if( cv < 32 || cv > 126 ) { return -1; }  
//     }
//     return 0;
// }

