// =====================================
// 한글을 각각의 자음과 모음으로 분리하는 코드용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

//
// note: 이 소스 코드는 UTF-8 포맷으로 저장해야 합니다.
//

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>


// 한글 초성
const wchar_t H_First[] = {
    L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ', L'ㄸ',
    L'ㄹ', L'ㅁ', L'ㅂ', L'ㅃ', L'ㅅ',
    L'ㅆ', L'ㅇ', L'ㅈ', L'ㅉ', L'ㅊ',
    L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ'
};
// 한글 중성
const wchar_t H_Middle[] = {
    L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ', L'ㅓ',
    L'ㅔ', L'ㅕ', L'ㅖ', L'ㅗ', L'ㅘ',
    L'ㅙ', L'ㅚ', L'ㅛ', L'ㅜ', L'ㅝ',
    L'ㅞ', L'ㅟ', L'ㅠ', L'ㅡ', L'ㅢ',
    L'ㅣ'
};
// 한글 종성
const wchar_t H_Last[] = {
    L' ', L'ㄱ', L'ㄲ', L'ㄳ', L'ㄴ',
    L'ㄵ', L'ㄶ', L'ㄷ', L'ㄹ', L'ㄺ',
    L'ㄻ', L'ㄼ', L'ㄽ', L'ㄾ', L'ㄿ',
    L'ㅀ', L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ',
    L'ㅆ', L'ㅇ', L'ㅈ', L'ㅊ', L'ㅋ',
    L'ㅌ', L'ㅍ', L'ㅎ'
};


// 유니코드 한글을 초성 중성 종성으로 분리
bool make_FML(wchar_t uniVal, int *first, int *middle, int *last);


int main(int argc, char **argv) {
    int first;
    int middle;
    int last;
    wchar_t text[] = L"김치가 맛있다.";
    wchar_t uniVal;
   
    setlocale(LC_ALL, "");

    for(int i = 0; text[i] != '\0'; i++) {
        uniVal = text[i];

        if(make_FML(uniVal, &first, &middle, &last)) {
            wprintf(L"%lc --> %lc%lc%lc\n",
                uniVal, H_First[first], H_Middle[middle], H_Last[last]);
        } else {
            wprintf(L"%lc --> %lc\n", uniVal, uniVal);
        }
    }

    return 0;
}

// 유니코드 한글을 초성 중성 종성으로 분리
bool make_FML(wchar_t uniVal, int *first, int *middle, int *last) {
    wchar_t temp;

    // 한글 여부 확인
    if (uniVal < 0xAC00 || uniVal > 0xD7AF) {
        return false;
    }

    // 자소 분리
    temp = uniVal - 0xAC00;
    *first  = temp / 28 / 21;  // 초성 분리
    *middle = temp / 28 % 21;  // 중성 분리
    *last   = temp % 28;       // 종성 분리

    return true;
}
