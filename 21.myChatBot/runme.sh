#!/usr/bin/sh

curl   https://api.openai.com/v1/chat/completions  \
-H "Content-Type: application/json"  \
-H "Authorization: Bearer $OPENAI_API_KEY"  \
-d "$(cat ~/cprojects/21.myChatBot/myquestion.json)" > ~/cprojects/21.myChatBot/response.json

# curl   https://api.openai.com/v1/chat/completions -H "Content-Type: application/json" -H "Authorization: Bearer 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" -d "$(cat ~/cprojects/21.myChatBot/myquestion.json)"  >  ~/cprojects/21.myChatBot/response.json
