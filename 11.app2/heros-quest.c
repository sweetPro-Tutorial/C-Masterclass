// =====================================
// App1 : HerosQuest Game
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>
 
// 던전의 구성요소
#define HERO      'h'  // 용사
#define TRAP      'T'  // 함정
#define GOLD      'G'  // 골드
#define WALL      '#'  // 벽
#define EMPTY     ' '  // 빈 공간
 
// 맵 크기
#define MAP_ROWS   8
#define MAP_COLUMNS  10
 
// 맵
char map[MAP_ROWS][MAP_COLUMNS] = {
    "##########",
    "#     G  #",
    "#     T  #",
    "#    h   #",
    "#    TT G#",
    "#  T   G #",
    "#        #",
    "##########"
};
 
// 이동 명령어
#define LEFT       '4'
#define RIGHT      '6'
#define UP         '8'
#define DOWN       '2'
#define STAY       '5'
#define UP_LEFT    '7'
#define UP_RIGHT   '9'
#define DOWN_LEFT  '1'
#define DOWN_RIGHT '3'
 
// 용사의 상태
enum stateType { WIN = 1, DIE, PLAYING };
typedef enum stateType State;  // 별명
 
// 구조체 타입 선언
struct  positionType {
    int row;  // map 의 가로 인덱스
    int col;  // map 의 세로 인덱스
};
typedef  struct positionType  Position;
 
 
// 빈 함수 선언
void intro();  // 게임 소개 함수
void playHero();  // 용사 1회 플레이 함수


// 이동명령을 입력
char inputCommand();
// 용사의 현재 위치를 새 위치로 이동
State moveHero(char command);


// 용사의 현재위치를 찾는 기능
Position findHerosPosition();
// 이동할 새 위치를 계산하는 기능
Position makeHerosNewPosition(char command, Position oldPos);
// 새 위치로 이동이 가능한지 판단하는 기능
bool canMoveTo(Position newPos);
// 승패가 나는지 판단하는 기능
State checkGameState(Position newPos);
// 현재 맵에 있는 골드의 개수 카운트용
int countGold();


// 새 위치로 이동하는 기능
void moveHeroPosition(Position oldPos, Position newPos);




void printDungeon();  // 던전을 출력하는 함수
 
 
int main() {
    // printf("<<<  HERO'S  QUEST  >>>\n");
 
    intro();  // 게임 소개
    // makeDungeon();  // 던전 생성
    printDungeon();  // 던전 출력    
    playHero();  // 용사를 플레이하기
   
    return 0;
}
 
 
// 빈 함수 정의
void intro() {
    char *introMessage =
        "<<<  HERO'S  QUEST  >>>\n"
        "\n"
        "[ 목표 ]\n"
        "던전에 있는 함정을 피해 골드를 모으세요.\n"
        "골드를 모두 모으면 용사의 승리, 함정에 빠지면 패배입니다.\n"
        "\n"
        "[ 표시 ]\n"
        "용사 : h     벽 : #\n"
        "골드 : G     함정 : T\n"
        "\n"
        "[ 사용가능한 명령어 ]\n"
        "이동 : 7.8.9 (예: 4 를 입력하면 용사를 왼쪽으로 한칸 이동함)\n"
        "       4.h.6\n"
        "       1.2.3\n"
        "\n";
 
    printf("%s", introMessage);
    // printf("intro 아직 지원되지 않습니다\n");
}


// void makeDungeon() {
//     printf("makeDungeon 아직 지원되지 않습니다\n");
// }


void playHero() {
    char command;
    int restGold;


    State heroState;
    int moveCount = 0;
    while(true) {
        command = inputCommand(); // 이동명령을 입력;
        heroState = moveHero(command); // 용사의 현재 위치를 새 위치로 이동;
        moveCount++;
        printDungeon();
        if(heroState == WIN || heroState == DIE) { break; }  //만약 승패가 결정되었으면 반복문을 빠져나감;
    }
    printf(">>> %s\n", (heroState == WIN ? "Congratulation!" : "You Die...") );
}


// 이동명령을 입력
char inputCommand() {
    char command = STAY;


    printf(">>> 명령을 입력하세요 : ");
    scanf(" %c", &command);
    while(getc(stdin) != '\n');  // 키보드 버퍼 클랜징
   
    return command;
}


// 용사의 현재 위치를 새 위치로 이동
State moveHero(char command) {
    Position  oldPos;  // 현재 위치 저장용
    Position  newPos;  // 다음 위치 저장용
   
    oldPos = findHerosPosition();  // 용사의 현재위치를 찾는다;
    newPos = makeHerosNewPosition(command, oldPos);  // 이동할 새 위치를 계산한다;


    bool movable = canMoveTo(newPos);  // 새 위치로 이동이 가능한지 판단한다;


    State state = PLAYING;
    if(movable) {  // 만약 이동이 가능하면
        state = checkGameState(newPos);  // 승패가 나는지 판단한다;
        moveHeroPosition(oldPos, newPos);  // 새 위치로 이동시킨다;
    }
 
    return state;
}


// 용사의 현재위치를 찾는 기능
Position findHerosPosition() {
    int row;
    int col;
 
    Position hero;
    for(row = 0; row < MAP_ROWS; row++) {  // 배열을 한 줄씩 조사
        for(col = 0; col < MAP_COLUMNS; col++) {  // 현재 줄을 조사
            if(map[row][col] == HERO) {
                hero.row = row;
                hero.col = col;
 
                return hero;
            }
        }
    }
}


// 이동할 새 위치를 계산하는 기능
Position makeHerosNewPosition(char command, Position oldPos) {
    Position newPos = oldPos;
 
    // 이동할 새 위치 계산
    switch(command) {
    case LEFT       : newPos.col--; break;
    case RIGHT      : newPos.col++; break;
    case UP         : newPos.row--; break;
    case DOWN       : newPos.row++; break;
    case UP_LEFT    : newPos.row--; newPos.col--; break;
    case UP_RIGHT   : newPos.row--; newPos.col++; break;
    case DOWN_LEFT  : newPos.row++; newPos.col--; break;
    case DOWN_RIGHT : newPos.row++; newPos.col++; break;
    case STAY       : break;
    }
 
    return newPos;
}


// 새 위치로 이동이 가능한지 판단하는 기능
bool canMoveTo(Position newPos) {
    char what = map[newPos.row][newPos.col];

    switch(what) {
    case EMPTY: return true;  // 이동가능
    case WALL :
        return false; // 이동불가
    case TRAP :
        return true;
    case GOLD : return true;
    case HERO :
        return false;
    default   :
        return false;
    }
}


// 승패가 나는지 판단하는 기능
State checkGameState(Position newPos) {
    char what = map[newPos.row][newPos.col];
    int restGold = 0;  // 남은 골드 수 저장용

    switch(what) {
    case EMPTY: return PLAYING;  // 승패결정 안 났음
    case TRAP :
        return DIE;      // 패배 : 승패결정 났음
    case GOLD :
        restGold = countGold() - 1; // 골드 습득 후 나머지 골드 수 계산
        if(restGold == 0) { return WIN; }
        else { return PLAYING; }
    default   : return PLAYING;
    }
}
// 현재 맵에 있는 골드의 개수 카운트용
int countGold() {
    int count = 0;
    for(int row = 0; row < MAP_ROWS; row++) {
        for(int col = 0; col < MAP_COLUMNS; col++) {
            if(map[row][col] == GOLD) count++;
        }
    }
    return count;
}


// 새 위치로 이동하는 기능
void moveHeroPosition(Position oldPos, Position newPos) {
    map[newPos.row][newPos.col] = HERO;   // 대상을 새 위치로 이동
    map[oldPos.row][oldPos.col] = EMPTY;  // 전 위치는 비움
}






void printDungeon() {
    for(int row = 0; row < MAP_ROWS; row++) {
        for(int col = 0; col < MAP_COLUMNS; col++) {  // 가로로 한 줄 출력
            printf("%c", map[row][col]);
        }
        printf("\n");  // 다음 줄 출력 전에 줄 띄기
    }
 
    // printf("printDungeon 아직 지원되지 않습니다\n");
}
 
