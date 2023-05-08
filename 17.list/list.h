#ifndef _LIST_H_
#define _LIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct nodeStruct {
    char *data;
    struct nodeStruct *next;
};
typedef struct nodeStruct Node;

struct listStruct {
    Node *head;
    int size;
};
typedef struct listStruct LinkedList;


bool isEmpty(LinkedList *list);  // 리스트가 비어 있는지 확인
Node *makeNode(char *data);  // 노드 생성
void freeNode(Node *node);  // 노드에 할당된 메모리 제거
void pushFront(LinkedList *list, char *data);  // 리스트 맨 앞에 노드 추가
void popFront(LinkedList *list);  // 리스트 맨 앞 노드 삭제
void printNode(Node *node);  // 노드를 보여줌
void printList(LinkedList *list);  // 모든 노드를 보여줌
void eraseAllList(LinkedList *list);  // 리스트 내의 모든 노드를 삭제

void setHead(LinkedList *list, Node *node);  // head  설정
Node *getBeginNode(LinkedList *list);  // 리스트 맨 앞 노드를 찾아주는 함수


#endif  // _LIST_H_

