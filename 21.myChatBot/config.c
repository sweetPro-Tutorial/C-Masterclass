#include "config.h"

int keyHandler(void *config, String name, String value) {
    Config *thisConfig = (Config *)config;
    if(match("question_json_pathname", name)) { 
        strcpy(thisConfig->question_json_pathname, value); 
    } else if(match("response_json_pathname", name)) { 
        strcpy(thisConfig->response_json_pathname, value); 
    } else { return FAIL; }

    return SUCCESS;
}

void printConfig(Config *config) {
    printf( "Config=[question_json_pathname=%s,response_json_pathname=%s]\n",
        config->question_json_pathname, config->response_json_pathname);
}