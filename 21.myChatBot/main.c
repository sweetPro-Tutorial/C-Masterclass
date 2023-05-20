#include <locale.h>
#include "common.h"
#include "list.h"
#include "response-parser.h"


void programTitle();
void inputQuestion(StringLong question);  // 질문 입력
bool isValidQuestion(StringLong question);  // 입력값이 정상인지 확인

bool chatRequest(StringLong question);
void makeQuestionJsonFile(StringLong question);
// util: URL encoder: 성공시 encodedText 의 주소를, 실패(오버플로)시 NULL 반환
char *urlEncode(StringLong encodedText, StringLong originalText);


int main() {
    setlocale(LC_ALL, ".UTF8");

    programTitle();
    printTitle("Send a message.");

    StringLong question;
    while(true) { 
        // 사용자로부터 질문을 입력 받는다.
        inputQuestion(question);  
        // printf("%s\n", question);

        chatRequest(question);  // 정보연계

        // 응답 메시지로부터 필요한 데이터를 추출한다.
        LinkedList list = { NULL, NULL, 0 };
        if(!extractChatInfo(&list)) { 
            printf("--- 접속지연 등의 이유로 ChatGPT로부터 응답을 받지 못했습니다. 다시 질문해 주세요.\n");
        };
        // printList(&list);  // test log

        // 사용자에게 ChatGPT의 응답을 보여준다.
        printf("%s\n", getBeginNode(&list)->data);
        eraseAllList(&list);

        // bye handling
        StringLong striped; 
        strncpy(striped, strStrip(question), sizeof(StringLong));
        if(match(question, "bye")) { 
            printTitle("마이 챗봇을 종료합니다.");
            exit(0); 
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
bool chatRequest(StringLong question) {
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

    makeQuestionJsonFile(question);  // make myquestion.json file

    // 요청용 명령어 실행 및 응답 메시지를 파일에 저장
    int result = system(requestCommand);
    // printf("system result=%d\n", result);
    
    return true;
}

// 파일 예시: 
// { "model":"gpt-3.5-turbo", "messages":[{"role": "user", "content": "Hi!"}] }
void makeQuestionJsonFile(StringLong question) {
    StringLong questionUrlEncoded = { 0, };

    if(urlEncode(questionUrlEncoded, question) == NULL) { return; }

    FILE *fp = fopen("myquestion.json", "wb");
    fprintf(fp, 
        "{ \"model\":\"gpt-3.5-turbo\", "
        "  \"messages\": [ { \"role\": \"user\", \"content\": \"%s\" } ] }",
        questionUrlEncoded);
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




