#!/usr/bin/sh

curl   https://api.openai.com/v1/chat/completions  \
-H "Content-Type: application/json"  \
-H "Authorization: Bearer $OPENAI_API_KEY"  \
-d "$(cat $1)" > $2
