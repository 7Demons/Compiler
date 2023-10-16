#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

/** TODO:
 * * many function assume data is not NULL. should be fine.
 * * free function.
 * 
 * 
*/

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

BOOL pop(DynamicArray *pArray) {
    if (pArray == NULL) {
        return FALSE;
    }
    if (pArray->data == NULL) {
        return FALSE;
    }
    if (pArray->size <= 0) {
        return FALSE;
    }
    //void *deleteAddress = (char *)pArray->data + (pArray->elementSize * pArray->size);
    //free(deleteAddress);
    pArray->size--;
    
    if (pArray->size < pArray->maxCapacity / 2) {
        int newNoElem = pArray->maxCapacity/2;
        int newSizeBytes = newNoElem * pArray->elementSize;
        void *temp = (void *)realloc(pArray->data, newSizeBytes);
        if (temp == NULL) {
            printf("Error: Reallocation failure!");
            return FALSE;
        }
        pArray->data = temp;
        pArray->maxCapacity = newNoElem;
    }

    return TRUE;
}

BOOL swap(DynamicArray *pArray, int indexP, int indexQ) {
    if (pArray == NULL) {
        return FALSE;
    }
    if (pArray->data == NULL) {
        return FALSE;
    }
    if (indexP < 0 || indexQ < 0) {
        return FALSE;
    }
    if (pArray->size < indexP || pArray->size < indexQ) {
        return FALSE;
    }

    void *temp = malloc(pArray->elementSize);
    if (temp == NULL) {
        return FALSE;
    }

    void *pIndexP = (char*)pArray->data + (pArray->elementSize * indexP);
    void *pIndexQ = (char*)pArray->data + (pArray->elementSize * indexQ);
    memcpy(temp, pIndexP, pArray->elementSize);
    memcpy(pIndexP, pIndexQ, pArray->elementSize);
    memcpy(pIndexQ, temp, pArray->elementSize);
    free(temp);
}

void *get(DynamicArray *pArray, int index) {
    if (pArray == NULL) {
        return NULL;
    }
    if (pArray->size < index) {
        return NULL;
    }
    void *address = (char *)pArray->data + (pArray->elementSize * index);
    return address;
}

void debugArray(DynamicArray *pArray) {
    // int *pData = pArray->data;
    // for (int i = 0; i < pArray->size; i++) {
    //     printf("%d\n", *pData);
    //     pData++;
    // }

    for (int i = 0; i < pArray->size; i++) {
        int *val = get(pArray, i);
        if (val == NULL) {
            break;
        }
        printf("[index %d]: %d\n", i, *val);
        
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

    for (int i = 0; i < 3; i++) {
        push(test, &x);
        push(test, &y);
        push(test, &z);
    }

    debugArray(test);

    printf("\n\n");
    pop(test);
    pop(test);
    pop(test);
    pop(test);
    pop(test);
    pop(test);
    pop(test);
    debugArray(test);

    printf("\n\n");
    swap(test, 0, 1);
    debugArray(test);

    printf("%d \n", test->maxCapacity);
    const int a; 
    scanf("%d", &a);
   
}

// c        197.4 MB
// python   394.1 MB