#include <stdio.h>
#include "linkedList.h"

    static unsigned int option;
    static unsigned int flag;
    static char phoneNum[NAME_NUM_LEN];
    static void displayMainMenu();
    static unsigned int validInput();

void main() {
    do {
        displayMainMenu();
        printf("\nYour choice?: ");
        fflush(stdin);
        scanf("%d", &option);
        switch(option) {
        case 1: Node *foundRecord = displayRecord(validInput());
                (foundRecord == NULL) ? puts("Record doesn't exists!")
                : printf("\n%1d%15s%15s", foundRecord->recordNum, foundRecord->phoneNum, foundRecord->name);
        case 2: displayDirectory(); break;
        case 3: (flag = insertRecordBeg(createRecord()) == 0) 
                ? puts("Insertion was successful!") 
                : puts("Insertion failed, record already exists!");
                break;
        case 4: unsigned int i = 0;
                validPhoneNum(&i, flag, phoneNum);
                (flag = deleteRecord(phoneNum) == 0) 
                ? puts("Deletion was successful!")
                : puts("Deletion failed, record doesn't exists!"); 
                break;
        case 0: puts("Have a good one!"); break;
        default: puts("Invalid option, please choose a valid option!"); break;
        }
    } while (option != 0);
    fflush(stdin);
    getchar();
}

static void displayMainMenu() {
    puts("\n\n***** MAIN MENU *****"
        "\n1: Display record"
        "\n2: Display directory"
        "\n3: Add a new record at the beginning of the directory"
        "\n4: Delete a record"
        "\n0: Exit");
}

static unsigned int validInput() {
    unsigned int input = 2;
    while (input != 0 && input != 1) {
        puts("Enter \"1\" to search by phone number or \"0\" to search by name:");
        fflush(stdin);
        scanf("%d", &input);
    }
    return input;
}