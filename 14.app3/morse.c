// =====================================
// morse encoder, decoder 용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


// operation 코드
#define ENCODE  'e'  // for encode
#define DECODE  'd'  // for decode
#define QUIT    'q'  // 옵션이나 입력파일에 이상 발생 시


// toMorse:
// space symbols for toMorse
#define SPACE_BETWEEN_TWO_LETTERS  " "
#define SPACE_BETWEEN_TWO_WORDS    "/"
// state of 영문 텍스트 단어 식별용
#define OUTSIDE 0  // 상태 : 단어 밖 (현재 읽은 문자는 단어 밖에 있음)
#define INSIDE  1  // 상태 : 단어 안 (현재 읽은 문자는 단어 안에 있음)




// toText: 상태, 이벤트
#define OUT_CODE   0  // 상태 : 모스 코드 밖 (현재 읽은 문자는 코드 밖에 있음)
#define IN_CODE    1  // 상태 : 모스 코드 안 (현재 읽은 문자는 코드 안에 있음)
#define WORD       2  // 상태 : 모스 단어
#define WORD_FOUND 3  // 이벤트 : 단어 발견
#define CODE_FOUND 4  // 이벤트 : 모스 부호 발견
#define NA         5  // 이벤트 : 해당 사항 없음(Not Applicable)


char checkOption(int argc, char **argv);  // 옵션 검사
void toMorse(char *inputFileName, char *outputFileName);  // 영문 텍스트 --> 모스 부호로 변환
void toText(char *inputFileName, char *outputFileName);  // 모스 부호 --> 영문 텍스트로 변환
void anomalyReport();  // 이상 보고서: 옵션이나 입력파일의 문제 알림

void openFiles(FILE **input, FILE **output,
    char *inputFileName, char *outputFileName);
void closeFiles(FILE *inputFile, FILE *outputFile);

// 단어 식별
bool checkWord(int *statePointer, char ch);
// 모스 파일 식별
bool isMorseFile(FILE *fp);

// bool findMorseWord(char ch, int *statePointer);
// bool findMorseCode(char ch, int *statePointer);
int checkMorseChar(char ch, int *statePointer);


int main(int argc, char **argv) {
    printf("[ MORSE UTILITY ]\n");

    char operation = checkOption(argc, argv);  // 옵션 검사
    switch(operation) {
    case ENCODE: toMorse(argv[2], argv[3]); break;   // 모스 부호로 변환
    case DECODE: toText(argv[2], argv[3]);  break;   // 영문 텍스트로 변환
    default: anomalyReport(); break; // 이상 보고서: 옵션이나 입력파일의 문제 알림
    }

    return 0;
}


char checkOption(int argc, char **argv) {  // 옵션 검사
    // 옵션 공통 코드: 옵션의 개수 확인
    if(argc != 4) { return QUIT; }
    // 옵션 내용 검사
    if(strcmp(argv[1], "-e") == 0) { return ENCODE; }
    if(strcmp(argv[1], "-d") == 0) { return DECODE; }
    return QUIT;
}



#define CODE_SIZE  10
#define TABLE_SIZE 128

// use the standard: ITU-R M.1677-1 (10/2009)
char morseTable[TABLE_SIZE][CODE_SIZE] = {
    // 모스부호   인덱스
    // -------   ------
    { ""      }, // 0  (special character: N.A)    
    { ""      }, // 1      
    { ""      }, // 2      
    { ""      }, // 3      
    { ""      }, // 4      
    { ""      }, // 5      
    { ""      }, // 6      
    { ""      }, // 7      
    { ""      }, // 8      
    { ""      }, // 9      
    { ""      }, // 10      
    { ""      }, // 11      
    { ""      }, // 12      
    { ""      }, // 13      
    { ""      }, // 14      
    { ""      }, // 15      
    { ""      }, // 16      
    { ""      }, // 17      
    { ""      }, // 18      
    { ""      }, // 19      
    { ""      }, // 20      
    { ""      }, // 21      
    { ""      }, // 22      
    { ""      }, // 23      
    { ""      }, // 24      
    { ""      }, // 25      
    { ""      }, // 26      
    { ""      }, // 27      
    { ""      }, // 28      
    { ""      }, // 29      
    { ""      }, // 30      
    { ""      }, // 31      

    { ""       }, // 32 ' ' (The space between two words)
    { ""       }, // 33 !    (N.A)
    { ".-..-." }, // 34 "    
    { ""       }, // 35 #    
    { ""       }, // 36 $    
    { ""       }, // 37 %    
    { ""       }, // 38 &    
    { ".----." }, // 39 '    
    { "-.--."  }, // 40 (    
    { "-.--.-" }, // 41 )    
    { "-..-"   }, // 42 *    
    { ".-.-."  }, // 43 +    
    { "--..--" }, // 44 ,    
    { "-....-" }, // 45 -    
    { ".-.-.-" }, // 46 .    
    { "-..-."  }, // 47 /    

    { "-----" }, // 48 0    
    { ".----" }, // 49 1    
    { "..---" }, // 50 2    
    { "...--" }, // 51 3    
    { "....-" }, // 52 4    
    { "....." }, // 53 5    
    { "-...." }, // 54 6    
    { "--..." }, // 55 7    
    { "---.." }, // 56 8    
    { "----." }, // 57 9    

    { "---..." }, // 58 :    
    { ""       }, // 59 ;    
    { ""       }, // 60 <    
    { "-...-"  }, // 61 =    
    { ""       }, // 62 >    
    { "..--.." }, // 63 ?    
    { ".--.-." }, // 64 @    

    { ".-"    }, // 65 A    
    { "-..."  }, // 66 B    
    { "-.-."  }, // 67 C    
    { "-.."   }, // 68 D    
    { "."     }, // 69 E    
    { "..-."  }, // 70 F    
    { "--."   }, // 71 G    
    { "...."  }, // 72 H    
    { ".."    }, // 73 I    
    { ".---"  }, // 74 J    
    { "-.-"   }, // 75 K    
    { ".-.."  }, // 76 L    
    { "--"    }, // 77 M    
    { "-."    }, // 78 N    
    { "---"   }, // 79 O    
    { ".--."  }, // 80 P    
    { "--.-"  }, // 81 Q    
    { ".-."   }, // 82 R    
    { "..."   }, // 83 S    
    { "-"     }, // 84 T    
    { "..-"   }, // 85 U    
    { "...-"  }, // 86 V    
    { ".--"   }, // 87 W    
    { "-..-"  }, // 88 X    
    { "-.--"  }, // 89 Y    
    { "--.."  }, // 90 Z  

    { ""      }, // 91 [    
    { ""      }, // 92 '\'    
    { ""      }, // 93 ]    
    { ""      }, // 94 ^    
    { ""      }, // 95 _    
    { ""      }, // 96 `  

    { ".-"    }, // 97 a    
    { "-..."  }, // 98 b    
    { "-.-."  }, // 99 c    
    { "-.."   }, // 100 d    
    { "."     }, // 101 e    
    { "..-."  }, // 102 f    
    { "--."   }, // 103 g    
    { "...."  }, // 104 h    
    { ".."    }, // 105 i    
    { ".---"  }, // 106 j    
    { "-.-"   }, // 107 k    
    { ".-.."  }, // 108 l    
    { "--"    }, // 109 m    
    { "-."    }, // 110 n    
    { "---"   }, // 111 o    
    { ".--."  }, // 112 p    
    { "--.-"  }, // 113 q    
    { ".-."   }, // 114 r    
    { "..."   }, // 115 s    
    { "-"     }, // 116 t    
    { "..-"   }, // 117 u    
    { "...-"  }, // 118 v    
    { ".--"   }, // 119 w    
    { "-..-"  }, // 120 x    
    { "-.--"  }, // 121 y    
    { "--.."  }, // 122 z  

    { ""      }, // 123 {    
    { ""      }, // 124 |    
    { ""      }, // 125 }    
    { ""      }, // 126 ~    
    { ""      }, // 127    

};


void toMorse(char *inputFileName, char *outputFileName) {  // 영문 텍스트 --> 모스 부호로 변환
    int ascii = 0;
    FILE *inputFile;
    FILE *outputFile;

    openFiles(&inputFile, &outputFile, inputFileName, outputFileName);

    // 사전 검사: 유효한 입력파일인지 검사
    if(isMorseFile(inputFile)) {
        printf( "%s 는 유효한 입력파일이 아닙니다\n"
                ">>> may be morse-encoded file.\n", inputFileName);
        closeFiles(inputFile, outputFile);
        return;
    }
   
    // text to morse code
    int state;         // 상태용 변수 선언
    state = OUTSIDE;   // 초기값으로 단어가 없음 즉, "단어 밖" 을 줌.
    bool event = false;// 단어 발견 이벤트용 변수
    // char name[2][20] = { "OUTSIDE",   "INSIDE" };
    while( (ascii = fgetc(inputFile)) != EOF ) {
        // 단어와 단어 사이인 경우
        event = checkWord(&state, ascii);
        // printf("%c(0x%02x): ", ascii, ascii);  // test logging
        // printf(">>> state,event=(%s,%s)\n",
        //     name[state], event ? "WORD_FOUND" : "NA");  // test logging
        if(event) {
            fprintf(outputFile, "%s%s",
                SPACE_BETWEEN_TWO_WORDS, SPACE_BETWEEN_TWO_LETTERS);
            continue;
        }

        // 매칭된 모스 부호가 없는 경우
        if(strcmp(morseTable[ascii], "") == 0) { continue; }  // do nothing

        // 매칭된 모스 부호가 있는 경우
        fprintf(outputFile, "%s%s",
            morseTable[ascii], SPACE_BETWEEN_TWO_LETTERS);  // 변환한 모스 부호를 출력 파일에 저장한다;
    }
    printf(">>> 변환이 끝났습니다.\n");

    closeFiles(inputFile, outputFile);
}

// 단어 식별
bool checkWord(int *statePointer, char ch) {
    if(isspace(ch)) {
        if(*statePointer == INSIDE) {
            *statePointer = OUTSIDE;
            return true;
        }
    } else {  // 공백문자 외의 문자 발견 시        
        *statePointer = INSIDE;
    }

    return false;
}


void openFiles(FILE **input, FILE **output,
    char *inputFileName, char *outputFileName) {

    *input = fopen(inputFileName, "r");
    if(*input == NULL) {
        anomalyReport();

        exit(EXIT_FAILURE);
    }
    *output = fopen(outputFileName, "w");
    if(*output == NULL) {
        anomalyReport();
        if(*input != NULL) { fclose(*input); };
       
        exit(EXIT_FAILURE);
    }
}

void closeFiles(FILE *inputFile, FILE *outputFile) {
    if(inputFile != NULL) { fclose(inputFile); }
    if(outputFile != NULL) { fclose(outputFile); };
}

// 모스 파일 식별
#define TEXT_BUFFER_SIZE 1024
bool isMorseFile(FILE *fp) {
    char textBuffer[TEXT_BUFFER_SIZE] = { 0, };

    while(fgets(textBuffer, TEXT_BUFFER_SIZE, fp) != NULL) {
        for(int i = 0, ascii = 0; i < strlen(textBuffer); i++) {
            ascii = textBuffer[i];
            switch(ascii) {
            // 모스 파일에서 사용하는 문자들
            case '.' :
            case '-' :
            case ' ' :
            case '/' : continue;
            // 모스 파일에서 사용하지 않는 문자 발견
            default  :  
                fseek(fp, 0L, SEEK_SET);
                return false;
            }
        }
    }

    fseek(fp, 0L, SEEK_SET);
    return true;
}



void toText(char *inputFileName, char *outputFileName) {  // 모스 부호 --> 영문 텍스트로 변환
    int ascii = 0;
    char morseBuffer[CODE_SIZE] = { 0, };

    FILE *inputFile;
    FILE *outputFile;

    openFiles(&inputFile, &outputFile, inputFileName, outputFileName);

    // 사전 검사: 유효한 입력파일인지 검사
    if(!isMorseFile(inputFile)) {
        printf( "%s 는 유효한 입력파일이 아닙니다\n"
                ">>> may be english-text file.\n", inputFileName);
        closeFiles(inputFile, outputFile);
        return;
    }

    // morse code to text
    int ch;
    int i = 0;
    int state = OUT_CODE;  // 상태용 변수
    int event = NA;  // 이벤트용 변수
    // char name[6][20] = { "OUT_CODE",   "IN_CODE",    "WORD",
    //                      "WORD_FOUND", "CODE_FOUND", "NA" };
    while( (ch = fgetc(inputFile)) != EOF ) {
        ascii = 0;
        event = checkMorseChar(ch, &state);
        // printf(">>> state,event=(%s,%s)\n", name[state], name[event]);  // test

        // 단어와 단어 사이일 경우, 스페이스 문자로 변환한다;
        if(event == WORD_FOUND) {
            ascii = ' ';
        }

        // 모스 부호를 하나 발견한 경우, 문자 하나로 변환한다;
        if(ch == '.' || ch == '-') {  // 모스 부호용 문자인 . 또는 - 버퍼링
            morseBuffer[i] = ch;
            i++;
        }
        if(event == CODE_FOUND) {
            // 발견한 모스 부호와 매칭되는 영문자 검색
            for(int j = 0; j < TABLE_SIZE; j++) {  
                if(!strncmp(morseBuffer, morseTable[j], CODE_SIZE)) {  
                    ascii = j;  
                    break;
                }
            }
            // printf("morse code %s ==> '%c'\n", morseBuffer, ascii);  // test

            // 버퍼 초기화
            memset(morseBuffer, 0x00, CODE_SIZE);
            i = 0;
        }
           
        // 변환한 문자를 출력 파일에 저장한다;
        if(ascii != 0) { fputc(ascii, outputFile); }
    }
    printf(">>> 변환이 끝났습니다.\n");

    closeFiles(inputFile, outputFile);    
}


int checkMorseChar(char ch, int *statePointer) {
    switch(ch) {
    case '/' :  // 단어 식별자 발견 시
        if(*statePointer == OUT_CODE) {
            *statePointer = WORD;  
            return WORD_FOUND;  // 단어 발견 했음;
        }
        break;
    case ' ' :  // 공백문자 발견 시
        if(*statePointer == IN_CODE) {
            *statePointer = OUT_CODE;  
            return CODE_FOUND;  // 모스 부호 발견 했음;
        }
        else if(*statePointer == WORD) {
            *statePointer = OUT_CODE;  
        }
        break;
    case '.' :  // . 또는 - 문자 발견 시
    case '-' :
        if(*statePointer == OUT_CODE) {
            *statePointer = IN_CODE;
        }  
        break;
    default :
    }

    return NA;
}


bool findMorseWord(char ch, int *statePointer) {
    switch(ch) {
    case '/' :  // 단어 식별자 발견 시
        if(*statePointer == OUT_CODE) {
            *statePointer = WORD;  
            return true;// 단어 발견 했음;
        }
        break;
    case ' ' :  // 스페이스 문자 발견 시
        *statePointer = OUT_CODE;
        break;
    default :  // . 또는 - 문자 발견 시
    }

    return false;
}


bool findMorseCode(char ch, int *statePointer) {
    switch(ch) {
    case ' ' :  // 공백문자 발견 시
        if (*statePointer == IN_CODE) {
            *statePointer = OUT_CODE;
            return true;  // 모스 부호 발견 했음;
        }
        break;
    case '.' :  // . 또는 - 문자 발견 시
    case '-' :
        *statePointer = IN_CODE;  
        break;
    default :
    }

    return false;
}



char SYNOPSYS[] = "옵션에 이상이 있습니다(invalid option)\n"
                  "--------------------------------------\n"
                  "Usage: morse <operation> inputfilename outputfilename\n"
                  "\n"
                  "    Operations:\n"
                  "    -e\n"
                  "        ASCII 문자를 모스 부호로 변환(인코딩)\n"
                  "    -d\n"
                  "        모스 부호를 ASCII 문자로 변환(디코딩)\n";

void anomalyReport() {  // 이상 보고서: 옵션이나 입력파일의 문제 알림
    printf("%s", SYNOPSYS);
}

