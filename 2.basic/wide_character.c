
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main() {
    // how to print uni code
    setlocale(LC_CTYPE, "");  // 현재 로케일로 입출력에만 영향을 미침.
    wchar_t star = 0x2605;
    wprintf(L"%lc\n", star);
    wprintf(L"\u2660 \u2661 \u2662 \u2663\n");
}

/* 
실행예시:

★
♠ ♡ ? ♣
*/