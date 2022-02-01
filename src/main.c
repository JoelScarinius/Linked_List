#include <stdio.h>
#include "linkedList.h"

    static unsigned int option = 0;
    static unsigned int flag = 2;
    static char nameOrPhoneNum[NAME_NUM_LEN];

    static void printWelcomeMessage();
    static void displayMainMenu();
    static void validInput(int *flag);

void main() {
    printWelcomeMessage();
    do {
        displayMainMenu();
        printf("\nYour choice?: ");
        fflush(stdin);
        scanf("%d", &option);
        switch(option) {
        case 1: validInput(&flag);
                Node *foundRecord = displayRecord(&flag, nameOrPhoneNum);
                if (foundRecord == NULL) puts("Record doesn't exists or directory is empty!");
                else {
                    printHeader();
                    printf("\n%-20d%-20s%-20s", foundRecord->ordinalNum, foundRecord->phoneNum, foundRecord->name);
                }
                break;
        case 2: displayDirectory(); break;
        case 3: (flag = insertRecordBeg(createRecord()) == 0) 
                ? puts("Insertion was successful!") 
                : puts("Insertion failed, record already exists!");
                break;
        case 4: unsigned int i = 0;
                validPhoneNum(&i, flag, nameOrPhoneNum);
                ((flag = deleteRecord(nameOrPhoneNum)) == 0) ? puts("Deletion was successful!")
                : ((flag == 1) ? puts("Deletion failed, directory is empty!") : puts("Deletion failed, record doesn't exists!")); 
                break;
        case 0: puts("Have a good one!"); break;
        default: puts("Invalid option, please choose a valid option!"); break;
        }
    } while (option != 0);
}

static void printWelcomeMessage() {
    puts("******************************************************************************************\n"
        "Welcome!\nThis is a program that uses a linkedlist to create a directory of phone numbers and names.\n"
        "Down below the main menu is diplayed where you can see which options you have.\nPlease enjoy!\n"
        "******************************************************************************************");
}

static void displayMainMenu() {
    puts("\n\n***** MAIN MENU *****"
        "\n1: Display record"
        "\n2: Display directory"
        "\n3: Add a new record at the beginning of the directory"
        "\n4: Delete a record"
        "\n0: Exit");
}

static void validInput(int *flag) {
    do {
        printf("\nEnter \"1\" to search by phone number or \"0\" to search by name: ");
        fflush(stdin);
        scanf("%d", &*flag);
    } while (*flag != 0 && *flag != 1);
}