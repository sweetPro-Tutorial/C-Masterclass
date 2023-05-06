#ifndef _COMMON_H_
#define _COMMON_H_


#include <stdio.h>
#include <time.h>
#include <string.h>

#define LINE_SIZE           1024  // 긴   문자열용
#define ITEM_SIZE           100   // 짧은 문자열용

typedef char StringLong[LINE_SIZE];
typedef char String[ITEM_SIZE];
typedef enum { YYYYMMDD, YYYYMMDD_HH, YYYYMMDD_HHmmSS } DateFormat;

char *getMasterFilename(String dataTime);  // 마스터 파일 이름 반환
char *getMasterFilename_X(String dataTime);  // <-- 부적절한 해결 예
char *getMasterFilename_O(char *result, int size, String dataTime);  // <-- 적절한 해결 예
char *getTimeString(DateFormat kind);  // 포맷으로 날짜 문자열 반환
char *getTimeString_X(DateFormat kind);  // <-- 부적절한 해결 예
char *getTimeString_O(char *result, int size, DateFormat kind);  // <-- 적절한 해결 예


#endif
