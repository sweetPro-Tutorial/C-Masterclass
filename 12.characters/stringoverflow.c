// =====================================
// App1 : 문자열 넘침 방지용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <string.h>




#define MAX_NAME_LENGTH 10
#define MAX_PHONE_LENGTH 20


#define MAX_LENGTH 100
#define QUESTION  "지구는 ( ) 둘레를 돈다. 괄호 안에 들어갈 단어는 영어로 무엇인가?"  
#define ANSWER    "sun"


#define NUMBERS "0123456789"


// 사용시 주의사항2(재진입 금지) 이상현상 확인용 코드
void re_entrant_anomalyTest();
// 사용시 주의사항2(재진입 금지) 해결한 코드
void re_entrant_solved();




// strlen 함수 만들기:
// ==================
int myStrlen(char *str);




int main() {
char *ptr = NULL;
// printf(">>> %c\n", *ptr);


    char name[MAX_NAME_LENGTH + 1] = { 0, }; // 선언과 동시에 구성요소를 0 으로 초기화 했음


    printf("memory size of name = %d bytes\n", sizeof(name));
    printf(">>> string length   = %d\n", strlen(name));


    strcpy(name, "Eliza");
    strcpy(name, "Eve");
    printf("name is %s\n", name);


    // strcpy 사용 예시:
    // ===============
    char source[MAX_PHONE_LENGTH + 1] = { 0, };
    char dest[MAX_PHONE_LENGTH + 1] = { 0, };
    char *pointer;


    strcpy(source, "010-1234-1004"); // 초기값 주기
    pointer = strcpy(dest, source);  // 값 복사하기


    printf("source  = [%s]\n", source);
    printf("dest    = [%s]\n", dest);
    printf("pointer = [%s]\n", pointer);


    // strncpy 사용 예시:
    // =========================
    char fullName[MAX_NAME_LENGTH + 1] = { 0, };
    char nickName[MAX_NAME_LENGTH + 1] = { 0, };
    strcpy(fullName, "Elizabeth");
    strncpy(nickName, fullName, 5);
 
    printf("fullName = [%s]\n", fullName);
    printf("nickName = [%s]\n", nickName);


    // strncat 사용 예시:
    // ================
    char song[40] = "We Are The Champions";
    char artist[40] = "Queen";
    char extension[10] = "mp3";
    char filename[100] = { 0, };


    // 노래 이름 뒤에 확장자를 연결해서 음악 파일명을 생성
    //   filename = song + "." + extension
    //            = "We Are The Champions.mp3"
    strncpy(filename, song, strlen(song));  // step1


    strcat(filename, ".");  // step2


    strncat(filename, extension, strlen(extension));  // step3
    printf("filename = [%s]\n", filename);


    // sprintf 사용 예시:
    // ================
    // 위 step1부터 3까지 3 라인을 보다 간편하게 고쳐 쓸 수 있습니다.
    sprintf(filename, "%s.%s", song, extension);
    printf("filename = [%s]\n", filename);




    // // strcmp 사용 예시:
    // // ================
    // char reply[MAX_LENGTH + 1] = { 0, };  // 최대 100 자 저장 가능


    // printf("[문제 풀이 프로그램]\n");
    // printf("문제 : %s\n", QUESTION);
    // scanf("%s", reply);


    // if(!strcmp(reply, ANSWER)) {
    //     printf(">>> 결과 : O.K\n");
    // }
    // else {
    //     printf(">>> 결과 : X\n");
    // }


    // strncmp 사용 예시:
    // =================
    char myBirthday[10] = "20051225";
    char birthday1[10]  = "20060707";
    int result = strncmp(myBirthday, birthday1, 4);
    printf("myBirthday(%s) vs birthday1(%s)\n", myBirthday, birthday1);
    if(result == 0) {
        printf(">>> 나이가 같음\n");
    }
    else if (result < 0) {
        printf(">>> 내가 더 어림\n");
    } else {
        printf(">>> 내 나이가 더 많음\n");
    }






    // strstr 사용 예시:
    // =================
    char *startAddress = strstr("ZDATA", "DATA");
    printf("%s\n", startAddress);


    // NULL 은 symbolic void pointer constant 입니다.
    printf("NULL is %d\n", NULL);


    // 사용전 NULL 확인으로,
    // 문자열 처리 프로그램을 튼튼하게 만들기
    char copyTest[10] = { 0, };
    startAddress = strstr("ZDATA", "test");
    if(startAddress == NULL) {
        printf(">>> 원하는 문자열 미발견\n");  // <<< 여기에 예외처리 로직 추가
    } else {
        strcpy(copyTest, startAddress);
    }
   


    // strchr 사용 예시:
    // =================        
    startAddress = strchr(filename, 'X');
    printf("[%s] 에 '%c' 가 %s\n",
        filename, 'X', (startAddress == NULL ? "없습니다" : "있습니다") );


    startAddress = strchr(filename, 'e');
    printf("[%s] 에 '%c' 가 %s\n", filename,
        'e', (startAddress == NULL ? "없습니다" : "있습니다") );


    if(startAddress) {
        // 문자열에 들어 있는 'e' 의 위치를 전부 찾아보자
        while(startAddress != NULL) {
            printf(">>> 찾은 위치의 인덱스 = [%ld], 이하 문자열 = [%s]\n",
                startAddress - filename, startAddress);
            startAddress = strchr(startAddress + 1, 'e');
        }


        printf("[참고]\n");
        printf("인덱스 : 012345678901234567890123\n");
        printf("문자열 : %s\n", filename);
    }




    //
    // 문자 집합을 사용하는 문자열 처리 함수들
    // ====================================
    // strspn 사용 예시:
    char id[15] = "011223-3456789";  // 주민등록번호
    int length = strspn(id, NUMBERS);
    printf("주민번호 = %s\n", id);
    printf(">>> 찾아낸 숫자 문자열의 길이 = %d\n", length);


    memset(birthday1, 0x00, sizeof(birthday1));  // 중요: 사용하기 전에 메모리 초기화
    strncpy(birthday1, id, length);
    printf(">>> 생일 = %s\n", birthday1);




    // strcspn 사용 예시:
    // 패스포트 번호에서 숫자가 아닌 문자열 길이를 찾아내는 코드
    char passportNo[10] = "M70123456";
    char buffer[10] = { 0, };


    length = strcspn(passportNo, NUMBERS);
    printf("passport_no = [%s]\n", passportNo);
    printf("패스포트 번호에서 숫자가 아닌 문자열 길이 = [%d]\n", length);
    printf("     --> \"%.*s\"\n", length, passportNo);




    // strtok 사용 예시:
    //   문자열을 공백문자 ' ' 및 느낌표 '!' 를 칼로 사용해서
    //   토큰으로 잘라내는 코드
    char originalString[MAX_LENGTH + 1] = "I like programming!";
    char backupString[MAX_LENGTH + 1] = { 0, };  // 초기화
    char delimiter[3] = " !";   // 구분자는 공백문자 ' ' 와 느낌표 '!'
    char *token;


    // step1: 원본 문자열의 복사본을 만듭니다.
    strcpy(backupString, originalString);  
    printf("구분자 = [%s]\n", delimiter);
    printf("절단 전 : 원본 문자열(originalString) = [%s]\n", originalString);
    printf("절단 전 : 복사본 문자열(backupString) = [%s]\n", backupString);


    // step2: 첫 토큰을 얻습니다.
    //   중요: 첫 토큰을 얻을 때는 입력값으로 문자열(복사본)을 사용.
    //   만약, 토큰이 존재하지 않으면 NULL 을 반환.
    token = strtok(backupString, delimiter);


    // 토큰이 존재하는지 확인합니다.(반복)
    while(token != NULL) {
        printf(">>> token : %s\n", token);


        // step3: 다음 토큰을 얻습니다.
        //   중요: 두번째 부터는 토큰을 얻을 때는 입력값으로 NULL 을 사용.
        token = strtok(NULL, delimiter);
    }
    printf("절단 후 : 원본 문자열(originalString) = [%s]\n", originalString);
    printf("절단 후 : 복사본 문자열(backupString) = [%s]\n", backupString);


    // 사용시 주의사항2(재진입 금지) 이상현상 확인용 코드
    re_entrant_anomalyTest();


    printf("\n");
    // 사용시 주의사항2(재진입 금지) 해결한 코드
    re_entrant_solved();




    printf("strlen  : %d\n", strlen(originalString));
    printf("myStrlen: %d\n", myStrlen(originalString));




}


void re_entrant_anomalyTest() {
    char string[20] = "a/bb///ccc:xxx:yyy";
    char string2[20] = { 0, };
    char *delimiter = ":";
    char *subdelimiter = "/";
    char *token;
    char *subtoken;
    int i = 1;


    printf("used string  : %s\n", string);
    printf("delimiter    : \"%s\"\n", delimiter);
    printf("sub-delimiter: \"%s\"\n", subdelimiter);
    printf("----------------------\n");


    token = strtok(string, delimiter);
    while(token != NULL) {
        printf("token %d: %s\n", i, token);
        i++;
   
        // re-entrant
        strcpy(string2, token);
        subtoken = strtok(string2, subdelimiter);
        while(subtoken != NULL) {
            printf("     --> %s\n", subtoken);
            subtoken = strtok(NULL, subdelimiter);
        }


        token = strtok(NULL, delimiter);
    }
}


void re_entrant_solved() {
    char string[20] = "a/bb///ccc:xxx:yyy";
    char string2[20] = { 0, };
    char *delimiter = ":";
    char *subdelimiter = "/";
    char *token;
    char *subtoken;
    int i = 1;


    printf("used string  : %s\n", string);
    printf("delimiter    : \"%s\"\n", delimiter);
    printf("sub-delimiter: \"%s\"\n", subdelimiter);
    printf("----------------------\n");


    char *savePointer1;
    char *savePointer2;
   
    token = strtok_r(string, delimiter, &savePointer1);
    while(token != NULL) {
        printf("token %d: %s\n", i, token);
        i++;
   
        // re-entrant
        strcpy(string2, token);
        subtoken = strtok_r(string2, subdelimiter, &savePointer2);
        while(subtoken != NULL) {
            printf("     --> %s\n", subtoken);
            subtoken = strtok_r(NULL, subdelimiter, &savePointer2);
        }


        token = strtok_r(NULL, delimiter, &savePointer1);
    }
}


// strlen 함수 만들기:
// ==================
int myStrlen(char *str) {
    int counter = 0;
    int i;  // index
   
    i = 0;  // 문자열의 처음을 가리킨다;
    while(str[i] != '\0') {  // 한 문자를 읽는다. 문자열 끝이 아니면
        counter++;  // counter 를 증가한다;
        i++;  // 다음 문자로 이동한다;
    }


    return counter;
}

