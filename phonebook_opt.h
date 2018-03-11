#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1

typedef struct __PHONE_BOOK_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __BST_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    char lastName[MAX_LAST_NAME_SIZE];
    struct __BST_ENTRY *left;
    struct __BST_ENTRY *right;
} bst_entry;

bst_entry *findName(char lastName[], bst_entry *pHead);
entry *append(char lastName[], entry *e);
bst_entry *newNode(char lastName[]);
int countLNodes(entry *head);
bst_entry *sortedListToBSTRecur(entry **head_ref, int n);
bst_entry *sortedListToBST(entry *head);

#endif
