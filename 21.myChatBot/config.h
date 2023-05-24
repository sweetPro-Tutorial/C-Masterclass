#ifndef _CONFIG_H_
#define _CONFIG_H_


#include "common.h"

typedef struct {
    String question_json_pathname; 
    String response_json_pathname;
} Config;

// 일치하는 키의 값을 설정정보에 저장 : 성공 시 0, 실패 시 -1 반환
int keyHandler(void *config, String name, String value);

void printConfig(Config *config);


#endif