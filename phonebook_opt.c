#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

entry *findName(char lastName[], entry *pHead)
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

/* Helper function that allocates a new node with the given lastName and
    NULL left and right pointers. */
entry* newNode(char lastName[])
{
    entry *node = (entry*)malloc(sizeof(entry));
    strcpy(node->lastName, lastName);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to get height of the tree
int height(entry *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

entry *append(char lastName[], entry *node)
{
    /* 1.  Perform the normal BST appendion */
    if (node == NULL)
        return(newNode(lastName));

    if (strcasecmp(lastName, node->lastName) < 0)
        node->left  = append(lastName, node->left);
    else if (strcasecmp(lastName, node->lastName) > 0)
        node->right = append(lastName, node->right);
    else // Equal lastNames are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && strcasecmp(lastName, node->left->lastName) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcasecmp(lastName, node->right->lastName) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcasecmp(lastName, node->left->lastName) > 0) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcasecmp(lastName, node->right->lastName) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

void preOrder(entry *root)
{
    if(root != NULL) {
        printf("%s ", root->lastName);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// A utility function to right rotate subtree rooted with y
entry *rightRotate(entry *y)
{
    entry *x = y->left;
    entry *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
entry *leftRotate(entry *x)
{
    entry *y = x->right;
    entry *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(entry *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

