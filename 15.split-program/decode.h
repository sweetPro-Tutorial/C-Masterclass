#ifndef _DECODE_H_
#define _DECODE_H_

#include "encode.h"
#include "anomaly.h"

// toText: 상태, 이벤트
#define OUT_CODE   0  // 상태 : 모스 코드 밖 (현재 읽은 문자는 코드 밖에 있음)
#define IN_CODE    1  // 상태 : 모스 코드 안 (현재 읽은 문자는 코드 안에 있음)
#define WORD       2  // 상태 : 모스 단어
#define WORD_FOUND 3  // 이벤트 : 단어 발견
#define CODE_FOUND 4  // 이벤트 : 모스 부호 발견
#define NA         5  // 이벤트 : 해당 사항 없음(Not Applicable)

void toText(char *inputFileName, char *outputFileName);  // 모스 부호 --> 영문 텍스트로 변환

int checkMorseChar(char ch, int *statePointer);

#endif