#include "decode.h"

// 외부 파일(encode.c)의 전역변수 morseTable 사용하기
extern char morseTable[TABLE_SIZE][CODE_SIZE];

void toText(char *inputFileName, char *outputFileName) {  // 모스 부호 --> 영문 텍스트로 변환
    int ascii = 0;
    char morseBuffer[CODE_SIZE] = { 0, };

    FILE *inputFile;
    FILE *outputFile;

    openFiles(&inputFile, &outputFile, inputFileName, outputFileName);

    // 사전 검사: 유효한 입력파일인지 검사
    if(!isMorseFile(inputFile)) {
        printf( "%s 는 유효한 입력파일이 아닙니다\n"
                ">>> may be english-text file.\n", inputFileName);
        closeFiles(inputFile, outputFile);
        return;
    }

    // morse code to text
    int ch;
    int i = 0;
    int state = OUT_CODE;  // 상태용 변수
    int event = NA;  // 이벤트용 변수
    // char name[6][20] = { "OUT_CODE",   "IN_CODE",    "WORD",
    //                      "WORD_FOUND", "CODE_FOUND", "NA" };
    while( (ch = fgetc(inputFile)) != EOF ) {
        ascii = 0;
        event = checkMorseChar(ch, &state);
        // printf(">>> state,event=(%s,%s)\n", name[state], name[event]);  // test

        // 단어와 단어 사이일 경우, 스페이스 문자로 변환한다;
        if(event == WORD_FOUND) {
            ascii = ' ';
        }

        // 모스 부호를 하나 발견한 경우, 문자 하나로 변환한다;
        if(ch == '.' || ch == '-') {  // 모스 부호용 문자인 . 또는 - 버퍼링
            morseBuffer[i] = ch;
            i++;
        }
        if(event == CODE_FOUND) {
            // 발견한 모스 부호와 매칭되는 영문자 검색
            for(int j = 0; j < TABLE_SIZE; j++) {  
                // if(!strncmp(morseBuffer, morseTable[j], CODE_SIZE)) {  
                if(!strncmp(morseBuffer, getMorseTable()[j], CODE_SIZE)) {  
                    ascii = j;  
                    break;
                }
            }
            // printf("morse code %s ==> '%c'\n", morseBuffer, ascii);  // test

            // 버퍼 초기화
            memset(morseBuffer, 0x00, CODE_SIZE);
            i = 0;
        }
           
        // 변환한 문자를 출력 파일에 저장한다;
        if(ascii != 0) { fputc(ascii, outputFile); }
    }
    printf(">>> 변환이 끝났습니다.\n");

    closeFiles(inputFile, outputFile);    
}


int checkMorseChar(char ch, int *statePointer) {
    switch(ch) {
    case '/' :  // 단어 식별자 발견 시
        if(*statePointer == OUT_CODE) {
            *statePointer = WORD;  
            return WORD_FOUND;  // 단어 발견 했음;
        }
        break;
    case ' ' :  // 공백문자 발견 시
        if(*statePointer == IN_CODE) {
            *statePointer = OUT_CODE;  
            return CODE_FOUND;  // 모스 부호 발견 했음;
        }
        else if(*statePointer == WORD) {
            *statePointer = OUT_CODE;  
        }
        break;
    case '.' :  // . 또는 - 문자 발견 시
    case '-' :
        if(*statePointer == OUT_CODE) {
            *statePointer = IN_CODE;
        }  
        break;
    default :
    }

    return NA;
}