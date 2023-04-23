// =====================================
// 터미널에서 한글을 입력 받을 경우용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <string.h>
// #include <locale.h>

#define MAX_NAME_SIZE 50

int main(void) {
    // setlocale(LC_ALL, "");
    char name[MAX_NAME_SIZE] = { 0, };
    printf("Enter your name (up to %d characters): ", MAX_NAME_SIZE - 1);
    fflush(stdout);
    fgets(name, MAX_NAME_SIZE, stdin);
    printf("length = %d\n", strlen(name));
    printf("name   = %s\n", name);

    printf("Your name in UTF-8 hexadecimal code:\n");
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] <= 0x7F) {
            // ASCII character, output directly
            printf("%02x ", (unsigned char)name[i]);
        } else if (name[i] <= 0x7FF) {
            // 2-byte UTF-8 character
            printf("%02x %02x ", 
                (unsigned char)name[i], 
                (unsigned char)name[i + 1]);
            i++;
        } else {
            // 3-byte UTF-8 character
            printf("%02x %02x %02x ", 
                (unsigned char)name[i], 
                (unsigned char)name[i + 1], 
                (unsigned char)name[i + 2]);
            i = i + 2;
        }
    }
    printf("\n"); 

    return 0;
}
