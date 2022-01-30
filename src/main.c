#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "linkedList.h"

    static unsigned int option;
    static unsigned int flag;
    static char phoneNum[NAME_NUM_LEN];

void main() {
    do {
        puts("\n\n***** MAIN MENU *****"
            "\n1: Display record"
            "\n2: Display directory"
            "\n3: Add a new record at the beginning of the directory"
            "\n4: Delete a record"
            "\n0: Exit");
        printf("\nYour choice?: ");
        fflush(stdin);
        scanf("%d", &option);
    switch(option) {
            case 1: do {
                        puts("Enter \"1\" to search by phone number or \"0\" to search by name:");
                        fflush(stdin);
                        scanf("%d", flag);
                        Node *foundRecord = displayRecord(flag);
                        (foundRecord == NULL) ? puts("Record doesn't exists!")
                        : printf("\n%1d%15s%15s", foundRecord->recordNum, foundRecord->phoneNum, foundRecord->name);
                    } while (flag != 0 || flag != 1);
            case 2: displayDirectory(); break;
            case 3: (flag = insertRecordBeg(createRecord()) == 0) 
                    ? puts("Insertion was successful!") 
                    : puts("Insertion failed, record already exists!");
                    break;
            case 4: // FUNKAR NÄSTAN KOLLA PÅ DETTA IGEN HADE VART GRYMT OM DET FUNKA HELT MEN BEHÖVS NOG EN DEBUGG.
                    int i;
                    validPhoneNum(&i, flag, phoneNum);
                    (flag = deleteRecord(phoneNum) == 0) 
                    ? puts("Deletion was successful!")
                    : puts("Deletion failed, record doesn't exists!"); 
                    break;
            case 0: puts("Have a good one!"); break;
            default: puts("Invalid option, please choose a valid option!"); break;
            // case 1: createDirectory(&start); puts("Directory created"); break;
            // case 1: Node *start = createDirectory(); puts("Directory created"); break;
        }
    } while (option != 0);
    fflush(stdin);
    getchar();
}


// static char phoneNum[NAME_NUM_LEN] validPhoneNum() { 
//     unsigned int i = 0;
//                     do {
//                         if (i == 0) {
//                             puts("Please enter phone number belonging to the record you want to delete: ");
//                             fflush(stdin);
//                             fgets(phoneNum, NAME_NUM_LEN, stdin);
//                             phoneNum[strlen(phoneNum)-1] = '\0'; // Removes '\n' character that was added by fgets.
//                         }
//                         flag = isdigit(phoneNum[i]);
//                         i++;
//                         if (flag == 0) {
//                             puts("Invalid input, please try again!\n");
//                             i = 0;
//                         }
//                     } while (phoneNum[i] != '\0');
// }