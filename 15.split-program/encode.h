#ifndef _ENCODE_H_
#define _ENCODE_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "anomaly.h"

#define CODE_SIZE  10
#define TABLE_SIZE 128

// toMorse:
// space symbols for toMorse
#define SPACE_BETWEEN_TWO_LETTERS  " "
#define SPACE_BETWEEN_TWO_WORDS    "/"
// state of 영문 텍스트 단어 식별용
#define OUTSIDE 0  // 상태 : 단어 밖 (현재 읽은 문자는 단어 밖에 있음)
#define INSIDE  1  // 상태 : 단어 안 (현재 읽은 문자는 단어 안에 있음)

#define TEXT_BUFFER_SIZE 1024

void toMorse(char *inputFileName, char *outputFileName);  // 영문 텍스트 --> 모스 부호로 변환

void openFiles(FILE **input, FILE **output,
    char *inputFileName, char *outputFileName);
void closeFiles(FILE *inputFile, FILE *outputFile);

// 단어 식별
bool checkWord(int *statePointer, char ch);
// 모스 파일 식별
bool isMorseFile(FILE *fp);

// 모스 부호 테이블 반환
char (*getMorseTable())[CODE_SIZE];

#endif