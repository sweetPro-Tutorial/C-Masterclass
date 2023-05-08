#include "list.h"


// isEmpty      : 리스트가 비어 있는지 확인
bool isEmpty(LinkedList *list) {
    return (getBeginNode(list) == NULL);
}

// makeNode     : 노드 생성
Node *makeNode(char *data) {
    int dataSize = strlen(data) + 1;

    Node *newNode = (Node *)malloc(sizeof(Node));  // Node용: 메모리 할당
    newNode->data = (char *)malloc(dataSize);      // data용: 메모리 할당
    memcpy(newNode->data, data, dataSize);         // data 초기화
    newNode->next = NULL;                          // next 초기화

    return newNode;
}

// freeNode     : 노드에 할당된 메모리 제거
void freeNode(Node *node) {
    if(node == NULL) { return; }

    free(node->data);  // data용 메모리 해제
    free(node);        // node용 메모리 해제
}

// setHead : head  설정
void setHead(LinkedList *list, Node *node) {
    list->head = node;
}
// getBeginNode: 리스트 맨 앞 노드를 찾아주는 함수
Node *getBeginNode(LinkedList *list) {
    return list->head;
}

// pushFront    : 리스트 맨 앞에 노드 추가
void pushFront(LinkedList *list, char *data) {
    // 1) 새 노드 생성
    Node *newNode = makeNode(data);
    // 2) 새 노드의 next 링크는 맨 앞 노드를 가리키게 함
    newNode->next = getBeginNode(list);
    // 3) head 는 새 노드를 가리키게 함
    setHead(list, newNode);
    // 4) size 증가
    list->size++;
}

// popFront     : 리스트 맨 앞 노드 삭제
void popFront(LinkedList *list) {
    // 만약 리스트가 텅 비었으면 삭제할 수 없음
    if(isEmpty(list)) { return; }

    // head 는 next 노드를 가리키게 함
    Node *temp = getBeginNode(list);
    setHead(list, getBeginNode(list)->next);
    // head 가 가리키던 노드는 삭제
    freeNode(temp);
    // size 감소
    list->size--;
}

// printNode    : 노드를 보여줌
void printNode(Node *node) {
    if(node == NULL) {
        printf("(NULL)\n");
        return;
    }
    if(node->next == NULL) {
        printf("(data:%s,next:NULL)\n", node->data);
        return;
    }
    printf("(data:%s,next:%p)\n", node->data, node->next);
}

// printList    : 모든 노드를 보여줌
void printList(LinkedList *list) {
    printf(">>> list up\n");
    // 맨 앞 노드부터 시작해서
    Node *tempNode = getBeginNode(list);
    // 링크를 끝까지 쭉 따라가면서
    while(tempNode != NULL) {
        // 노드를 하나씩 출력합니다.
        printNode(tempNode);
        tempNode = tempNode->next;
    }
}


// eraseAllList : 리스트 내의 모든 노드를 삭제
void eraseAllList(LinkedList *list) {
    while(!isEmpty(list)) {
        popFront(list);
    }
}

