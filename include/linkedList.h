#ifndef _linkedList_h
#define _linkedList_h

#define NAME_NUM_LEN 15 // This is a define that sets the maximum length of names and phone numbers inputted by user.

typedef struct Node { // This struct is used to create a linkedlist as a directory containing records with phone numbers and names.
    struct Node *next; // Next record in the directory
    char phoneNum[NAME_NUM_LEN]; // Phone number represented as a string.
    char name[NAME_NUM_LEN]; // Name represented as a string.
    int ordinalNum; // The records ordinal number in the directory.
} Node;

// This fuction displays one certain record searched by phone number or name deepending on what the user chooses.
// The function returns a record with the value null or the found record that the user searched for.
Node* displayRecord(int *flag, char nameOrPhoneNum[NAME_NUM_LEN]);
// This fuction displays the entire directory and returns void.
void displayDirectory();
// This function is a helper function that displays a describing header that helps the user to understand what they see and returns void.
void printHeader();
// This function creates a record containing phone number and name and returns the created record.
Node* createRecord();
// This is a helper function that is used in some other functions and it returns void.
// The function controls that the user inputs a valid format when inputting the phone number to the record.
void validPhoneNum(int *i, int flag, char *phoneNum);
// This is a helper function that is used in some other functions and it returns void.
// The function controls that the user inputs a valid format when inputting the name to the record.
void validName(int *j, int flag, char *name);
// This function inserts the created record to the beginning of the directory and returns a flag as an integer.
int insertRecordBeg(Node *newNode);
// This function deletes a record in the directory and returns a flag as an integer.
int deleteRecord(char phoneNum[NAME_NUM_LEN]);

#endif // End of linkedList.h