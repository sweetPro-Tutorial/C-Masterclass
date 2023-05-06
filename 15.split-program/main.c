// =====================================
// morse encoder, decoder 용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include "main.h"


int main(int argc, char **argv) {
    printf("[ MORSE UTILITY ]\n");

    char operation = checkOption(argc, argv);  // 옵션 검사
    switch(operation) {
    case ENCODE: toMorse(argv[2], argv[3]); break;   // 모스 부호로 변환
    case DECODE: toText(argv[2], argv[3]);  break;   // 영문 텍스트로 변환
    default: anomalyReport(); break; // 이상 보고서: 옵션이나 입력파일의 문제 알림
    }

    return 0;
}


char checkOption(int argc, char **argv) {  // 옵션 검사
    // 옵션 공통 코드: 옵션의 개수 확인
    if(argc != 4) { return QUIT; }
    // 옵션 내용 검사
    if(strcmp(argv[1], "-e") == 0) { return ENCODE; }
    if(strcmp(argv[1], "-d") == 0) { return DECODE; }
    return QUIT;
}









bool findMorseWord(char ch, int *statePointer) {
    switch(ch) {
    case '/' :  // 단어 식별자 발견 시
        if(*statePointer == OUT_CODE) {
            *statePointer = WORD;  
            return true;// 단어 발견 했음;
        }
        break;
    case ' ' :  // 스페이스 문자 발견 시
        *statePointer = OUT_CODE;
        break;
    default :  // . 또는 - 문자 발견 시
    }

    return false;
}


bool findMorseCode(char ch, int *statePointer) {
    switch(ch) {
    case ' ' :  // 공백문자 발견 시
        if (*statePointer == IN_CODE) {
            *statePointer = OUT_CODE;
            return true;  // 모스 부호 발견 했음;
        }
        break;
    case '.' :  // . 또는 - 문자 발견 시
    case '-' :
        *statePointer = IN_CODE;  
        break;
    default :
    }

    return false;
}






