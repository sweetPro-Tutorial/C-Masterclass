#include "list.h"


int main() {
    LinkedList list = { NULL, 0 };

    // add test
    pushFront(&list, "D");
    pushFront(&list, "C");
    pushFront(&list, "B");
    printList(&list);
    printf("size=%d\n", list.size);

    pushFront(&list, "A");
    printList(&list);
    printf("size=%d\n", list.size);

    // delete node test
    popFront(&list);
    popFront(&list);
    printList(&list);
    printf("size=%d\n", list.size);

    // delete list test
    eraseAllList(&list);
    printList(&list);
    printf("size=%d\n", list.size);

    pushFront(&list, "1st data");
    pushFront(&list, "2nd data");
    pushFront(&list, "3rd data");
    pushFront(&list, "4th data");
    printList(&list);
    printf("size=%d\n", list.size);

    // add after test
    pushBack(&list, "0th data");
    pushBack(&list, "-1th data");
    printList(&list);
    printf("size=%d\n", list.size);

    // delete from behind test
    popBack(&list);
    popBack(&list);
    printList(&list);
    printf("size=%d\n", list.size);

    // popBack(&list);
    // popBack(&list);
    // popBack(&list);
    // popBack(&list);
    // printList(&list);
    // printf("size=%d\n", list.size);

}
