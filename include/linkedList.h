#ifndef _linkedList_h
#define _linkedList_h

#define NAME_NUM_LEN 15

typedef struct Node {
    struct Node *next;
    char phoneNum[NAME_NUM_LEN];
    char name[NAME_NUM_LEN];
    int recordNum;
} Node;

void validPhoneNum(int *i, int flag, char *phoneNum);
Node* displayRecord(int flag);
void displayDirectory();
Node* createRecord();
int insertRecordBeg(Node *newNode);
int deleteRecord(char phoneNum[NAME_NUM_LEN]);

#endif