#ifndef _ANOMALY_H_
#define _ANOMALY_H_

#include <stdio.h>

#define SYNOPSYS    "옵션에 이상이 있습니다(invalid option)\n"                \
                    "--------------------------------------\n"                \
                    "Usage: morse <operation> inputfilename outputfilename\n" \
                    "\n"                                                      \
                    "    Operations:\n"                                       \
                    "    -e\n"                                                \
                    "        ASCII 문자를 모스 부호로 변환(인코딩)\n"         \
                    "    -d\n"                                                \
                    "        모스 부호를 ASCII 문자로 변환(디코딩)\n"

void anomalyReport();  // 이상 보고서: 옵션이나 입력파일의 문제 알림

#endif  // _ANOMALY_H_
