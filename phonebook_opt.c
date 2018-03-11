#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

bst_entry *findName(char lastName[], bst_entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        else if(strcasecmp(lastName, pHead->lastName) < 0)
            pHead = pHead->left;
        else
            pHead = pHead->right;
    }
    return NULL;
}


entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

/* sortedListToBSTRecur() to construct BST */
bst_entry* sortedListToBST(entry *head)
{
    /*Count the number of nodes in Linked List */
    int n = countLNodes(head);

    /* Construct BST */
    return sortedListToBSTRecur(&head, n);
}

/* The main function that constructs balanced BST and returns root of it.
       head_ref -->  Pointer to pointer to head node of linked list
       n  --> No. of nodes in Linked List */
bst_entry* sortedListToBSTRecur(entry **head_ref, int n)
{
    /* Base Case */
    if (n <= 0)
        return NULL;

    /* Recursively construct the left subtree */
    bst_entry *left = sortedListToBSTRecur(head_ref, n/2);

    /* Allocate memory for root, and link the above constructed left
       subtree with root */
    bst_entry *root = newNode((*head_ref)->lastName);
    root->left = left;

    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref)->pNext;

    /* Recursively construct the right subtree and link it with root
      The number of nodes in right subtree  is total nodes - nodes in
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = sortedListToBSTRecur(head_ref, n-n/2-1);

    return root;
}

/* A utility function that returns count of nodes in a given Linked List */
int countLNodes(entry *head)
{
    int count = 0;
    entry *temp = head;
    while(temp) {
        temp = temp->pNext;
        count++;
    }
    return count;
}


/* Helper function that allocates a new node with the
   given lastName and NULL left and right pointers. */
bst_entry* newNode(char lastName[])
{
    bst_entry* node = (bst_entry*)
                      malloc(sizeof(bst_entry));
    strcpy(node->lastName, lastName);
    node->left = NULL;
    node->right = NULL;

    return node;
}
