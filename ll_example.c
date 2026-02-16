// ll_example.c
#include <stdio.h>
#include "ll.h" // เรียกใช้ไฟล์ header ที่เราสร้าง

int main(void) {
    LLPtr startPtr = NULL; // list เริ่มต้นเป็น empty
    unsigned int choice;   // ตัวเลือกเมนู
    int item;              // id ที่รับเข้ามา
    char name[50];         // name ที่รับเข้ามา

    instructions(); // แสดงเมนู

    printf("%s", "? ");
    scanf("%u", &choice);

    while (choice != 3) {
        switch (choice) {
            case 1:
                printf("%s", "Enter id and name: ");
                scanf("%d %s", &item, name);
                insert(&startPtr, item, name);
                
                // แสดงผลทั้งขาไปและขากลับ
                printList(startPtr);
                printReverse(startPtr);
                break;

            case 2:
                if (!isEmpty(startPtr)) {
                    printf("%s", "Enter number to be deleted: ");
                    scanf("%d", &item);

                    if (deletes(&startPtr, item)) {
                        printf("%d deleted.\n", item);
                        printList(startPtr);
                        printReverse(startPtr);
                    } else {
                        printf("%d not found.\n", item);
                    }
                } else {
                    puts("List is empty.");
                }
                break;

            default:
                puts("Invalid choice.\n");
                instructions();
                break;
        }

        printf("%s", "? ");
        scanf("%u", &choice);
    }

    // ล้างข้อมูลทั้งหมดก่อนจบโปรแกรม
    clearAll(&startPtr);
    puts("End of run.");

    return 0;
}