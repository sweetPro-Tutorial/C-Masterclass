#include "common.h"

static StringLong tempString;

char *getMasterFilename(String dataTime) {
    memset(tempString, 0x00, LINE_SIZE);
    sprintf(tempString, "%.10s.csv", dataTime);
    return tempString;
}

char *getMasterFilename_X(String dataTime) {
    static StringLong tempString;

    memset(tempString, 0x00, LINE_SIZE);
    sprintf(tempString, "%.10s.csv", dataTime);
    return tempString;
}

char *getMasterFilename_O(char *result, int size, String dataTime) {
    memset(result, 0x00, size);
    sprintf(result, "%.10s.csv", dataTime);
    return result;
}

char *getTimeString(DateFormat kind) {
    time_t temp;
    struct tm *timePointer;

    memset(tempString, 0x00, LINE_SIZE);
    time(&temp);
    timePointer = localtime(&temp);
    switch(kind) {
    case YYYYMMDD:  // eg) "2023-01-31"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d", timePointer);
        break;
    case YYYYMMDD_HH:  // eg) "2023-01-31 09"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d %H", timePointer);
        break;
    case YYYYMMDD_HHmmSS:  // eg) "2023-01-31 09:55:01"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d %H:%M:%S", timePointer);
        break;
    default:  // eg) "2023-01-31 09:55:01"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d %H:%M:%S", timePointer);
        break;
    }

    return tempString;
}

char *getTimeString_X(DateFormat kind) {
    static StringLong tempString;
    time_t temp;
    struct tm *timePointer;

    memset(tempString, 0x00, LINE_SIZE);
    time(&temp);
    timePointer = localtime(&temp);
    switch(kind) {
    case YYYYMMDD:  // eg) "2023-01-31"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d", timePointer);
        break;
    case YYYYMMDD_HH:  // eg) "2023-01-31 09"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d %H", timePointer);
        break;
    case YYYYMMDD_HHmmSS:  // eg) "2023-01-31 09:55:01"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d %H:%M:%S", timePointer);
        break;
    default:  // eg) "2023-01-31 09:55:01"
        strftime(tempString, sizeof(tempString), "%Y-%m-%d %H:%M:%S", timePointer);
        break;
    }

    return tempString;
}

char *getTimeString_O(char *result, int size, DateFormat kind) {
    time_t temp;
    struct tm *timePointer;

    memset(result, 0x00, size);
    time(&temp);
    timePointer = localtime(&temp);
    switch(kind) {
    case YYYYMMDD:  // eg) "2023-01-31"
        strftime(result, size, "%Y-%m-%d", timePointer);
        break;
    case YYYYMMDD_HH:  // eg) "2023-01-31 09"
        strftime(result, size, "%Y-%m-%d %H", timePointer);
        break;
    case YYYYMMDD_HHmmSS:  // eg) "2023-01-31 09:55:01"
        strftime(result, size, "%Y-%m-%d %H:%M:%S", timePointer);
        break;
    default:  // eg) "2023-01-31 09:55:01"
        strftime(result, size, "%Y-%m-%d %H:%M:%S", timePointer);
        break;
    }

    return result;
}
