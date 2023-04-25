// =====================================
// App1 : HerosQuest Game (version 3)
//   작성자 : 양상봉
//   작성일 : 
// =====================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//
// 던전 정보
//
// 던전의 구성요소
#define HERO      'h'  // 용사
#define TRAP      'T'  // 함정
#define GOLD      'G'  // 골드
#define WALL      '#'  // 벽
#define EMPTY     ' '  // 빈 공간
#define MONSTER   'M'  // 몬스터
#define COLUMN    '#'  // 기둥
 
// 던전 map 크기
#define MAP_ROWS     12
#define MAP_COLUMNS  16
 
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

// [개선 아이디어1-이동명령 추가]
// 이동 명령어(set 2)
#define LEFT2      'A'
#define RIGHT2     'D'
#define UP2        'W'
#define DOWN2      'S'

#define LEFT3      'a'
#define RIGHT3     'd'
#define UP3        'w'
#define DOWN3      's'

// [개선 아이디어5-이동명령 텔레포트 추가]
// 이동 명령어(set 3)
#define TELEPORT   'T'
#define TELEPORT2  't'

// 몬스터 최대 수
#define MAX_MONSTERS 10

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
State playHero();  
// 던전을 출력하는 함수
void printDungeon();
// [개선 아이디어3-자동 생성 map]
// 던전 생성: 벽/용사/골드/몬스터/트랩 등 생성
void makeDungeon();
// [개선 아이디어4-몬스터 추가]
// 턴제 플레이: 용사의 턴이 끝나면 몬스터의 턴.
void play();
// 컴퓨터에 의해 몬스터가 1회 움직임
State playMonster();

// 던전에 벽을 생성
void makeWall();
// 던전에 구성요소 배치
void setDungeon(char object, int max);

// 모든 몬스터의 현재위치 찾기: 몬스터의 수 반환
int findMonstersPosition(Position *oldPosList);
// 몬스터를 이동할 새 위치 결정
Position makeMonstersNewPosition(Position monstersPos, Position herosPos);
// 새 위치로 이동이 가능한지 판단
bool canMonsterMoveTo(Position newPos, int id);

// 이동명령 입력용
char inputCommand();
// 용사의 현재 위치를 새 위치로 이동
State moveHero(char command, int *restGoldPtr);

// 용사의 현재위치를 찾는 기능
Position findHerosPosition();
// 이동할 새 위치를 계산하는 기능
Position makeHerosNewPosition(char command, Position oldPos);
// 새 위치로 이동이 가능한지 판단하는 기능
bool canMoveTo(Position newPos, char command);
// [개선 아이디어2-성능 개선]
// 승패가 나는지 판단하는 기능
State checkGameState(Position newPos, int *restGoldPtr, char command);
// 현재 맵에 있는 골드의 개수 카운트용
int countGold();
// 새 위치로 이동하는 기능
void movePosition(Position oldPos, Position newPos, char kind);

// 승패 메시지 출력용
void printGameOver(State heroState, int moveCount);

 
//
// 기능 구조도상의 최상위 기능은 main 함수가 됩니다.
//
//                   [main]
//                      |
//    +-----------+-----+-----+------------+
//    |           |           |            |
// [intro]  [makeDungeon]   [play]   [printDungeon]
//                            |              
//                    +-------+-------+
//                    |               |
//               [playHero]     [playMonster]
//
int main() {
    intro();  // 게임 소개
    makeDungeon();  // <<< [개선 아이디어3-자동 생성 map]
    printf("던전의 모습은 아래와 같습니다.\n");
    printDungeon();  // 던전 출력    
    play();
   
    return 0;
}



// [개선 아이디어4-몬스터 추가]
// 턴제 플레이: 용사의 턴이 끝나면 몬스터의 턴.
void play() {
    int moveCount = 0;
    State heroState;

    while(true) {
        // 용사의 턴
        heroState = playHero();  // 현재 위치를 새 위치로 이동
        moveCount++;
        if(heroState == WIN || heroState == DIE) {  // 승패결정 시 빠져나감
            printDungeon();
            break;
        }  

        // 몬스터의 턴
        heroState = playMonster();
        printDungeon();
        if(heroState == DIE) { break; }  // 승패결정 시 빠져나감
    }
    printGameOver(heroState, moveCount);
}



// 컴퓨터에 의해 몬스터가 1회 움직임
State playMonster() {
    Position monstersPos[MAX_MONSTERS] = { 0, };
    // 몬스터들의 현재위치 찾기
    int monsterCount = findMonstersPosition(monstersPos);  
    // 용사의 현재위치 찾기
    Position herosPos = findHerosPosition();  

    Position newPos;
    Position oldPos;
    bool movable;
    State state = PLAYING;
    char target;
    for(int i = 0; i < monsterCount; i++) {
        // 몬스터를 이동할 새 위치 결정
        oldPos = monstersPos[i];
        newPos = makeMonstersNewPosition(oldPos, herosPos);
        // 새 위치로 이동이 가능한지 판단
        movable = canMonsterMoveTo(newPos, i);
        if(movable) {
            // 승패가 나는지 판단
            target = map[newPos.row][newPos.col];
            if(target == HERO) { state = DIE; }
            // 새 위치로 이동
            movePosition(oldPos, newPos, MONSTER);  
            if(state == DIE) { return state; }
        }
    }

    return state;
}



// 모든 몬스터의 현재위치 찾기: 몬스터의 수 반환
int findMonstersPosition(Position *oldPosList) {
    int i = 0;

    for(int row = 0; row < MAP_ROWS; row++) {
        for(int col = 0; col < MAP_COLUMNS; col++) {
            if(map[row][col] == MONSTER) {
                oldPosList[i].row = row;
                oldPosList[i].col = col;
                i++;
            }
        }
    }

    return i;
}

// 몬스터를 이동할 새 위치 결정
Position makeMonstersNewPosition(Position monstersPos, Position herosPos) {
    Position newPos = monstersPos;

    // 용사를 세로 방향으로 추적 계산
    if(newPos.row < herosPos.row) { newPos.row++; }
    else if(newPos.row > herosPos.row) { newPos.row--; }

    // 용사를 가로 방향으로 추적 계산
    if(newPos.col < herosPos.col) {newPos.col++; }
    else if(newPos.col > herosPos.col) { newPos.col--; }

    return newPos;
}

// 새 위치로 이동이 가능한지 판단
bool canMonsterMoveTo(Position newPos, int id) {
    // 이동할 위치에 무엇이 있는지 확인
    char target = map[newPos.row][newPos.col];
    switch(target) {
    case WALL       :
        printf("몬스터-%d: 벽에 부딪혔습니다. 이동할 수 없습니다.\n", id);
        return false;
    case MONSTER    :
        printf("몬스터-%d: 몬스터에 부딪혔습니다. 이동할 수 없습니다.\n", id);
        return false;
    case TRAP       :
        printf("몬스터-%d: 트랩이 있어서 이동할 수 없습니다.\n", id);
        return false;
    case HERO       :
        printf("몬스터-%d: 용사를 잡았습니다. 컴퓨터의 승리입니다.\n", id);
        return true;
    case EMPTY      :
        printf("몬스터-%d: [%d][%d] 로 이동했습니다.\n", id, newPos.row, newPos.col);
        return true;
    case GOLD       :
        printf("몬스터-%d: 골드를 발견하고 그 주변에 대기합니다.\n", id);
        return false;
    default         :
        printf("몬스터-%d: 대기합니다.\n", id);
        return false;
    }
}



// [개선 아이디어3-자동 생성 map]
// 던전 생성: 벽/용사/골드/몬스터/트랩 등 생성
void makeDungeon() {
    srand(time(NULL));  // 난수 발생기 초기화

    // 던전을 깨끗이 지움
    for(int row = 0; row < MAP_ROWS; row++) {
        for(int col = 0; col < MAP_COLUMNS; col++) {
            map[row][col] = EMPTY;
        }
    }  

    makeWall();  // 던전에 벽을 생성
    setDungeon(COLUMN, 3);  // 던전에 기둥 생성
    setDungeon(TRAP, 3);  // 던전에 트랩 생성
    setDungeon(HERO, 1);  // 던전에 용사 생성
    setDungeon(GOLD, 3);  // 던전에 골드 생성
    setDungeon(MONSTER, 2);  // 던전에 몬스터 생성
}

// 던전에 벽을 생성
void makeWall() {
    // 맵 태두리에 벽 세우기
    for(int col = 0; col < MAP_COLUMNS; col++) {
        map[0][col] = WALL;  // 위쪽 벽
        map[MAP_ROWS - 1][col] = WALL;  // 아래쪽 벽
    }
    for(int row = 0; row < MAP_ROWS; row++)  {
        map[row][0] = WALL;  // 왼쪽 벽
        map[row][MAP_COLUMNS - 1] = WALL;  // 오른쪽 벽
    }    
}

// 던전에 구성요소 배치
void setDungeon(char object, int max) {
    int col;
    int row;
    int count = 0;

    while(count < max) {  // 그 외의 것 만들기
        row = rand() % MAP_ROWS;
        col = rand() % MAP_COLUMNS;
        if(map[row][col] == EMPTY) {
            map[row][col] = object;
            count++;
        }
    }    
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
        "이동     : 7.8.9 (예: 4 를 입력하면 용사를 왼쪽으로 한칸 이동함)\n"
        "           4.h.6\n"
        "           1.2.3\n"
        "                 또는\n"
        "             W\n"
        "           A.S.D\n"
        "텔레포트 : T\n"
        "\n";
 
    printf("%s", introMessage);
}

// 용사 1회 플레이용
State playHero() {
    int restGold = countGold();
    char command = inputCommand(); // 이동명령을 입력;
    State heroState = moveHero(command, &restGold); // 용사의 현재 위치를 새 위치로 이동;

    return heroState;
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
State moveHero(char command, int *restGoldPtr) {
    Position  oldPos;  // 현재 위치 저장용
    Position  newPos;  // 다음 위치 저장용
   
    oldPos = findHerosPosition();  // 용사의 현재위치를 찾는다;
    newPos = makeHerosNewPosition(command, oldPos);  // 이동할 새 위치를 계산한다;

    bool movable = canMoveTo(newPos, command);  // 새 위치로 이동이 가능한지 판단한다;

    State state = PLAYING;
    if(movable) {  // 만약 이동이 가능하면
        // 승패가 나는지 판단한다;
        state = checkGameState(newPos, restGoldPtr, command);  // 승패가 나는지 판단한다;
        movePosition(oldPos, newPos, HERO);  // 새 위치로 이동시킨다;
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

    case TELEPORT2  :
    case TELEPORT   :  // [개선 아이디어5-이동명령 텔레포트 추가]
        newPos.row = ( rand() % (MAP_ROWS    - 2) ) + 1;
        newPos.col = ( rand() % (MAP_COLUMNS - 2) ) + 1;
        printf("용사: 텔레포트를 시도 합니다.\n");
        break;    
    }
 
    return newPos;
}

// 새 위치로 이동이 가능한지 판단하는 기능
bool canMoveTo(Position newPos, char command) {
    char what = map[newPos.row][newPos.col];

    switch(what) {
    case EMPTY: return true;  // 이동가능
    case WALL : // [개선 아이디어5-이동명령 텔레포트 추가]
        if(command == TELEPORT2 || command == TELEPORT) {
            printf("용사: 이런! 벽 속으로 텔레포트 되었습니다.\n");
            return true;
        }
        printf("용사: 벽에 부딪혔습니다. 이동할 수 없습니다.\n");
        return false; // 이동불가
    case TRAP :
        printf("용사: 함정에 빠졌습니다.\n");
        return true;
    case GOLD : return true;
    case HERO :
        printf("용사: 대기합니다.\n");
        return false;
    case MONSTER:
        printf("용사: 잘못된 만남입니다. 몬스터에서 잡혔습니다.\n");
        return true;
    default   :
        printf("용사: 대기합니다.\n");
        return false;
    }
}

// 승패가 나는지 판단하는 기능
State checkGameState(Position newPos, int *restGoldPtr, char command) {
    char what = map[newPos.row][newPos.col];
    int restGold = 0;  // 남은 골드 수 저장용

    switch(what) {
    case EMPTY: return PLAYING;  // 승패결정 안 났음
    case TRAP : return DIE;      // 패배 : 승패결정 났음
    case GOLD :  // [개선 아이디어2-성능 개선]
        (*restGoldPtr)--; // 골드 습득 후 남은 골드 수 계산
        restGold = *restGoldPtr;
        printf("용사: 골드를 모았습니다. 남은 골드는 %d 개 입니다.\n", restGold);
        if(restGold == 0) { return WIN; }
        return PLAYING;
    case WALL :  // [개선 아이디어5-이동명령 텔레포트 추가]
        if(command == TELEPORT2 || command == TELEPORT) {
            return DIE;
        }
    case MONSTER: return DIE;
    default     : return PLAYING;
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
void movePosition(Position oldPos, Position newPos, char kind) {
    char object;

    switch(kind) {
    case HERO   : object = HERO; break;
    case MONSTER: object = MONSTER; break;
    default     : object = HERO; break;
    }

    map[newPos.row][newPos.col] = object;   // 대상을 새 위치로 이동
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
