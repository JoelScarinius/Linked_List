#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "linkedList.h"

static Node *start = NULL; // Global start node used to keep track of the starting record in the directory.

// This function searches the directory for the record with given phone number or name. 
// The function returns the pointer to the previous record if found, NULL if the found record is the first one and flag is changed to 1.
// The function also returns NULL if the directory is empty and flag is changed to 0.
static Node* searchDirectory(char nameOrPhoneNum[NAME_NUM_LEN], int *flag);
// This function returns true or false depending on if the directory is empty or not.
static bool emptyDirectory();

Node* displayRecord(int *flag, char nameOrPhoneNum[NAME_NUM_LEN]) {
    if (emptyDirectory()) return NULL; // If directory is empty return NULL.
    Node *foundRecord = searchDirectory(nameOrPhoneNum, flag);
    // If foundRecord is NULL and the first record in the directory is the record searched for return it else record doesn't exists return NULL.
    if (foundRecord == NULL) { 
        if ((strcmp(start->name, nameOrPhoneNum)) != 0 && (strcmp(start->phoneNum, nameOrPhoneNum)) != 0) return NULL;
        else return start;
    }
    else { // Else if record doesn't exists return NULL else the record searched for is the next record in the list return that record.
        if ((strcmp((foundRecord->next)->name, nameOrPhoneNum)) != 0 && (strcmp((foundRecord->next)->phoneNum, nameOrPhoneNum)) != 0) return NULL;
        else return foundRecord->next;
    }
}

void displayDirectory() { // Displays all records in the directory.
    if (emptyDirectory()) puts("Directory is empty!"); // If directory is empty display that to the screen.
    Node *ptr = start;
    if (ptr != NULL) printHeader();
    while(ptr != NULL) { // Prints all the records in the directory to the screen.
        printf("\n%-20d%-20s%-20s", ptr->ordinalNum, ptr->phoneNum, ptr->name);
        ptr = ptr->next;
    }
}

void printHeader() { // This function is a helper function that displays a describing header.
    puts("\n-----------------------------------------------------");
    printf("%-20s%-20s%-20s\n", "Ordinal number#", "Phone number#", "Name:");
    puts("-----------------------------------------------------");
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
    newNode->ordinalNum = 1; // New records will always be inserted as the first record in directory therefore ordinalNum = 1.
    return newNode;
}

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

void validName(int *j, int flag, char *name) { // Checks if format of the string entered is valid.
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
        while (ptr->next != NULL) { // All nodes succeding newNode have their ordinalNum incremented by 1.
            ptr->ordinalNum += 1;
            ptr = ptr->next;
        }
        if (ptr->next == NULL) ptr->ordinalNum += 1; // Needed this if statement to make sure the last node in the directory is incremented by 1.
        return flag = 0; // Successful insertion flag = 0 is returned.
    }
}

int deleteRecord(char phoneNum[NAME_NUM_LEN]) { // Deletes any record in the directory.
    int flag = 0;
    if (emptyDirectory()) return flag = 1; // If directory is empty return flag = 1.
    Node *prePtr = searchDirectory(phoneNum, &flag); // Searches for phone number inputted by user.
    Node *ptr = start;
    if (flag == 0) return flag = -1; // If flag == 0 record doesn't exists returns flag = -1.
    else if (prePtr == NULL) { // If found record is the first record in the directory.
        start = ptr->next; // Start becomes the record start points to.
        free(ptr); // Frees the old start record.
        ptr = start; // Set ptr to the new start record.
        if (ptr == NULL) return flag = 0; // If directory now is empty retrun flag = 0 which means deletion was successful.
        while (ptr->next != NULL) { // Else lower all following records ordinal number by one.
            ptr->ordinalNum -= 1;
            ptr = ptr->next;
        }
        if (ptr->next == NULL) ptr->ordinalNum -= 1; // If only one record left in the directory.
    }
    else if (strcmp((ptr = prePtr->next)->phoneNum, phoneNum) == 0) { // Sets ptr to the record pointed to by prePtr and comepare phone numbers.
        prePtr->next = ptr->next; // prePtr->next is now set to point to the record after the record that user wants to delete.
        free(ptr);
        while (prePtr->next != NULL) { // Lowers all following records ordinal number by one.
            prePtr = prePtr->next;
            prePtr->ordinalNum -= 1;
        }
    }
    return flag = 0; // Deletion was successful.
}
// Searches the directory for the record with given phone number or name.
static Node* searchDirectory(char nameOrPhoneNum[NAME_NUM_LEN], int *flag) {
    Node *ptr = start, *prePtr = ptr;
    if (ptr != NULL) { // If directory contains of only one element and is found set flag = 1 and return NULL.
        if ((strcmp(ptr->phoneNum, nameOrPhoneNum)) == 0 || (strcmp(ptr->name, nameOrPhoneNum)) == 0 && ptr->ordinalNum == 1) {
            *flag = 1;
            return prePtr = NULL;
        }
    }
    // If the directory contains of more than one record and is found set flag = 1 and return the record previous to the record searched for.
    while (ptr != NULL) { 
        if ((strcmp(ptr->phoneNum, nameOrPhoneNum)) == 0 || (strcmp(ptr->name, nameOrPhoneNum)) == 0) {
            *flag = 1;
            return prePtr;
        }
        prePtr = ptr;
        ptr = ptr->next;
    }
    return ptr; // Record wasn't found returns ptr that is NULL in this case.
}

static bool emptyDirectory() { // Returns true or false depending on if the directory is empty or not.
    return (start == NULL) ? true : false;
}