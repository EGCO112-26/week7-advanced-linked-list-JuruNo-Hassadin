// ll.h
#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------------------
// 1. สร้าง Structure และ Typedef
// ------------------------------------------
struct Node {
    int id;               
    char name[50];        
    struct Node *nextPtr; // ขาไป
    struct Node *pPtr;    // ขากลับ (Previous)
};

typedef struct Node LLnode;
typedef LLnode *LLPtr;

// ------------------------------------------
// 2. สร้างฟังก์ชัน (Implementation)
// ------------------------------------------

// เช็คว่าลิสต์ว่างหรือไม่
int isEmpty(LLPtr sPtr) {
    return sPtr == NULL;
}

// แสดงเมนูคำสั่ง
void instructions(void) {
    puts("Enter your choice:\n"
         "   1 to insert an element into the list.\n"
         "   2 to delete an element from the list.\n"
         "   3 to end.");
}

// แทรกข้อมูล (Insert)
void insert(LLPtr *sPtr, int value, char *n) {
    LLPtr newPtr;
    LLPtr previousPtr;
    LLPtr currentPtr;

    newPtr = (LLPtr)malloc(sizeof(LLnode));

    if (newPtr != NULL) {
        newPtr->id = value;
        strcpy(newPtr->name, n);
        newPtr->nextPtr = NULL;
        newPtr->pPtr = NULL;

        previousPtr = NULL;
        currentPtr = *sPtr;

        // วนหาตำแหน่งที่เหมาะสม (เรียงจากน้อยไปมาก)
        while (currentPtr != NULL && value > currentPtr->id) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        // กรณีแทรกที่หัวแถว (Head)
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            if (*sPtr != NULL) {
                (*sPtr)->pPtr = newPtr; // ผูกขากลับ
            }
            *sPtr = newPtr;
        } 
        // กรณีแทรกระหว่างกลาง หรือ ท้ายแถว
        else {
            previousPtr->nextPtr = newPtr;
            newPtr->pPtr = previousPtr; // ผูกขากลับ

            newPtr->nextPtr = currentPtr;
            if (currentPtr != NULL) {
                currentPtr->pPtr = newPtr; // ผูกขากลับตัวถัดไป
            }
        }
    } else {
        printf("%d not inserted. No memory available.\n", value);
    }
}

// ลบข้อมูล (Delete)
int deletes(LLPtr *sPtr, int value) {
    LLPtr previousPtr;
    LLPtr currentPtr;
    LLPtr tempPtr;

    // ลบตัวแรก (Head)
    if (value == (*sPtr)->id) {
        tempPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr;
        
        if (*sPtr != NULL) {
            (*sPtr)->pPtr = NULL; // ตัดขากลับ
        }
        
        free(tempPtr);
        return 1;
    } 
    // ลบตัวอื่น
    else {
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;

        while (currentPtr != NULL && currentPtr->id != value) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (currentPtr != NULL) { // เจอตัวที่จะลบ
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr; // ข้ามตัวที่จะลบ
            
            if (currentPtr->nextPtr != NULL) {
                currentPtr->nextPtr->pPtr = previousPtr; // เชื่อมขากลับข้ามตัวที่ลบ
            }
            
            free(tempPtr);
            return 1;
        }
    }
    return 0;
}

// แสดงผลขาไป (Forward)
void printList(LLPtr currentPtr) {
    puts("The list is:");
    if (isEmpty(currentPtr)) {
        puts("List is empty.");
    } else {
        while (currentPtr != NULL) {
            printf("%d %s --> ", currentPtr->id, currentPtr->name);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL");
    }
}

// แสดงผลขากลับ (Reverse)
void printReverse(LLPtr currentPtr) {
    if (isEmpty(currentPtr)) return;

    // วิ่งไปท้ายสุดก่อน
    while (currentPtr->nextPtr != NULL) {
        currentPtr = currentPtr->nextPtr;
    }

    // วิ่งย้อนกลับ
    while (currentPtr != NULL) {
        printf("%d %s --> ", currentPtr->id, currentPtr->name);
        currentPtr = currentPtr->pPtr;
    }
    puts("NULL");
}

// ล้างข้อมูลทั้งหมด (Clear All)
void clearAll(LLPtr *sPtr) {
    puts("Clear all nodes");
    LLPtr tempPtr;
    while (*sPtr != NULL) {
        tempPtr = *sPtr;
        printf("delete %d\n", (*sPtr)->id);
        *sPtr = (*sPtr)->nextPtr;
        free(tempPtr);
    }
}

#endif