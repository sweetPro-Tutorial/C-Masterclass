// =====================================
// bit 연산용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>


int main() {


    // 진수별 디지트들:
    // -------------
    // 10 진수용 digit: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 의 10 개
    //  2 진수용 digit: 0 과 1 의 2 개
    // 16 진수용 digit: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F 의 16 개


    // 10진수 250 = 2진수 11111010




/*
    10진수         2진수             16진수
    -----          ---------         -----
    0              0000 0000         0x00
    1              0000 0001         0x01
    2              0000 0010         0x02
    3              0000 0011         0x03
    4              0000 0100         0x04
    5              0000 0101         0x05
    6              0000 0110         0x06
    7              0000 0111         0x07
    8              0000 1000         0x08
    9              0000 1001         0x09
    10             0000 1010         0x0A
    11             0000 1011         0x0B
    12             0000 1100         0x0C
    13             0000 1101         0x0D
    14             0000 1110         0x0E
    15             0000 1111         0x0F
    ...            ...               ...
    127            0111 1111         0x7F
    128            1000 0000         0x80
    250            1111 1010         0xFA
    255            1111 1111         0xFF
*/


    int decimal = 250;       // 10 진수로 표현한 250
    int hexadecimal = 0xFA;  // 16 진수로 표현한 250
                             //    (2진수값 1111 1010 은 16진수로 압축해서 표현함)
    int octal = 0372;        //  8 진수로 표현한 250


    printf("decimal = %d, hexadecimal = %d, octal = %d\n",
        decimal, hexadecimal, octal);








/*
    비트 한 개에 대한 & 계산 예:
    =========================
    a     : 0    0    1    1
    b     : 0    1    0    1
    ------ ---  ---  ---  ---
    a & b : 0    0    0    1


    비트 8 개에 대한 & 계산 예:
    =========================
    a     : 0101 1111 (= 0x5F)
    b     : 0011 0000 (= 0x30)
    ------ -----------
    a & b : 0001 0000 (= 0x10)




    비트 한 개에 대한 | 계산 예:
    =========================
    a     : 0    0    1    1
    b     : 0    1    0    1
    ------ ---  ---  ---  ---
    a | b : 0    1    1    1


    비트 8 개에 대한 | 계산 예:
    =========================
    a     : 0101 1111 (= 0x5F)
    b     : 0011 0000 (= 0x30)
    ------ -----------
    a | b : 0111 1111 (= 0x7F)




    비트 한 개에 대한 ^ 계산 예:
    =========================
    a     : 0    0    1    1
    b     : 0    1    0    1
    ------ ---  ---  ---  ---
    a ^ b : 1    0    0    1


    비트 8 개에 대한 ^ 계산 예:
    =========================
    a     : 0101 1111 (= 0x5F)
    b     : 0011 0000 (= 0x30)
    ------ ----------
    a ^ b : 0110 1111 (= 0x6F)




    비트 8 개에 대한 << 계산 예:
    =========================
    a      : 0001 1010 (= 0x1A =  26)
    b      : 0000 0010 (= 0x02 =   2)
    ------- -----------
    a << b : 0110 10   <-- step 1: b 값은 십진수로 2임.
                                   그러므로 a 의 자이리동은 비트 두 자리임.
             0110 1000 <-- step 2: 이동 후 빈자리는 0 으로 채워짐.
                       (= 0x68 = 104)


    비트 8 개에 대한 >> 계산 예:
    =========================
    a      : 0001 1010 (= 0x1A =  26)
    b      : 0000 0010 (= 0x02 =   2)
    ------- -----------
    a >> b :   00 0110 <-- step 1: b 값은 십진수로 2임.
                                   그러므로 a 의 자이리동은 비트 두 자리임.
             0000 0110 <-- step 2: 이동 후 빈자리는 a 의 최상위 비트 값으로 채워짐.
                       (= 0x06 =   6)




    비트 8 개에 대한 ~ 계산 예:
    =========================
    a      : 0001 1010 (= 0x1A)
    ------- -----------
    ~a       1110 0101 (= 0xE5)  // a 값의 비트 부정값(= 1의 보수값)


    // 100 - 10 은 100 + (-10) 으로도 표현 가능
   
*/


    // masking example 1:
    // =================
    // char flag = 'a';   // 문자 'a' 는 2진수로 0110 0001
    // char mask = 0xDF;  // 0xDF 는 2진수로 1101 1111 임.
   
    // // 6번째 비트를 0 으로 만들어줌.
    // printf("마스킹 전 : flag = 문자 '%c', 16진수 0x%X, 10진수 %d\n", flag, flag, flag);
   
    // flag = flag & mask;  // flag 값을 마스킹함
    // printf("마스킹 후 : flag = 문자 '%c', 16진수 0x%X, 10진수 %d\n", flag, flag, flag);


    // masking example 2:
    // =================
    // char flag = 'a';   // 문자 'a' 는 2 진수로 0110 0001
    // char mask = 0x80;  // 0x80 는 2진수로 1000 0000
    // char result;


    // result = flag & mask;  // flag 값을 마스킹함
    // printf("flag = 16진수 0x%X\n", flag);
    // if(result == mask) {
    //     printf("flag 의 8번째 비트는 1 입니다\n");
    // }
    // else {
    //     printf("flag 의 8번째 비트는 0 입니다\n");
    // }


    // masking example 3:
    // =================
    // char flag = 'A';   // 문자 'A' 는 2 진수로 0100 0001
    // char mask = 0x20;  // 0x20 는 2진수로 0010 0000


    // printf("마스킹 전 : flag = 문자 '%c', 16진수 0x%X, 10진수 %d\n", flag, flag, flag);
    // flag = flag | mask;  // flag 값을 마스킹함
    // printf("마스킹 후 : flag = 문자 '%c', 16진수 0x%X, 10진수 %d\n", flag, flag, flag);






    // XOR 의 특성:
    //   ( original ^ mask ) ^ mask = original


    // masking example 4:
    // =================
    char original = 'Z';
    char mask = 0x75;  // 암호화 및 복호화용 키 값: 0x75 는 2진수로 0111 0101
    char encoded;
    char decoded;


    encoded = original ^ mask;  // 암호화
    decoded = encoded ^ mask;   // 복호화
    printf("인코딩 전 : original = '%c', 16진수 0x%X, 10진수 %d\n",
        original, original, original);
    printf("인코딩 후 : encoded  = '%c', 16진수 0x%X, 10진수 %d\n",
        encoded, encoded, encoded);
    printf("디코딩 후 : decoded  = '%c', 16진수 0x%X, 10진수 %d\n",
        decoded, decoded, decoded);




    // one's complement example:
    //   더하기로 빼기를 하는 코드:
    //   value - value = value + 2의 보수값 = 0
    // ========================
    int value = 100;
    int onesComplement = ~value; // 1의 보수
    int twosComplement = onesComplement + 1; // 2의 보수
   
    printf("value = %d\n", value);
    printf("1의 보수값 = %d\n", onesComplement);
    printf("2의 보수값 = %d\n", twosComplement);
    printf("value - value = %d\n", value - value);
    printf("value + 2의 보수값 = %d\n", value + twosComplement);


}
