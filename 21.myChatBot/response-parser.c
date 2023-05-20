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
        // fflush(stdout);
        if(isChatData(token)) {   // 답변 메시지인지 확인
            StringLong answer;
            parseChatData(answer, token);  // 정보 추출
            pushFront(list, answer);  // 추출한 정보로 리스트 작성
            return;
        }
        if(isErrorData(token)) {   // 에러 메시지인지 확인
            token = strtok_r(NULL, delimiter, &savePointer);  // 다음 토큰에 에러 내용 있음

            StringLong gptError;
            parseErrorData(gptError, token);  // 정보 추출
            pushFront(list, gptError);  // 추출한 정보로 리스트 작성
            return;
        }

        token = strtok_r(NULL, delimiter, &savePointer);
    }
    eraseAllList(list);
}

bool isChatData(char *token) {
    char *startPosition = strstr(token, "\"role\"");
    if(startPosition == NULL) { return false; }
    if(match_n(startPosition, "\"role\":", 7)) { return true; }
    return false;
}
bool isErrorData(char *token) {
    char *startPosition = strstr(token, "\"error\"");
    if(startPosition == NULL) { return false; }
    if(match_n(startPosition, "\"error\":", 8)) { return true; }
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
bool parseErrorData(StringLong *errorInfo, char *chatData) {
    // 문자열에서 "message": 아래의 내용을 끊어 내기
    //   SAMPLE: "error": {
    //     ==>     "message": "Rate limit reached for default-gpt-3.5-turbo...",
    String parseKey = "\"message\":";
    char *startPosition = strstr(chatData, parseKey) + strlen(parseKey);

    snprintf(errorInfo, sizeof(StringLong) - 1, "--- ERROR message: %s", startPosition);
    return true;
}
