#include "encode.h"

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

char (*getMorseTable())[CODE_SIZE] {
    return morseTable;
}