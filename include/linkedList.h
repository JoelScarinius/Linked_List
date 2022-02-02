#ifndef _linkedList_h
#define _linkedList_h

#define NAME_NUM_LEN 15

typedef struct Node {
    struct Node *next;
    char phoneNum[NAME_NUM_LEN];
    char name[NAME_NUM_LEN];
    int ordinalNum;
} Node;

// This is a helper function that is used in some other functions and it returns void.
// The function controls that the user inputs a valid format when inputting the phone number to the record.
void validPhoneNum(int *i, int flag, char *phoneNum);
// This is a helper function that is used in some other functions and it returns void.
// The function controls that the user inputs a valid format when inputting the name to the record.
void validName(int *j, int flag, char *name);
Node* displayRecord(int *flag, char nameOrPhoneNum[NAME_NUM_LEN]);
void displayDirectory();
void printHeader();
Node* createRecord();
int insertRecordBeg(Node *newNode);
int deleteRecord(char phoneNum[NAME_NUM_LEN]);

#endif