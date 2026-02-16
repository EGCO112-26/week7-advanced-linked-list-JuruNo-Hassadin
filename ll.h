
// self-referential structure
struct Node {
    int id;             // เปลี่ยน data เป็น id
    char name[50];      // เพิ่มตัวแปรเก็บชื่อ
    struct Node *nextPtr; // ชี้ไปตัวถัดไป
    struct Node *pPtr;    // ชี้ไปตัวก่อนหน้า (Previous Pointer)
};

typedef struct Node LLnode;
typedef LLnode *LLPtr;



// prototypes

void insert(LLPtr *sPtr, int value, char *n);
int deletes(LLPtr *sPtr, int value);
int isEmpty(LLPtr sPtr);
void printList(LLPtr currentPtr);
void printReverse(LLPtr currentPtr); // ฟังก์ชันใหม่สำหรับปริ้นย้อนกลับ
void instructions(void);





void instructions(void) {
    puts("Enter your choice:\n"
         "   1 to insert an element into the list.\n"
         "   2 to delete an element from the list.\n"
         "   3 to end.");
}

// 2. แก้ insert ให้จัดการ pointer 4 ทิศทาง
void insert(LLPtr *sPtr, int value, char *n) {
    LLPtr newPtr;
    LLPtr previousPtr;
    LLPtr currentPtr;

    newPtr = (LLPtr)malloc(sizeof(LLnode));

    if (newPtr != NULL) {
        newPtr->id = value;
        strcpy(newPtr->name, n); // copy string
        newPtr->nextPtr = NULL;
        newPtr->pPtr = NULL;

        previousPtr = NULL;
        currentPtr = *sPtr;

        // วนลูปหาตำแหน่งเรียงตาม id น้อยไปมาก
        while (currentPtr != NULL && value > currentPtr->id) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        // กรณีแทรกที่หัวแถว (Head)
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            if (*sPtr != NULL) {
                (*sPtr)->pPtr = newPtr; // ผูกขากลับของหัวเก่ามาหาตัวใหม่
            }
            *sPtr = newPtr;
        } 
        // กรณีแทรกระหว่างกลาง หรือ ท้ายแถว
        else {
            previousPtr->nextPtr = newPtr;
            newPtr->pPtr = previousPtr; // ผูกขากลับไปหาตัวก่อนหน้า

            newPtr->nextPtr = currentPtr;
            if (currentPtr != NULL) {
                currentPtr->pPtr = newPtr; // ผูกขากลับของตัวถัดไปมาหาตัวใหม่
            }
        }
    } else {
        printf("%d not inserted. No memory available.\n", value);
    }
}

// 3. แก้ delete ให้ตัด pointer ขาไปและขากลับ
int deletes(LLPtr *sPtr, int value) {
    LLPtr previousPtr;
    LLPtr currentPtr;
    LLPtr tempPtr;

    if (value == (*sPtr)->id) { // ลบตัวแรก
        tempPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr;
        
        if (*sPtr != NULL) {
            (*sPtr)->pPtr = NULL; // ตัดขากลับของหัวใหม่
        }
        
        free(tempPtr);
        return 1; // สำเร็จ
    } else {
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;

        while (currentPtr != NULL && currentPtr->id != value) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (currentPtr != NULL) { // เจอตัวที่จะลบ
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr; // ข้ามตัวที่จะลบ (ขาไป)
            
            if (currentPtr->nextPtr != NULL) {
                currentPtr->nextPtr->pPtr = previousPtr; // ข้ามตัวที่จะลบ (ขากลับ)
            }
            
            free(tempPtr);
            return 1; // สำเร็จ
        }
    }
    return 0; // ไม่เจอ
}

int isEmpty(LLPtr sPtr) {
    return sPtr == NULL;
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

// แสดงผลขากลับ (Backward)
void printReverse(LLPtr currentPtr) {
    if (isEmpty(currentPtr)) {
        return; // ว่างก็ไม่ต้องทำอะไร (ข้อความแสดงใน printList แล้ว)
    }

    // 1. วิ่งไปให้สุดแถวก่อน
    while (currentPtr->nextPtr != NULL) {
        currentPtr = currentPtr->nextPtr;
    }

    // 2. วิ่งย้อนกลับมาหัวแถวโดยใช้ pPtr
    while (currentPtr != NULL) {
        printf("%d %s --> ", currentPtr->id, currentPtr->name);
        currentPtr = currentPtr->pPtr;
    }
    puts("NULL");
}
