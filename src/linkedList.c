#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "linkedList.h"

static Node *start = NULL; // Global start node used to keep track of the starting record in the directory.
// This is a helper function to the function createRecord and it returns void.
// The function controls that the user inputs a valid format when inputting the phone number to the record.
// static void validPhoneNum(int *i, int flag, Node *newNode);
// void validPhoneNum(int *i, int flag, char *phoneNum);
// This is a helper function to the function createRecord and it returns void.
// The function controls that the user inputs a valid format when inputting the name to the record.
static void validName(int *j, int flag, char *name);
// This function searches the directory for the record with given phone number. 
// The function returns the pointer to the previous record if found, NULL if the found record is the first one and flag is changed to 1.
// The function also returns NULL if the directory is empty and flag is changed to 0.
static Node* searchDirectory(char phoneNum[NAME_NUM_LEN], int *flag);

Node* displayRecord(int flag) {
    unsigned int i = 0;
    char phoneNum[NAME_NUM_LEN];
    char name[NAME_NUM_LEN];
    // LOOPA DETTA OM USERN SKRIVER FEL.
    if(flag == 1) {
        validPhoneNum(&i, flag, phoneNum);
    }
    else
    {
        validName(&i, flag, name);
    }
    
}

void displayDirectory() { // Displays all records in the directory.
    Node *ptr = start;
    while(ptr != NULL) { // Prints all the records in the directory to the screen.
        printf("\n%1d%15s%15s", ptr->recordNum, ptr->phoneNum, ptr->name);
        ptr = ptr->next;
    }
    if (start == NULL) puts("Directory is empty!");
}

Node* createRecord() { // Creates a record containg phone number, name and ordinal number.
    Node *newNode = (Node*)malloc(sizeof(Node)); // Allocates memory on the heap for the record.
    if (newNode == NULL) { // Prints an error message and terminates the program if something went wrong when allocating memmory.
        puts("Failed to allocate memmory!");
        exit(-1);
    }
    for (int i = 0, j = 0, flag = 0; newNode->phoneNum[i] != '\0' || newNode->name[j] != '\0';) { // Loops as long as user inputs invalid strings.
        if (j == 0 && newNode->phoneNum[i] != '\0') validPhoneNum(&i, flag, newNode->phoneNum); // Checks if format of the string entered is valid.
        else validName(&j, flag, newNode->name); // Checks if format of the string entered is valid.
    }
    newNode->recordNum = 1; // New records will always be inserted as the first record in directory therefore recordNum = 1.
    return newNode;
}

// static void validPhoneNum(int *i, int flag, Node *newNode) { // Checks if format of the string entered is valid.
//     if (*i == 0) {
//         puts("Enter a phone number containing only digits:");
//         fflush(stdin);
//         fgets(newNode->phoneNum, NAME_NUM_LEN, stdin);
//         newNode->phoneNum[strlen(newNode->phoneNum)-1] = '\0'; // Removes '\n' character that was added by fgets.
//     }
//     flag = isdigit(newNode->phoneNum[*i]); // flag = 0 means entered phone number doesn't only contain digits as required to be valid.
//     *i+=1;
//     if (flag == 0) {
//         puts("Invalid input, please try again!\n");
//         *i = 0;
//     }
// }
void validPhoneNum(int *i, int flag, char *phoneNum) { // Checks if format of the string entered is valid.
    if (*i == 0) {
        puts("Enter a phone number containing only digits:");
        fflush(stdin);
        fgets(phoneNum, NAME_NUM_LEN, stdin);
        if (strlen(phoneNum) > 1) phoneNum[strlen(phoneNum)-1] = '\0'; // Removes '\n' character that was added by fgets.
    }
    flag = isdigit(phoneNum[*i]); // flag = 0 means entered phone number doesn't only contain digits as required to be valid.
    *i+=1;
    if (flag == 0) {
        puts("Invalid input, please try again!\n");
        *i = 0;
    }
}

static void validName(int *j, int flag, char *name) { // Checks if format of the string entered is valid.
    if (*j == 0) {
        puts("Enter a name containing only letters from the english alphabet:");
        fflush(stdin);
        fgets(name, NAME_NUM_LEN, stdin);
        if (strlen(name) > 1) name[strlen(name)-1] = '\0'; // Removes '\n' character that was added by fgets.
    }
    flag = isalpha(name[*j]); // flag = 0 means entered name doesn't only contain letters in the english alphabet as required to be valid.
    *j+=1;
    if (flag == 0) {
        puts("Invalid input, please try again!\n");
        *j = 0;
    }
}

int insertRecordBeg(Node *newNode) { // Inserts new record at the beginning of the directory.
    int flag = 0;
    Node *ptr = searchDirectory(newNode->phoneNum, &flag); // Searches the directory for record with given phone number. 
    if (flag == 1) return flag = -1; // If phone number already is in the directory insertion fails and flag is returned.
    if(start==NULL) { // If the directory is empty newNode becomes the start node and next node is NULL.
        newNode->next = NULL;
        start = newNode;
        return flag = 0; // Successful insertion flag = 0 is returned.
    }
    else { // Else newNode becomes the start and next node will be the old start node.
        newNode->next = start;
        ptr = start;
        start = newNode;
        while (ptr->next != NULL) { // All nodes succeding newNode have their recordNum incremented by 1.
            ptr->recordNum += 1;
            ptr = ptr->next;
        }
        if (ptr->next == NULL) ptr->recordNum += 1; // Needed this if statement to make sure the last node in the directory is incremented by 1.
        return flag = 0; // Successful insertion flag = 0 is returned.
    }
}


int deleteRecord(char phoneNum[NAME_NUM_LEN]) {
    int flag = 0;
    Node *prePtr = searchDirectory(phoneNum, &flag); 
    Node *ptr = start;
    if (flag == 0) return flag = -1;
    else if (prePtr == NULL) {
        start = ptr->next;
        free(ptr);
        ptr = start;
        if (ptr == NULL) return flag = 0;
        while (ptr->next != NULL) {
            ptr->recordNum -= 1;
            ptr = ptr->next;
        }
        if (ptr->next == NULL) ptr->recordNum -= 1;
    }
    else if ((flag = strcmp((ptr = prePtr->next)->phoneNum, phoneNum))== 0) {
        prePtr->next = ptr->next;
        free(ptr);
        while (prePtr->next != NULL) {
            prePtr = prePtr->next;
            prePtr->recordNum -= 1;
        }
    }
    return flag = 0;
}

static Node* searchDirectory(char phoneNum[NAME_NUM_LEN], int *flag) {
    Node *ptr = start, *prePtr = ptr;
    int i;
    if (ptr != NULL) {
        if ((i = strcmp(ptr->phoneNum, phoneNum)) == 0 && ptr->recordNum == 1) {
            *flag = 1;
            return prePtr = NULL;
        }
    }
    while (ptr != NULL) {
        if ((i = strcmp(ptr->phoneNum, phoneNum)) == 0) {
            *flag = 1;
            return prePtr;
        }
        prePtr = ptr;
        ptr = ptr->next;
    }
    return ptr;
}
Node* searchByNameOrNum(int flag) { 
   
}    