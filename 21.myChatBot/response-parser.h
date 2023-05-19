#ifndef _RESPONSE_PARSER_H_
#define _RESPONSE_PARSER_H_


#include "list.h"
#include "common.h"

#define RESPONSE_FILENAME  "response.json"

bool extractChatInfo(LinkedList *list);
void responseParse(LinkedList *list, char *data);  // 응답 메시지 파싱
bool isChatData(char *token);
bool parseChatData(StringLong *chatInfo, char *chatData);  // ChatGPT의 답변 내용만 추출


#endif