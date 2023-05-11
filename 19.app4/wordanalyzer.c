//
// Word Analyzer
//   version 1 : word counter
//   version 2 : + word frequency counter
//   version 2.1 : + 단어 오인식 버그 픽스, 목록 소팅 기능 추가
//   version 3 : + 블랙 리스트(word)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define VERSION     "3.0"
#define BUFFER_SIZE 1024
#define MAX_WORDS   20000  // MAX NDW(number of different words)
#define WORD_LENGTH 45
#define BLACKLIST_SIZE 100

typedef char Word[WORD_LENGTH + 1];  // 단어 타입 정의

struct wordInfoType {
    Word word;      // 단어
    int frequency;  // 출현빈도
};
typedef struct wordInfoType WordInfo;  // 단어정보 타입 정의

// for ver.1
FILE *openStream(int argc, char **argv);
void closeStream(FILE *fp, int argc);

// for ver.2
void countWordFrequency(WordInfo *words, char *word, int *uniqueWordCount);
void printResult(int totalWordCount, int uniqueWordCount, WordInfo *words);

// for ver.2.1
void preprocessWord(char *word, char *buffer);  // 단어를 대문자로 변경하고,
                                                // 단어 앞뒤의 기호 제거
void sort(WordInfo *words, int listSize);
int compareFrequency(const void * a, const void * b);  // 빈도수 순으로 정렬
int compareAlpha(const void * a, const void * b);  // 알파벳 순으로 정렬
void partialSort(int startIndex, int rearIndex, WordInfo *words, int frequency);  // 부분 정렬

// for ver.3
// void loadBlackList(char (*blacklist)[WORD_LENGTH + 1]);  // 데이터 로딩
void loadBlackList(Word *blacklist);  // 데이터 로딩
bool isBlacklisted(char *word, Word *blacklist);

int main(int argc, char **argv) {
    char buffer[BUFFER_SIZE + 1];
    FILE *stream = openStream(argc, argv);

    printf( "[ Word Analyzer Ver.%s ]\n", VERSION);
    // printf( "문장을 입력하세요.\n"
    //         "끝내려면 Ctrl+Z 를 누른 후 Enter 키를 누르세요(리눅스는 Ctrl+D) :\n");

    // char blacklist[BLACKLIST_SIZE][WORD_LENGTH + 1] = { 0, };
    Word blacklist[BLACKLIST_SIZE] = { 0, };
    loadBlackList(blacklist);  // 데이터 로딩

    // 총 단어 수 계산
    int totalWordCount = 0;  // for ver.1
    int uniqueWordCount = 0;  // for ver.2
    WordInfo words[MAX_WORDS] = { 0, };
    char word[WORD_LENGTH + 1] = { 0, };  // for ver.2.1
    while ( fscanf(stream, "%s", buffer) != EOF ) {
        preprocessWord(word, buffer);
        if(strlen(word) == 0) { continue; }  // 빈 문자열 검사
        if(isBlacklisted(word, blacklist)) { continue; }  // Blacklist 검사

        totalWordCount++;
        countWordFrequency(words, word, &uniqueWordCount);
    }
    sort(words, uniqueWordCount);
    printResult(totalWordCount, uniqueWordCount, words);

    closeStream(stream, argc);
}

bool isBlacklisted(char *word, Word *blacklist) {
    const char EMPTY = '\0';
    for(int i = 0; i < BLACKLIST_SIZE; i++) {
        if(blacklist[i][0] == EMPTY) { return false; }  // blacklist 의 끝 검사

        if(strncmp(word, blacklist[i], WORD_LENGTH) == 0) { return true; }
    }
    return false;
}

void loadBlackList(Word *blacklist) {  // 블랙리스트 데이터 로딩
    FILE *fp;
    char *filename = "blacklist.txt";
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf( "blacklist 데이터 파일 %s 을 여는데 실패했습니다\n"
                ">>> blacklist 없이 실행됩니다.\n", filename);
        return;
    }

    Word word = { 0, };
    int index = 0;
    while(fscanf(fp, "%s", word) != EOF) {
        const char END = '\0';
        for(int i = 0; word[i] != END; i++) {  // 대문자로 변환
            word[i] = toupper( (unsigned char) word[i] );
        }

        strcpy(blacklist[index], word);
        printf(">>> set blacklist[%d] = [%s]\n", index, blacklist[index]);
        index++;

        if(index >= BLACKLIST_SIZE) { break; }  // 오버플로우 검사
    }
    fclose(fp);
}

void sort(WordInfo *words, int listSize) {
    if(listSize == 0) { return; }

    // 빈도 순으로 정렬
    qsort(words, listSize, sizeof(WordInfo), compareFrequency);

    // 같은 빈도끼리 알파벳 순으로 정렬
    int frequency = 0;
    int nextFrequency = 0;
    int startIndex = 0;
    int lastIndex = listSize - 1;
    for(int i = 0; i <= lastIndex; i++) {
        // 목록을 순회하면서 빈도수가 달라지는 위치를 파악
        frequency = words[i].frequency;
        nextFrequency = words[i + 1].frequency;
        if(frequency == nextFrequency) { continue; }

        // 만약 빈도수가 바뀌면, 현재 빈도수의 단어들을 알파벳 순으로 소팅
        partialSort(startIndex, i, words, frequency);

        startIndex = i + 1;
    }
    // 순회가 끝난 후, 만약 미처리된 데이터가 있으면 처리
    if(startIndex < lastIndex) {
        partialSort(startIndex, lastIndex, words, frequency);
    }
}

void partialSort(int startIndex, int rearIndex, WordInfo *words, int frequency) {  // 부분 정렬
    // printf(">>> frequency %d: index range = [%d ~ %d]\n", frequency, startIndex, rearIndex);  // test log
    int size = (rearIndex - startIndex) + 1;
    WordInfo *startPosition = &(words[startIndex]);
    qsort(startPosition, size, sizeof(WordInfo), compareAlpha);
}

int compareAlpha(const void * a, const void * b) {  // 알파벳 순으로 정렬
    char *value1 = ((WordInfo*)a)->word;
    char *value2 = ((WordInfo*)b)->word;
    int compareResult = strcmp(value1, value2);  // 올림차순
    // printf(">>> compare result: %s,%s --> %d\n", value1, value2, compareResult);  // test log

    return compareResult;
}

int compareFrequency(const void * a, const void * b) {  // 빈도수 순으로 정렬
    int value1 = ((WordInfo*)a)->frequency;
    int value2 = ((WordInfo*)b)->frequency;
    int compareResult = value2 - value1;  // 내림차순
    // printf(">>> compare result: %d,%d --> %d\n", value1, value2, compareResult);  // test log
 
    return compareResult;
}



void preprocessWord(char *word, char *buffer) {
    // 단어를 대문자로 변환한다.
    const char END = '\0';
    for(int i = 0; buffer[i] != END; i++) {
        buffer[i] = toupper( (unsigned char) buffer[i] );
    }

    // 단어 앞에 기호가 있으면 제거한다.
    char *wordStartPosition;
    int index = 0;
    while( !isalpha(buffer[index]) ) {
        if(buffer[index] == END) { break; }
        index++;
    }
    wordStartPosition = &(buffer[index]);
    // while( !isalpha(*wordStartPosition) ) {
    //     if(*wordStartPosition == END) { break; }
    //     wordStartPosition++;
    // }

    // 단어 뒤에 기호가 있으면 제거한다.
    if(wordStartPosition[0] == END) {  // 더이상 처리할 문자열이 없으면 끝냄
        word[0] = END;
        return;
    }  

    int backIndex = strnlen(wordStartPosition, WORD_LENGTH) - 1;
    for(int i = backIndex; i >= 0; i--) {  // 역방향 순회
        if(isalpha(buffer[i])) {
            buffer[i + 1] = END;
            break;
        }
    }

    memset(word, 0, WORD_LENGTH + 1);  // 사용하기 전에 초기화
    strncpy(word, wordStartPosition, WORD_LENGTH);
}


void printResult(int totalWordCount, int uniqueWordCount, WordInfo *words) {
    printf("Total  words = %d\n", totalWordCount);
    printf("Unique words = %d\n", uniqueWordCount);
    printf("======================================\n");
    printf("word                 Frequency  Length\n");
    printf("-------------------- ---------- ------\n");
    for(int i = 0; i < uniqueWordCount; i++) {
        printf("%-20s %-10d %-10d\n",
            words[i].word, words[i].frequency, (int)strlen(words[i].word));
    }
}


void countWordFrequency(WordInfo *words, char *word, int *uniqueWordCount) {
    // 단어가 단어 목록에 있는지 검사
    bool found = false;
    int foundIndex = 0;
    int lastIndex = *uniqueWordCount - 1;
    for(int i = 0; i <= lastIndex; i++) {
        if(strncmp(words[i].word, word, WORD_LENGTH) == 0) {
            found = true;
            foundIndex = i;
            break;
        }
    }

    // 단어 목록에 있는 단어일 경우, 출현 빈도수를 증가시키고,
    if(found) {
        words[foundIndex].frequency++;        
        return;
    }

    // 단어 목록에 없는 단어일 경우, 단어 목록에 추가한다.
    int newIndex = lastIndex + 1;
    if(newIndex >= MAX_WORDS) {  // error flow: 배열 overflow 검사
        printf( ">>> ERROR: 단어 목록에 overflow 발생하여 프로그램을 종료합니다.\n"
                ">>> 현재 목록 사이즈: %d\n", newIndex);
        exit(2);
    }  
 
    strncpy(words[newIndex].word, word, WORD_LENGTH);  // 새 단어정보를 목록에 추가
    words[newIndex].frequency = 1;
 
    (*uniqueWordCount)++;  // 목록 안에 저장된 총 단어수를 증가
}



FILE *openStream(int argc, char **argv) {
    // 파일 옵션 지원
    switch(argc) {
    case 1: // 파일 옵션이 없으면: 표준 입력을 사용;
        return stdin;
    case 2: // 파일 옵션이 있으면: 이 파일을 사용;
        char *filename = argv[1];
        FILE *fp = fopen(filename, "r");
        if(fp == NULL) {
            printf("파일 %s 을 여는데 실패했습니다\n", filename);
            exit(1);
        }
        return fp;
    default:  // 파일 옵션이 여럿이면: 유효한 옵션 아님;
        printf( "Usage:\n"
                "    wordanalyzer [filename]\n");
        exit(2);
    }
}

void closeStream(FILE *fp, int argc) {
    if(argc == 2) {
        if(fp != NULL) { fclose(fp); }
    }
}

