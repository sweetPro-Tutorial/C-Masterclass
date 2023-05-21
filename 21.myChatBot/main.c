#include <locale.h>
#include "common.h"
#include "list.h"
#include "response-parser.h"

typedef struct {
    StringLong previous;
    StringLong current;
} Questions;


void programTitle();
void inputQuestion(StringLong question);  // 질문 입력
bool isValidQuestion(StringLong question);  // 입력값이 정상인지 확인

// bool chatRequest(StringLong question);  // ver.1
bool chatRequest(Questions *questions, LinkedList *list);  // ver.2
// void makeQuestionJsonFile(StringLong question);  // ver.1
void makeQuestionJsonFile(Questions *questions, LinkedList *list);  // ver.2

// util: URL encoder: 성공시 encodedText 의 주소를, 실패(오버플로)시 NULL 반환
char *urlEncode(StringLong encodedText, StringLong originalText);


int main() {
    // setlocale(LC_ALL, ".UTF8");

    programTitle();
    printTitle("Send a message.");

    Questions questions = { 0, };
    LinkedList list = { NULL, NULL, 0 };
    while(true) { 
        // 사용자로부터 질문을 입력 받는다.
        inputQuestion(questions.current);  
        // printf("%s\n", question);

        chatRequest(&questions, &list);  // 정보연계

        // 응답 메시지로부터 필요한 데이터를 추출한다.
        if(!extractChatInfo(&list) && !match_n(questions.current, "bye", 3)) {
            printf("--- 접속지연 등의 이유로 ChatGPT로부터 응답을 받지 못했습니다. 다시 질문해 주세요.\n");
            continue;
        };
        // printList(&list);  // test log

        // 사용자에게 ChatGPT의 응답을 보여준다.
        printf("%s\n", getBeginNode(&list)->data);

        // 이번 챗 내용을 기입
        strncpy(questions.previous, questions.current, sizeof(StringLong) - 1);

        // bye handling
        if(match_n(questions.current, "bye", 3)) { 
            printTitle("마이 챗봇을 종료합니다.");
            eraseAllList(&list);
            return 0;
        };
    }
}

/* 
SAMPLE REQUEST:
    curl https://api.openai.com/v1/chat/completions \
      -H "Content-Type: application/json" \
      -H "Authorization: Bearer $OPENAI_API_KEY" \
      -d '{
        "model": "gpt-3.5-turbo",
        "messages": [{"role": "user", "content": "Hello!"}]
      }'
*/
bool chatRequest(Questions *questions, LinkedList *list) {
    // 전제조건: 환경변수 등록여부 확인
    if(getenv("OPENAI_API_KEY") == NULL) {
        printf( "API인증서 정보를 찾을 수 없습니다.\n"
                "환경변수 OPENAI_API_KEY를 등록해 주세요.\n");
        return false;
    }

    StringLong requestCommand = { 0, };
    // 요청용 명령어  생성
// C11 standard style:    
    // sprintf(requestCommand, 
    //     "curl https://api.openai.com/v1/chat/completions "
    //     "-H \"Content-Type: application/json\" "
    //     "-H \"Authorization: Bearer %s\" "
    //     "-d '{ "
    //     "     \"model\": \"gpt-3.5-turbo\", "
    //     "     \"messages\": [ { \"role\": \"user\", \"content\": \"%s\" } ] "
    //     "    }'  >  response.json", 
    //     getenv("OPENAI_API_KEY"), question);
    // printf("--- requestCommand=%s\n", requestCommand);  // test log

// gcc Raw String Literals style:
    // sprintf(requestCommand, 
    //     R"(curl https://api.openai.com/v1/chat/completions )" 
    //     R"(-H "Content-Type:application/json" )"
    //     R"(-H "Authorization:Bearer %s" )"
    //     R"(-d '{ )"
    //     R"(     "model":"gpt-3.5-turbo", )"
    //     R"(     "messages": [ { "role": "user", "content": "%s" } ] )"
    //     R"(    }'  >  response.json )", 
    //     getenv("OPENAI_API_KEY"), question);
    // printf("--- requestCommand=%s\n", requestCommand);  // test log

    // 윈도우에서의 문제해결: 쉘 스크립트 파일 호출 방식
    sprintf(requestCommand, "runme.sh" );       // for windows
    // sprintf(requestCommand, "./runme.sh" );  // for linux
    // printf("--- requestCommand=%s\n", requestCommand);  // test log

    makeQuestionJsonFile(questions, list);  // make myquestion.json file

    // 요청용 명령어 실행 및 응답 메시지를 파일에 저장
    int result = system(requestCommand);
    // printf("system result=%d\n", result);
    
    return true; 
}

// 파일 예시1: 
// { "model":"gpt-3.5-turbo", "messages":[{"role": "user", "content": "Hi!"}] }
//
// 파일 예시2: 
// { "model":"gpt-3.5-turbo",   "messages": [ 
//     { "role": "system", "content": "You are a helpful assistant." },
//     { "role": "user", "content": "AI stands for Artificial Intelligence. It refers to the creation of intelligent machines that can perform tasks that typically require human intelligence, such as visual perception, speech recognition, decision-making, and language translation.\n\nAI involves the development of algorithms and computer programs that can learn and make decisions based on data input. The development of AI is based on the collection and analysis of large amounts of data to improve the accuracy and effectiveness of the algorithms used.\n\nAI has become increasingly important in modern society and is now widely used in a variety of industries, including healthcare, finance, transportation, and entertainment. Its potential applications are virtually limitless and continue to expand as technology advances." },
//     { "role": "assistant", "content": "" },
//     { "role": "user", "content": "summarize the above sentence in 30 words." }
// ] }
void makeQuestionJsonFile(Questions *questions, LinkedList *list) {
    StringLong currQuestionUrlEncoded = { 0, };
    StringLong prevQuestionUrlEncoded = { 0, };
    StringLong prevAnswerUrlEncoded = { 0, };
    
    if(urlEncode(currQuestionUrlEncoded, questions->current) == NULL) { 
        currQuestionUrlEncoded[0] = '\0';
    }

    // API 호출할 때, 직전의 대화도 반영하기 위해.
    if(urlEncode(prevQuestionUrlEncoded, questions->previous) == NULL) { 
        prevQuestionUrlEncoded[0] = '\0';
    }
    if(list->size > 0) {
        char *lastAnswer = getBeginNode(list)->data;
        if(urlEncode(prevAnswerUrlEncoded, lastAnswer) == NULL) { 
            prevAnswerUrlEncoded[0] = '\0'; 
        }
    }

    FILE *fp = fopen("myquestion.json", "wb");
    fprintf(fp, 
        "{ \"model\":\"gpt-3.5-turbo\", \"messages\": [ \n"
        "   { \"role\": \"system\",    \"content\": \"You are a helpful assistant.\" }, \n"
        "   { \"role\": \"user\",      \"content\": \"%s\" }, \n"
        "   { \"role\": \"assistant\", \"content\": \"%s\" }, \n"
        "   { \"role\": \"user\",      \"content\": \"%s\" }  \n"
        "] }",
        prevQuestionUrlEncoded, prevAnswerUrlEncoded, currQuestionUrlEncoded);
    fflush(fp);
    fclose(fp);
}

// util: URL encoder: 성공시 encodedText 의 주소를, 실패(오버플로)시 NULL 반환
char *urlEncode(StringLong encodedText, StringLong originalText) {
    const char hex[16] = "0123456789abcdef";
    int maxPos = sizeof(StringLong) - 5;  // 최악의 경우를 고려.

    memset(encodedText, 0x00, sizeof(StringLong));
    int pos = 0;
    for (int i = 0; i < strlen(originalText); i++) {
        if(pos >= maxPos) { return NULL; }  // on overflow
        char ch = originalText[i];
        switch(ch) {
        case 'a'...'z': 
        case 'A'...'Z':
        case '0'...'9':
        case '(': case ')':
        case '?': case ',': case '.': case '!':
        case '\'': case ' ':
            encodedText[pos++] = ch;
            break;
        default:
            // 기타문자와 한글은 url encoding
            encodedText[pos++] = '%';
            encodedText[pos++] = hex[0x0F & (ch >> 4)];
            encodedText[pos++] = hex[0x0F & ch];
            break;
        }
    }
    return encodedText;
}


void inputQuestion(StringLong question) {
    printf("\n>>> ");
    fflush(stdout);  // for windows
    while(fgets(question, sizeof(StringLong), stdin) != NULL) {
        if(isValidQuestion(question)) {
            return;
        }
        printf("\n>>> ");
        fflush(stdout);  // for windows
    }
}

bool isValidQuestion(StringLong question) {
    strStrip(question);
    if(match(question, "")) { return false; }
    return true;
}

void programTitle() {
    printf( "\n\n"
            "###################################################################\n"
            "#                                                                 #\n"
            "#                     m y    C h a t    B o t                     #\n"
            "#                                                                 #\n"
            "#      -----------------------------------------------------      #\n"
            "#                                                                 #\n"
            "#              (대화를 종료하려면 bye 를 입력하세요)              #\n"
            "#                                                                 #\n"                        
            "###################################################################\n\n" );
}




