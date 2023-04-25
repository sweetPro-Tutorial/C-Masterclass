// =====================================
// App1 : HerosQuest Game (version 2)
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>

//
// 던전 정보
//
// 던전의 구성요소
#define HERO      'h'  // 용사
#define TRAP      'T'  // 함정
#define GOLD      'G'  // 골드
#define WALL      '#'  // 벽
#define EMPTY     ' '  // 빈 공간
 
// 던전 map 크기
#define MAP_ROWS     8
#define MAP_COLUMNS  10
 
// 던전 map 초기화(기본형태)
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
 
//
// 명령어
//
// 이동 명령어(set 1)
#define LEFT       '4'
#define RIGHT      '6'
#define UP         '8'
#define DOWN       '2'
#define STAY       '5'
#define UP_LEFT    '7'
#define UP_RIGHT   '9'
#define DOWN_LEFT  '1'
#define DOWN_RIGHT '3'

// 이동 명령어(set 2) <<< [개선 아이디어1-이동명령 추가]
#define LEFT2      'A'
#define RIGHT2     'D'
#define UP2        'W'
#define DOWN2      'S'

#define LEFT3      'a'
#define RIGHT3     'd'
#define UP3        'w'
#define DOWN3      's'

//
// 사용자가 만들어 쓰는 타입들
//
// 용사의 상태 타입
enum stateType { WIN = 1, DIE, PLAYING };
typedef enum stateType State;  // 별명
 
// map 상의 위치 타입
struct  positionType {
    int row;  // map 의 가로 인덱스
    int col;  // map 의 세로 인덱스
};
typedef  struct positionType  Position;
 
//
// 함수 선언
//
// 게임 소개용
void intro();  
// 용사 1회 플레이용
void playHero();  
// 던전을 출력하는 함수
void printDungeon();  



// 이동명령 입력용
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

// 승패 메시지 출력용
void printGameOver(State heroState, int moveCount);

 
//
// 기능 구조도상의 최상위 기능은 main 함수가 됩니다.
//
//                 [main]
//                    |
//    +---------------+-----------------+
//    |               |                 |
// [intro]      [printDungeon]      [playHero]
//
int main() {
    intro();  // 게임 소개
    printf("던전의 모습은 아래와 같습니다.\n");
    printDungeon();  // 던전 출력    
    playHero();  // 용사를 플레이하기
   
    return 0;
}
 
// 게임 소개용
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
}

// 용사 1회 플레이용
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
    printGameOver(heroState, moveCount);
}

// 던전을 출력하는 함수
void printDungeon() {
    for(int row = 0; row < MAP_ROWS; row++) {
        for(int col = 0; col < MAP_COLUMNS; col++) {  // 가로로 한 줄(행) 출력
            printf("%c", map[row][col]);
        }
        printf("\n");  // 다음 행 출력 전에 줄 띄기
    }
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
    case LEFT3      :
    case LEFT2      :
    case LEFT       : newPos.col--; break;

    case RIGHT3     :
    case RIGHT2     :
    case RIGHT      : newPos.col++; break;

    case UP3        :
    case UP2        :
    case UP         : newPos.row--; break;

    case DOWN3      :
    case DOWN2      :
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
        printf("용사: 벽에 부딪혔습니다. 이동할 수 없습니다.\n");
        return false; // 이동불가
    case TRAP :
        printf("용사: 함정에 빠졌습니다.\n");
        return true;
    case GOLD : return true;
    case HERO :
        printf("용사: 대기합니다.\n");
        return false;
    default   :
        printf("용사: 대기합니다.\n");
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
        printf(">>> 아깝습니다. 패배했습니다.\n");
        return DIE;      // 패배 : 승패결정 났음
    case GOLD :
        restGold = countGold() - 1; // 골드 습득 후 나머지 골드 수 계산
        printf("용사: 골드를 모았습니다. 남은 골드는 %d 개 입니다.\n", restGold);
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



// 승패 메시지 출력용
void printGameOver(State heroState, int moveCount) {
    switch(heroState) {
    case WIN :
        printf( "* * * * * * * * * * * * * * * * * * *\n"
                "*                                   *\n"
                "*     Congratulation!   You Win!    *\n"
                "*                           ---     *\n"
                "* * * * * * * * * * * * * * * * * * *\n\n" );
        break;
    case DIE :
        printf( "     .-.    \n"
                "   __| |__  \n"
                "  [__   __] \n"
                "     | |    \n"
                "     | |    \n"
                "Die  | |    \n"
                "   -'''''-  \n\n" );
        break;
    }

    printf("\n점수: 용사의 이동 회수 = [%d]\n\n", moveCount);
    printf(">>> End of Play <<<\n\n");
}

