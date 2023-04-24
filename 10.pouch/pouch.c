// =====================================
// '관련된 데이터끼리 묶어서 사용합시다'용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>
 
#define LAMPS_SIZE 13


// 속성1) 가로등 상태 : 켜짐, 꺼짐, 깜박임
// #define OFF   0
// #define ON    1
// #define BLINK 2
enum stateType { OFF, ON, BLINK };
typedef enum stateType State;  // 별명
 
// 속성2) 광원의 종류 : 보통 전구, 수은등, 형광등, 나트륨등, LED 전구
// #define ORDINARY_LAMP     0
// #define MERCURY_LAMP      1
// #define FLUORESCENT_LAMP  2
// #define SODIUM_LAMP       3
// #define LED               4
enum kindType { ORDINARY_LAMP, MERCURY_LAMP, FLUORESCENT_LAMP, SODIUM_LAMP, LED };




// 무명 열거 타입: 화이트 스페이스 문자용
enum { SPACE = ' ', TAB = '\t', NEW_LINE = '\n' };


#define END_MARK '#'
 
void countCharacters(void) {
    int character;
    int noWhiteSpace = 0;
    int noNumber = 0;
    int noAlphabet = 0;
    int noOther = 0;
 
    while( (character = getchar()) != END_MARK) {
        switch (character) {
        case SPACE :
        case TAB :
        case NEW_LINE :
            noWhiteSpace++;
            break;
        case '0' ... '9':
            noNumber++;
            break;
        case 'A' ... 'Z':
        case 'a' ... 'z':
            noAlphabet++;
            break;
        default:
            noOther++;
            break;
        }
    }
    // 결과 출력 부분
    printf("[Count Characters]\n");
    printf("number of WhiteSpace: %d\n", noWhiteSpace);
    printf("number of Number    : %d\n", noNumber);
    printf("number of Alphabet  : %d\n", noAlphabet);
    printf("number of all Others: %d\n", noOther);
}








/*
    구조체 사용법:
    ============
    struct  구조체이름  {
        타입1  항목1;
        ...
        타입n  항목n;
    };
*/
// 가로등 정보를 하나로 묶을 수 있는 구조체 타입:
struct lampInfoType {
//    int state;
    State state;
    int kind;
    double batteryLevel;
    bool warning;
};
// 타입에 별명 붙이기:
typedef  struct lampInfoType  LampInfo;




// 타이틀과 함께 가로등 정보 출력
void printLampInfo(struct lampInfoType lampInfo, char *label);


// 구조체용 set 함수의 입력값은 구조체 변수의 주소와 저장할 값들로 구성됨
// void setLampInfo(struct lampInfoType *lampInfo,
//     int state, int kind, double batteryLevel, bool warning);
void setLampInfo(LampInfo *lampInfo,
    int state, int kind, double batteryLevel, bool warning);


 
int main() {
    // 도로가의 가로등을 속성별로 1차원 배열로 코딩하면:
    int lampsState[LAMPS_SIZE] = { OFF, };  // for 속성1) 가로등 상태
    int lampsKind[LAMPS_SIZE] = { ORDINARY_LAMP, };  // for 속성2) 광원의 종류
    double lampsBatteryLevel[LAMPS_SIZE] = {  // for 속성3) 배터리 잔량
        100.0, 100.0, 100.0, 100.0, 100.0,  
        100.0, 100.0, 100.0, 100.0, 100.0,
        100.0, 100.0, 100.0
     };
    bool lampsWarning[LAMPS_SIZE] = { false, };  // for 속성4) 누전 경고


    // 9번 가로등의 정보
    lampsState[9] = ON;   // 9번 가로등에 불이 들어왔음
    lampsKind[9] = LED;  // 9번 가로등 광원은 LED
    lampsBatteryLevel[9] = 96.2;  // 9번 가로등 배터리 잔량
    lampsWarning[9] = true;  // 9번 가로등 누전 발생








    // 구조체 변수 선언:
    struct lampInfoType lampInfo;


    lampInfo.state = ON;
    lampInfo.kind = LED;
    lampInfo.batteryLevel = 77.7;
    lampInfo.warning = true;








    // 선언과 동시에 초기값 주기:
    struct lampInfoType lampInfo1 = { BLINK, LED, 77.7, true };
    struct lampInfoType lampInfo2 = { ON, };


    printLampInfo(lampInfo, "lampInfo");
    printLampInfo(lampInfo1, "lampInfo1");
    printLampInfo(lampInfo2, "lampInfo2");


    // 구조체 변수끼리 값 할당
    lampInfo1 = lampInfo2;
    printLampInfo(lampInfo1, "lampInfo1");
    printLampInfo(lampInfo2, "lampInfo2");


    // 구조체 변수의 크기:
    printf(">>> sizeof bool=%d bytes\n", sizeof(bool));
    printf(">>> sizeof lampInfo1=%d bytes\n", sizeof(lampInfo1));
    printf(">>> lampInfo1 addr              =0x%p\n", &lampInfo1);
    printf(">>> lampInfo1.state addr        =0x%p\n", &lampInfo1.state);
    printf(">>> lampInfo1.kind addr         =0x%p\n", &lampInfo1.kind);
    printf(">>> lampInfo1.batteryLevel addr =0x%p\n", &lampInfo1.batteryLevel);
    printf(">>> lampInfo1.warning addr      =0x%p\n", &lampInfo1.warning);












    // 사이즈가 13인 구조체 타입의 배열 lamps
    struct lampInfoType lamps[LAMPS_SIZE] = { 0, };


    // 첫 번째 가로등 정보 :
    //   상태는 ON, 램프 종류는 LED, 배터리는 95 %, 경고여부는 OK.
    // 두 번째 가로등 정보 :
    //   상태는 BLINK, 램프 종류는 LED, 배터리는 30 %, 경고여부는 WARNING.


    // set 함수를 사용하지 않았을 때의 코드:
    lamps[0].state = ON;
    lamps[0].kind = LED;
    lamps[0].batteryLevel = 95.0;
    lamps[0].warning = false;


    lamps[1].state = BLINK;
    lamps[1].kind = LED;
    lamps[1].batteryLevel = 30.0;
    lamps[1].warning = true;


    // set 함수를 사용한 코드:
    setLampInfo(&lamps[0], ON, LED, 95.0, false);
    setLampInfo(&lamps[1], BLINK, LED, 30.0, true);
    printLampInfo(lamps[0], "lamps[0]");
    printLampInfo(lamps[1], "lamps[1]");
    printLampInfo(lamps[2], "lamps[2]");


    // 구조체 타입과 일반 타입으로 변수를 선언하는 경우를 비교:
    // struct lampInfoType lampInfo3;
    LampInfo lampInfo3;
    int      age;


   




    // 열거 타입:
    printf(">>> OFF=%d, ON=%d, BLINK=%d\n", OFF, ON, BLINK);


    State stateVariable = OFF;
    stateVariable = 10;  // 열거 타입 변수에 리터럴 상수 할당은 권장 안함.






    // enum monthType { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
    // //                 0    1    2    3    4    5    6    7    8    9    10   11
    enum monthType { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
    //                 1        2    3    4    5    6    7    8    9    10   11   12
    typedef enum monthType Month;  // 별명


    printf("JAN=%d, DEC=%d\n", JAN, DEC);


    // // to count characters:
    // //   number, alphabet, white space, and all other characters
    // printf("This is a program to count characters.\n"
    //        "Press '#' key to end it:\n"
    //        ">>> ");
    // countCharacters();




    // union type:
    // ==========
    struct structDataType {
        int  number;
        char cArray[4];
    };
    typedef struct structDataType StructData;  // 별명


    union shareDataType {
        int  number;
        char cArray[4];
    };
    typedef union shareDataType ShareData;  // 별명


    // 변수 선언과 동시에 초기화
    StructData structData = { 0x41424344, "ABCD" };
    ShareData  shareData  = { 0x41424344 };


    printf(">>> sizeof structData = %d bytes\n", sizeof(structData));
    printf(">>> sizeof shareData = %d bytes\n", sizeof(shareData));


    printf(">>> shareData.number = 0x%x (= %d)\n", shareData.number, shareData.number);
    printf(">>> shareData.cArray[0] = %c\n", shareData.cArray[0]);
    printf(">>> shareData.cArray[1] = %c\n", shareData.cArray[1]);
    printf(">>> shareData.cArray[2] = %c\n", shareData.cArray[2]);
    printf(">>> shareData.cArray[3] = %c\n", shareData.cArray[3]);


}


// 구조체용 set 함수의 입력값은 구조체 변수의 주소와 저장할 값들로 구성됨
// void setLampInfo(struct lampInfoType *lampInfo,
//     int state, int kind, double batteryLevel, bool warning) {
void setLampInfo(LampInfo *lampInfo,
    int state, int kind, double batteryLevel, bool warning) {
    // (*lampInfo).state        = state;
    // (*lampInfo).kind         = kind;
    // (*lampInfo).batteryLevel = batteryLevel;
    // (*lampInfo).warning      = warning;


    lampInfo->state        = state;
    lampInfo->kind         = kind;
    lampInfo->batteryLevel = batteryLevel;
    lampInfo->warning      = warning;
}


// 타이틀과 함께 가로등 정보 출력
void printLampInfo(struct lampInfoType lampInfo, char *label) {
    char *stateName[3] = { "OFF", "ON", "BLINK" };
    char *kindName[5] = {
        "ORDINARY_LAMP", "MERCURY_LAMP",
        "FLUORESCENT_LAMP", "SODIUM_LAMP", "LED"
    };


    printf("%s=( ", label);
    printf("state=%s,", stateName[lampInfo.state]);
    printf("kind=%s,", kindName[lampInfo.kind]);
    printf("batteryLevel=%4.1f%%,", lampInfo.batteryLevel);
    printf("warning=%s )\n", (lampInfo.warning ? "WARNING" : "OK") );
}
