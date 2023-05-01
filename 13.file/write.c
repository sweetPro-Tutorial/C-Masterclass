// =====================================
// 텍스트 파일을 더 잘 다뤄 봅시다용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
#define LAMPS_SIZE 3

// 속성1) 가로등 상태 : 켜짐, 꺼짐, 깜박임
enum stateType { OFF, ON, BLINK };
// 속성2) 광원의 종류 : 보통 전구, 수은등, 형광등, 나트륨등, LED 전구
enum kindType { ORDINARY_LAMP, MERCURY_LAMP, FLUORESCENT_LAMP, SODIUM_LAMP, LED };
// 가로등 정보를 하나로 묶을 수 있는 구조체 타입:
struct lampInfoType {
    int    state;
    int    kind;
    double batteryLevel;
    bool   warning;
};
typedef  struct lampInfoType  LampInfo;  // 별명


// 타이틀과 함께 가로등 정보 출력
void printLampInfo(struct lampInfoType lampInfo, char *label);
// 타이틀과 함께 가로등 정보 파일에 저장
void saveLampInfo(FILE *fp, struct lampInfoType lampInfo, char *label);


int main() {
    // 파일 열기
    FILE *fp;
    char filename[100] = "lampdata.txt";
   
    fp = fopen(filename, "w+");
    if(fp == NULL) {
        printf("파일 %s 을 여는데 실패했습니다\n", filename);
        return 0;
    }

    // 가로등 정보 초기화
    LampInfo lamps[LAMPS_SIZE] = {
        { BLINK, LED, 77.7, true },
        { ON,    LED, 90.0, false },
        { OFF,   LED, 80.5, false }
    };
    // 가로등 정보 출력
    printLampInfo(lamps[0], "lamps 0");
    printLampInfo(lamps[1], "lamps 1");
    printLampInfo(lamps[2], "lamps 2");
    // 가로등 정보 저장
    saveLampInfo(fp, lamps[0], "lamps 0");
    saveLampInfo(fp, lamps[1], "lamps 1");
    saveLampInfo(fp, lamps[2], "lamps 2");

    // 문자열 "This is first line." 을 파일에 저장하는 코드
    // char buffer[100] = { 0, };
    // strcpy(buffer, "This is first line.");
    // fwrite(buffer, 1, strlen(line), fp);

    // 파일 닫기;
    fclose(fp);    

    return 0;
}

// 타이틀과 함께 가로등 정보 출력
char *stateName[3] = { "OFF", "ON", "BLINK" };
char *kindName[5] = {
        "ORDINARY_LAMP", "MERCURY_LAMP",
        "FLUORESCENT_LAMP", "SODIUM_LAMP", "LED"
};
void printLampInfo(struct lampInfoType lampInfo, char *label) {
    // printf("%s=( ", label);
    // printf("state=%s,", stateName[lampInfo.state]);
    // printf("kind=%s,", kindName[lampInfo.kind]);
    // printf("batteryLevel=%4.1f%%,", lampInfo.batteryLevel);
    // printf("warning=%s )\n", (lampInfo.warning ? "WARNING" : "OK") );

    // 위 코드를 한 줄의 printf 문으로 바꿔 쓰면:
    printf( "%s=( "
            "state=%s,"
            "kind=%s,"
            "batteryLevel=%4.1f%%,"
            "warning=%s )\n",
            label,
            stateName[lampInfo.state],
            kindName[lampInfo.kind],
            lampInfo.batteryLevel,
            (lampInfo.warning ? "WARNING" : "OK") );
}

// 타이틀과 함께 가로등 정보 파일에 저장:
// ==================================
// fprintf 를 사용한 코드
// void saveLampInfo(FILE *fp, struct lampInfoType lampInfo, char *label) {
//     fprintf(fp, "%s=( "
//             "state=%s,"
//             "kind=%s,"
//             "batteryLevel=%4.1f%%,"
//             "warning=%s )\n",
//             label,
//             stateName[lampInfo.state],
//             kindName[lampInfo.kind],
//             lampInfo.batteryLevel,
//             (lampInfo.warning ? "WARNING" : "OK") );
// }

// fputs 를 사용한 코드
// void saveLampInfo(FILE *fp, struct lampInfoType lampInfo, char *label) {
//     char line[100] = { 0, };

//     sprintf( line,
//         "%s=( "
//         "state=%s,"
//         "kind=%s,"
//         "batteryLevel=%4.1f%%,"
//         "warning=%s )\n",
//         label, stateName[lampInfo.state], kindName[lampInfo.kind],
//         lampInfo.batteryLevel, (lampInfo.warning ? "WARNING" : "OK") );
   
//     fputs(line, fp);
// }


// fwrite 를 사용한 코드
void saveLampInfo(FILE *fp, struct lampInfoType lampInfo, char *label) {
    char buffer[100] = { 0, };

    sprintf( buffer,
        "%s=( "
        "state=%s,"
        "kind=%s,"
        "batteryLevel=%4.1f%%,"
        "warning=%s )\n",
        label, stateName[lampInfo.state], kindName[lampInfo.kind],
        lampInfo.batteryLevel, (lampInfo.warning ? "WARNING" : "OK") );
 
    fwrite(buffer, 1, strlen(buffer), fp);
}
