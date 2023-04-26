// =====================================
// App1 : 문자열 넘침 방지용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <string.h>


#define MAX_SIZE 100




// 오버플로를 일부러 발생시키는 함수
void makeOverflow();




int main() {
    // string overflow 예방법:
    // ======================
    // 첫 번째 방법 : 문자열 저장소의 크기를 충분히 크게!
    char phoneNumber[MAX_SIZE] = { 0, };
    strcpy(phoneNumber, "01012345678");




    // 두 번째 방법 : 양껏 담고 나머지는 버리기!
    char dest[MAX_SIZE] = { 0, };
    char source[300] =
        "YOUTH\n\n"
        "Youth is not a time of life, it is a state of mind; "
        "it is not a matter of rosy cheeks, red lips and supple knees; "
        "it is a matter of the will, a quality of the imagination, "
        "a vigor of the emotions; "
        "it is the freshness of the deep springs of life.\n\n";
   
    int S = MAX_SIZE;        // 저장될 공간의 크기 : S
    int L = strlen(source);  // 원본 문자열의 길이 : L
    strncpy(dest, source, S - 1);


    printf("원본 문자열(source) = [%s]\n", source);
    printf(">>> 문자열 길이 = [%d]\n\n", L);
    printf("복사된 문자열(dest) = [%s]\n", dest);
    printf(">>> 문자열 길이 = [%d]\n", strlen(dest));




    printf("[오버플로 발생 시 이상 증상을 보여주는 프로그램]\n");
    printf("프로그램 시작====\n");
    makeOverflow();
    printf("프로그램 종료----\n");
}




// 오버플로를 일부러 발생시키는 함수
void makeOverflow() {
    char saying[50] = "An overflow of good converts to bad.";
    char buffer[10] = { 0, };


    // 의심스러운 명령문 앞에 붙인 디버깅용 출력문
    printf(">>> Before copy:\n");
    printf(">>> 원본 문자열은 [%s], 길이는 [%d]\n", saying, strlen(saying));
    printf(">>> 저장공간인 buffer 의 크기는 [%d] Bytes\n\n", sizeof(buffer));


    // strcpy(buffer, saying);  // <<< 의심가는 부분
    strncpy(buffer, saying, sizeof(buffer) - 1);


    // 의심스러운 명령문 뒤에 붙인 디버깅용 출력문
    printf(">>> After copy:\n");
    printf(">>> 원본 문자열은 [%s], 길이는 [%d]\n", saying, strlen(saying));
    printf(">>> 저장공간인 buffer 의 크기는 [%d] Bytes\n\n", sizeof(buffer));
   
    printf("\t원본 문자열 saying = [%s]\n", saying);
    printf("\tbuffer 에 복사된 문자열 = [%s]\n", buffer);
}


