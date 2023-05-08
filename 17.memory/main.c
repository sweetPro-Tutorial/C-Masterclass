#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test_stackOverflow();
void test_dynamicMemory();
void test_memset();
void test_realloc();
void test_not_use_realloc();


int main() {
    printf("hello world\n");

    // test_stackOverflow();
    test_dynamicMemory();
    test_memset();
    test_realloc();
    test_not_use_realloc();

    return 0;
}

void test_not_use_realloc() {
    char *string;

    printf("[test_not_use_realloc]\n");
    string = (char *)malloc(10);  // 할당된 동적 메모리는 10 바이트
    strcpy(string, "URL = ");
    printf("할당된 크기는 10 바이트\n");
    printf("내용 = [%s]\n", string);

    char *string50;  // 복사본용 식별자
    string50 = (char *)malloc(50);  // 복사본에 할당된 동적 메모리는 50 바이트
    sprintf(string50, "%swww.thankyouc.com", string);

    printf("할당된 크기는 50 바이트\n");
    printf("내용 = [%s]\n", string50);
   
    free(string);
    free(string50);
}

void test_realloc() {
    char *string;

    printf("[test_realloc]\n");
    string = (char *)malloc(10);  // 할당된 동적 메모리는 10 바이트
    strcpy(string, "URL = ");
    printf("할당된 크기는 10 바이트\n");
    printf("내용 = [%s]\n", string);

    string = (char *)realloc(string, 50);  // 할당된 동적 메모리 크기를 50 바이트로 변경
    strcat(string, "www.thankyouc.com");
    printf("할당된 크기는 50 바이트\n");
    printf("내용 = [%s]\n", string);
   
    free(string);
}


#define HEAP_SIZE  (50 * sizeof(int))  // 수식은 괄호 () 로 묶었음을 눈여겨 보세요

void test_memset() {
    int *heapArray = NULL;
   
    heapArray = (int *)malloc(HEAP_SIZE);  // HEAP_SIZE 만큼 메모리를 할당함
    printf("memset 전---------------------\n");
    printf("heapArray[0] = %d\n", heapArray[0]);
    printf("heapArray[1] = %d\n", heapArray[1]);

    memset(heapArray, 0, HEAP_SIZE);  // 메모리를 HEAP_SIZE 만큼 0으로 채움
   
    printf("0 으로 memset 후--------------\n");
    printf("heapArray[0] = %d\n", heapArray[0]);
    printf("heapArray[1] = %d\n", heapArray[1]);

    free(heapArray);
}


enum { GOLD, SILVER, BRONZE };
#define MEMORY_SIZE sizeof(int)
void test_dynamicMemory() {
    int score = 70;  // 지역변수

    printf("score = %d\n", score);
    printf("address = %p\n", malloc(MEMORY_SIZE));

    //
    // sample1:
    //
    int *age;  // 식별자 생성
    age = (int *)malloc(MEMORY_SIZE);
    *age = 10;

    int *ages;  // 식별자 생성
    ages = (int *)malloc(MEMORY_SIZE * 4);  // 동적 메모리 할당
    memset(ages, 0x00, MEMORY_SIZE * 4);  // 메모리 사용전 초기화
    // ages = (int *)calloc(MEMORY_SIZE * 4);  // 위 명령문 2개를 하나로 처리 가능
   
    ages[0] = 17;
    printf("*age = %d, ages[0] = %d\n", *age, ages[0]);

    free(age);
    free(ages);

    //
    // sample2:
    //
    int *medals;  // 식별자 생성
    medals = (int *)malloc(sizeof(int) * 3);  // 동적 메모리 할당
    medals[GOLD] = 17;  // 데이터 쓰기
    printf("GOLD medals = %d\n", medals[GOLD]);  // 데이터 읽기

    free(medals);  // 메모리 해제

    //
    // sample3: 문자열용 메모리 할당 예시
    //
    #define NAME_SIZE 20

    char *name;

    name = (char *)malloc(NAME_SIZE);
    memset(name, 0x00, NAME_SIZE);  // 메모리 사용전 초기화
    strncpy(name, "Eliza", NAME_SIZE - 1);
    printf("name = %s\n", name);

    free(name);  // 첫번째 free 성공
    // free(name);  // 같은 메모리에 2번 free: 에러 발생: 프로그램 강제 종료됨
    // printf("free is called two times\n");
}



void test_stackOverflow() {
    char array_1K[1024] = { 0, };       // 1  KB
    char array_1M[1024000] = { 0, };    // 1  MB
    char array_10M[10240000] = { 0, };  // 10 MB  <-- stack overflow 발생

    printf("Test memory: STACK size\n");
    printf("array_1K[0],array_1M[0],array_10M[0] = (%d,%d,%d)\n",
        array_1K[0], array_1M[0], array_10M[0]);
}
