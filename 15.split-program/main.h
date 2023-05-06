#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "anomaly.h"
#include "encode.h"
#include "decode.h"

// operation 코드
#define ENCODE  'e'  // for encode
#define DECODE  'd'  // for decode
#define QUIT    'q'  // 옵션이나 입력파일에 이상 발생 시

char checkOption(int argc, char **argv);  // 옵션 검사

#endif
