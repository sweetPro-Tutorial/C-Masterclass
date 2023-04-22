// =====================================
// C 언어의 wide character 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main() {
    // how to print uni code
    setlocale(LC_CTYPE, "");  // 현재 로케일로 입출력에만 영향을 미침.
    wchar_t star = 0x2605;
    wprintf(L"%lc\n", star);
    wprintf(L"%lc\n", 0x2605);

    wchar_t spade = 0x2660;
    wchar_t diamond = 0x2662;
    wchar_t heart = 0x2661;
    wchar_t club = 0x2663;
    wprintf(L"Spade  : %lc\n", spade);
    wprintf(L"Diamond: %lc\n", diamond);
    wprintf(L"Heart  : %lc\n", heart);
    wprintf(L"Club   : %lc\n", club);

    wchar_t wstring_card[] = L"♠ ♢ ♡ ♣";
    wprintf(L"\u2660 \u2662 \u2661 \u2663\n");
    wprintf(L"%ls\n", wstring_card);

    wchar_t wstring_hangle[] = L".한글.";    
    wprintf(L"%ls\n", wstring_hangle);
}

/* 
실행예시: 리눅스(locale : ko_KR.UTF-8)
★
★
Spade  : ♠
Diamond: ♢
Heart  : ♡
Club   : ♣
♠ ♢ ♡ ♣
♠ ♢ ♡ ♣
.한글.

=====================================
실행예시: 윈도우 cmd(code page : 65001 = UTF-8)
★
★
Spade  : ♠
Diamond: ?   <<<--- cmd 터미널은 완벽히 유니코드를 출력하지 못함.
Heart  : ♡
Club   : ♣
♠ ? ♡ ♣
♠ ? ♡ ♣
.한글.
*/