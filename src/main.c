#include <stdio.h>
#include "linkedList.h"

    static unsigned int option = 0;
    static unsigned int flag;
    static char phoneNum[NAME_NUM_LEN];

    static void printWelcomeMessage();
    static void displayMainMenu();
    static unsigned int validInput();

void main() {
    printWelcomeMessage();
    do {
        // if (option != 0) puts("\nPress any key to display the main menu!");
        // fflush(stdin);
        // getchar();
        displayMainMenu();
        printf("\nYour choice?: ");
        fflush(stdin);
        scanf("%d", &option);
        switch(option) {
        case 1: Node *foundRecord = displayRecord(validInput());
                if (foundRecord == NULL) puts("Record doesn't exists!");
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
                validPhoneNum(&i, flag, phoneNum);
                (flag = deleteRecord(phoneNum) == 0) ? puts("Deletion was successful!")
                : (flag == 1) ? puts("Directory is empty!") : puts("Deletion failed, record doesn't exists!"); 
                break;
        case 0: puts("Have a good one!"); break;
        default: puts("Invalid option, please choose a valid option!"); break;
        }
    } while (option != 0);
}

static void printWelcomeMessage() {
    puts("*******************************************************************************************\n"
        "Welcome!\nThis is a program that uses a linkedlist to create a directory of phone numbers and names.\n"
        "Down below the main menu is diplayed where you can see which options you have.\n"
        "*******************************************************************************************");
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