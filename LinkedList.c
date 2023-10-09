#ifndef LINKEDLIST_C
#define LINKEDLIST_C

#include <stdio.h>
#include <stdlib.h>

#define boolean int
#define TRUE 1
#define FALSE 0

// TODO: 
/*
Memory Management:should also implement a function to free the memory for the entire list and its nodes.
*/
typedef struct DLLNode {
    void *value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DLL {
    Node *first;
    Node *last;
    int size;
} List;

/** 
 * Create a new node for a linked list
 * value : value associated with this node.
*/
Node *newNode(void* value) {
    Node *pNew = (Node*)malloc(sizeof(Node));
    if (pNew == NULL) {
        return NULL;
    }
    pNew->value = value;
    return pNew;
}

/** 
 * Create a node using provided value and then add this node to front of the linked list. 
 * list : list to add the new node to.
 * value : value associated with node.
*/
boolean addFirst(List *list, void *value) {
    // list is null cannot add stuff.
    if (list == NULL) {
        return FALSE;
    }

    // failed allocation of new node
    Node *pNewNode = newNode(value);
    if (pNewNode == NULL) {
        return FALSE;
    }

    pNewNode->prev = NULL;
    // list is empty
    if (list->first == NULL) {
        pNewNode->next = NULL;
        list->first = pNewNode;
        list->last = list->first;
        list->size = 1;
        return TRUE;
    }

    (Node *)pNewNode->next = list->first;
    (Node *)list->first->prev = pNewNode;
    list->first = pNewNode;
    list->size++;
    // list is not empty
    return TRUE;
}

/** 
 * Create a node using provided value and then add this node to end of the linked list. 
 * list : list to add the new node to.
 * value : value associated with node.
*/
boolean addLast(List *list, void *value) {
    if (list == NULL) {
        return FALSE;
    }

    if (list->last == NULL) {
        return addFirst(list, value);
    }

    Node *pNewNode = newNode(value);
    if (pNewNode == NULL) {
        return FALSE;
    }

    (Node *)pNewNode->prev = list->last;
    (Node *)list->last->next = pNewNode;
    list->last = pNewNode;
    list->size++;
    return TRUE;
}

/** Create a node using provided value and then add this node to the corresponding position
 * Note: if index == listSize it will be added last. index out of range will return false. 
 * Note: if index == 0 it will be added to list head.
 * list : pointer to list struct
 * value : value to add.
 * index : The position in list to add to.
*/
boolean add(List *list, void *value, int index) {
    // list doesnt exist
    if (list == NULL) {
        return FALSE;
    }

    // list is empty
    if (index == 0 || list->size == 0) {
        return addFirst(list, value);
    }

    if (index == list->size) {
        return addLast(list, value);
    }

    // index out of range
    if (index < 0 || list->size < index) {
        return FALSE;
    }

    Node *pNewNode = newNode(value);
    if (pNewNode == FALSE) {
        return FALSE;
    }

    int i = 0;
    Node *tracer = list->first;
    while(tracer->next != NULL && i != index) {
        tracer = (Node *)tracer->next;
        i++;
    }

    Node *prevNode = (Node *)tracer->prev;

    (Node *)prevNode->next = pNewNode;
    (Node *)pNewNode->next = tracer;
    if (tracer != NULL) {
        (Node *)tracer->prev = pNewNode;
    }
    (Node *)pNewNode->prev = prevNode;
    list->size++;

    return TRUE;
}

// DEBUGING
void printList(List *list) {
    if (list == NULL) {
        return;
    }

    Node *tracer = list->first;
    int i = 0;
    while(i < list->size) {
        int *pValue = tracer->value;
        int value = *pValue;
        printf("%d \n", value);
        tracer = (Node *)tracer->next;
        i++;
    }
    printf("\n");

}

void deleteList(List *list) {
    Node *tracer = list->first;
    while (tracer != NULL) {
        Node *temp = tracer;
        tracer = (Node *)tracer->next;
        free(temp);
    }
    free(list);
}

int main() {
    printf("Hello world\n");
    int a = 71;
    int *pa = &a;

    int b = 55;
    int *pb = &b;

    int xx = 1111;
    int *pxx = &xx;

    List testList;
    testList.first = NULL;
    testList.last = NULL;
    List *pTestList = &testList;

    // 55, 71, 71 71, 71

    addFirst(pTestList, pb);
    addLast(pTestList, pa);
    addLast(pTestList, pa);
    addLast(pTestList, pa);
    addLast(pTestList, pa);
    printList(pTestList);
    add(pTestList, pxx, 5);
    printf("\n");

    printList(pTestList);
    Node *pFirstNode = testList.first;
    Node firstNode = *pFirstNode;
    Node *pSecondNode = (Node *)firstNode.next;
    Node secondNode = *pSecondNode;
    int *secondNodeValue = secondNode.value;
    int *pC = secondNodeValue;
    int c = *pC;
    
    printf(" test: %d", c);
    return 0;
}

#endif