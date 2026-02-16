// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include "ll.h"
int main(void) {
    LLPtr startPtr = NULL; 
    unsigned int choice;   
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

   
    puts("Clear all nodes");
    LLPtr tempPtr;
    while (startPtr != NULL) {
        tempPtr = startPtr;
        printf("delete %d\n", startPtr->id); // แสดงตัวที่กำลังลบ
        startPtr = startPtr->nextPtr;
        free(tempPtr);
    }
    puts("End of run.");

    return 0;
}