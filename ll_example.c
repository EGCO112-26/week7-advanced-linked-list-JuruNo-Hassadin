/* ll_example.c */
#include <stdio.h>
#include "ll.h" // เรียกใช้ไฟล์ Header ที่เราสร้างไว้

int main(void) {
    LLPtr startPtr = NULL; // เริ่มต้นเป็น NULL
    unsigned int choice;
    int item;
    char name[50];

    instructions(); // แสดงเมนู

    printf("%s", "? ");
    scanf("%u", &choice);

    while (choice != 3) {
        switch (choice) {
            case 1:
                printf("%s", "Enter id and name: ");
                scanf("%d %s", &item, name);
                insert(&startPtr, item, name);
                
                // แสดงผลตามโจทย์ (ทั้งไปและกลับ)
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