#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct DynamicArray {
    void *data;
    int elementSize;
    int size;
    int maxCapacity;
} DynamicArray;

/**
 * Returns a pointer to a DynamicArray with an initial capacity of 16.
 * elementSize : The size of elements in this array.
 * returns : A pointer to DynamicArray upon successful creation or NULL upon
 * failure. 
*/
DynamicArray *createDynamicArray(int elementSize) {
    int INITIAL_CAPACITY = 4;
    
    if (elementSize < 0) {
        printf("Error: Cannot have dynamic array with negative element size.");
        exit(EXIT_FAILURE);
    }

    DynamicArray *pNewArray = malloc(sizeof(DynamicArray));
    if (pNewArray == NULL) {
        printf("Error: failed to allocate dynamic array.");
        return NULL;
    }
    
    pNewArray->data = malloc(elementSize*INITIAL_CAPACITY);
    if (pNewArray->data == NULL) {
        printf("Error: failed to allocate array data.");
        return NULL;
    }

    pNewArray->elementSize = elementSize;
    pNewArray->size = 0;
    pNewArray->maxCapacity = INITIAL_CAPACITY;
    return pNewArray;
}

BOOL push(DynamicArray *pArray, void *value) {
    if (pArray == NULL) {
        return FALSE;
    }

    if (pArray->maxCapacity <= pArray->size) {
        int newNoElem = pArray->maxCapacity * 2 + 1;
        int newSizeBytes = newNoElem * pArray->elementSize;
        void *temp = (void *)realloc(pArray->data, newSizeBytes);
        if (temp == NULL) {
            printf("Error: Reallocation failure!");
            return FALSE;
        }
        pArray->data = temp;
        pArray->maxCapacity = newNoElem;
    }

    void *insertLocation = (char*)pArray->data + (pArray->elementSize * pArray->size);
    memcpy(insertLocation, value, pArray->elementSize);
    pArray->size++;
    return TRUE;
}

void debugArray(DynamicArray *pArray) {
    int *pData = pArray->data;
    for (int i = 0; i < pArray->size; i++) {
        printf("%d\n", *pData);
        pData++;
    }

}

int main() {
    printf("size of void pointer: %d \n", sizeof(void*));
    printf("size of char: %d \n", sizeof(int));

    printf("test\n");
    DynamicArray *test = createDynamicArray(sizeof(int));
    int x = 55555;
    int y = 7;
    int z = 4;
    push(test, &x);
    push(test, &y);
    push(test, &z);


    for (int i = 0; i < 80000000; i++) {
        push(test, &x);
        push(test, &y);
    }

    //debugArray(test);
    printf("%d \n", test->maxCapacity);
    const int a; 
    scanf("%d", &a);
   
}

// c        197.4 MB
// python   394.1 MB