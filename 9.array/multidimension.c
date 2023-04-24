// =====================================
// 2차원 배열용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
 
 
#define LAMPS_ROWS 2
#define LAMPS_SIZE 13
#define ON  1
#define OFF 0
 
 
// 1차원 배열 출력용 함수
void print1row(int *row, int size);
 
// 2차원 배열 출력용 함수
void printLamps2D(int (*lamps2D)[LAMPS_SIZE], int row_size, int col_size);
 
 
int main() {
    // 도로가의 가로등을 1차원 배열로 코딩하면:
    int lamps[LAMPS_SIZE] = { OFF, };  // 가로등의 개수는 13개임: 0 = Off, 1 = On
    lamps[9] = ON;  // 9번 가로등에 불이 들어왔음
 
    // case1: 도로 양쪽의 가로등을 한개의 1차원 배열로 표현:
    int lampsCase1[LAMPS_SIZE * 2] = { OFF, };
    lampsCase1[9] = ON;
    lampsCase1[22] = ON;  // 22 = LAMPS_SIZE + 9
 
    // case2: 도로 양쪽의 가로등을 각각 1차원 배열로 표현:
    int lamps1[LAMPS_SIZE] = { OFF, };  // 위쪽
    int lamps2[LAMPS_SIZE] = { OFF, };  // 아래쪽
    lamps1[9] = ON;
    lamps2[9] = ON;
 
    // case1 의 전체 데이터 순회:
    int onCount = 0;
    for(int i = 0; i < (LAMPS_SIZE * 2); i++) {
        if(lampsCase1[i] == ON) { onCount++; }
    }
    printf("On Count = %d\n", onCount);
 
    // case2: 4번째 열의 가로등을 모두 켜짐으로 바꾸려면
    lamps1[3] = ON;
    lamps2[3] = ON;
 
 
 
    // case3: 2차원 배열로 가로등 표현
    // int lamps2D[2][LAMPS_SIZE] = { { 0, }, };  // 가로 2줄 세로 13칸 즉, 2 x 13 배열
    int lamps2D[LAMPS_ROWS][LAMPS_SIZE] = { { 0, }, };  // 가로 2줄 세로 13칸 즉, 2 x 13 배열
    lamps2D[0][9] = 1;
    lamps2D[1][9] = 1;
 
 
    // 2차원 배열에서 현재 켜져 있는 가로등의 개수를 세는 알고리즘:
    // -------------------------------------------------------
    //   ① lamps2D 을 한 줄씩 조사한다.    
    //   ② 각 줄에 있는 켜진 등의 수를 센다.
 
 
 
    onCount = 0;
 
    // 모든 줄을 조사하기
    for(int row = 0; row < LAMPS_ROWS; row++) {  // 단계 ①
        // ② 한 줄(예: 첫번째 줄)을 조사하는 코드
        for(int column = 0; column < LAMPS_SIZE; column++) {
            if(lamps2D[0][column] == ON) onCount++;
        }
    }
    printf("On Count = %d\n", onCount);
 
 
 
    // 메모리 크기 = 배열의 크기 x 구성요소의 크기
    // ========================================
    // lamps2D memory size = (2 x 13) x 4
    //                     = 104 bytes
    printf("lamps2D 의 크기 = %d 바이트\n", sizeof(lamps2D));
    printf("lamps2D[0] 의 크기 = %d 바이트\n", sizeof(lamps2D[0]));
    printf("lamps2D[1] 의 크기 = %d 바이트\n", sizeof(lamps2D[1]));
    printf("lamps2D[0][9] 의 크기 = %d 바이트\n", sizeof(lamps2D[0][9]));
 
 
    // 3 차원 배열:
    // ==========
    // 만약 여러분이 프로그램을 작성하다가
    // 3차원 이상의 배열이 필요하다면 이렇게 생각하세요.
    // "내가 데이터 구조를 잘 못 설계했구나!" 라구요.
    int maps[3][8][10];  // 3 x 8 x 10 배열
   
   
   
    // 1차원 배열 출력용 함수 예:
    printf("[lamps2D]\n"
           "=========\n");
    for(int i = 0; i < LAMPS_ROWS; i++) {
        // header part:
        if(i == 0) { printf("lamps2D: lamps2D[%d]: ", i); }
        else       { printf("         lamps2D[%d]: ", i); }
       
        // body part:
        print1row(lamps2D[i], LAMPS_SIZE);
        printf("\n");
    }
   
   
    // 함수에 2차원 배열 전달 예:
    printf("[lamps2D]\n"
           "=========\n");
    printLamps2D(lamps2D, LAMPS_ROWS, LAMPS_SIZE);
   
   
 
}
 
// 1차원 배열 출력용 함수
void print1row(int *row, int size) {
    for(int i = 0; i < size; i++) {
        printf("[%d]", row[i]);
    }
}
 
// 2차원 배열 출력용 함수
void printLamps2D(int (*lamps2D)[LAMPS_SIZE], int row_size, int col_size) {
    for(int i = 0; i < row_size; i++) {
        // header part:
        if(i == 0) { printf("lamps2D: lamps2D[%d]: ", i); }
        else       { printf("         lamps2D[%d]: ", i); }
       
        // body part:
        for(int j = 0; j < col_size; j++) {
            printf("[%d]", lamps2D[i][j]);
        }
        printf("\n");
    }
}

