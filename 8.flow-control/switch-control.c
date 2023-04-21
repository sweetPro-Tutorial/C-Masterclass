// =====================================
// switch control용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <stdbool.h>


#define EASY      0
#define NORMAL    1
#define HARD      2
#define NIGHTMARE 3


#define MAX_TEMPERATURE 100




// 게임의 난이도에 따라 등장하는 적의 수 세팅
void setNoOfEnemies_usingif(int difficulty, int *noOfEnemies);
void setNoOfEnemies_usingswitch(int difficulty, int *noOfEnemies);


// to count characters:
//   number, alphabet, white space, and all other characters
void countCharacters(void);




int main() {
    int difficulty = NORMAL;
    int noOfEnemies = 0;
    setNoOfEnemies_usingif(difficulty, &noOfEnemies);
    printf("difficulty, noOfEnemies = %d, %d\n", difficulty, noOfEnemies);


    setNoOfEnemies_usingswitch(difficulty, &noOfEnemies);
    printf("difficulty, noOfEnemies = %d, %d\n", difficulty, noOfEnemies);


    // to count characters:
    //   number, alphabet, white space, and all other characters
    printf("This is a program to count characters.\n"
           "Press '#' and Enter key to end it:\n"
           ">>> ");
    countCharacters();


   
    // 조건 연산자의 사용법:
    //   조건식  ?  계산식A  :  계산식B


    // 조건 연산자는 다음의 if 문을 축약한 형태임:
    // if(조건식이 참이면) {
    //     계산식A;
    // }
    // else {
    //     계산식B;
    // }




    int temperature = 40;
    bool isAlarm = false;


    // 조건 연산자:
    isAlarm = (temperature > MAX_TEMPERATURE) ? true : false;
    // if 문으로 바꿔 쓰면:
    if(temperature > MAX_TEMPERATURE) {
        isAlarm = true;
    }
    else {
        isAlarm = false;
    }


    // 값 위치에 블럭이 오는 경우는 조건연산자를 쓸 수 없습니다:
    // isAlarm = (temperature > MAX_TEMPERATURE)
    //     ? { printf("참일   때 실행할 명령문\n"); }
    //     : { printf("거짓일 때 실행할 명령문\n"); };  // 에러
    // 위 코드는 compiler error 발생:
    //   error: expected expression before '{' token


    // 덧셈 연산자 + 는 피연산자가 2개인 연산자:
    //   A + B
    // 조건연산자 ? : 은 피연산자가 3개인 연산자:
    //   C ? A : B




    return 0;
}






#define END_MARK '#'


void countCharacters(void) {
    int character;
    int noWhiteSpace = 0;
    int noNumber = 0;
    int noAlphabet = 0;
    int noOther = 0;


    while( (character = getchar()) != END_MARK) {
        switch (character) {
        case ' ' :
        case '\t':
        case '\n':
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


// 게임의 난이도에 따라 등장하는 적의 수 세팅
void setNoOfEnemies_usingif(int difficulty, int *noOfEnemies) {
    if (difficulty == EASY) {
        *noOfEnemies = 2;   // EASY 모드에 등장하는 적의 수 세팅
    } else if (difficulty == NORMAL) {
        *noOfEnemies = 5;   // NORMAL 모드에 등장하는 적의 수 세팅
    } else if (difficulty == HARD) {
        *noOfEnemies = 10;  // HARD 모드에 등장하는 적의 수 세팅
    } else if (difficulty == NIGHTMARE) {
        *noOfEnemies = 30;  // NIGHTMARE 모드에 등장하는 적의 수 세팅
    } else {
        *noOfEnemies = 5;   // 등장하는 적의 수를 기본 값(default value)으로 세팅
    }
}


void setNoOfEnemies_usingswitch(int difficulty, int *noOfEnemies) {
    switch(difficulty) {
    case EASY:
        *noOfEnemies = 2;   // EASY case 실행
        break;
    case NORMAL:
        *noOfEnemies = 5;   // NORMAL case 실행
        break;
    case HARD:
        *noOfEnemies = 10;  // HARD case 실행
        break;
    case NIGHTMARE:
        *noOfEnemies = 30;  // NIGHTMARE case 실행
        break;
    default:
        *noOfEnemies = 5;   // default case 실행
        break;
    }
}
