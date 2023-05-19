#include "response-parser.h"

bool extractChatInfo(LinkedList *list) {
    char *data = loadFile(openFile(RESPONSE_FILENAME, "rb"));  // 응답 메시지 파일 로딩
    if(data == NULL) { return false; }
    // printf("response message=[%s]\n", data);  // test log
    responseParse(list, data);  // 파싱

    free(data);
    if(isEmpty(list)) { return false; }
    return true;    
}

void responseParse(LinkedList *list, char *data) {
    // 검색할 키 목록을 준비;  --> 총 1개: "content"
    // 응답 메시지를 한 객체씩 순회하면서
    // printWithTime(" >>> 응답 메시지 파싱");

    char *delimiter = "{}[]\n\t";
    char *token;
    char *savePointer;
    token = strtok_r(data, delimiter, &savePointer);
    while(token != NULL) {
        // printf(">>> token : %s\n", token);  // test log
        if(isChatData(token)) {   // 유효한 객체인지 확인
            StringLong answer;
            parseChatData(answer, token);  // 정보 추출
            pushFront(list, answer);  // 추출한 정보로 리스트 작성
            return;
        }

        token = strtok_r(NULL, delimiter, &savePointer);
    }
    eraseAllList(list);
}

bool isChatData(char *token) {
    if(match_n(token, "\"role\"", 4)) { return true; }
    return false;
}

bool parseChatData(StringLong *chatInfo, char *chatData) {
    // 문자열에서 "content": 아래의 내용을 끊어 내기
    //   SAMPLE: "role":"assistant","content":"Hello! How may I assist you?"
    String parseKey = "\"content\":";
    char *startPosition = strstr(chatData, parseKey) + strlen(parseKey);
    // 앞뒤의 큰따옴표 제거
    startPosition++;
    startPosition[strlen(startPosition) - 1] = '\0';

    strncpy(chatInfo, startPosition, sizeof(StringLong) - 1);
    return true;
}
