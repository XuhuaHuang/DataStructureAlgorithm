/*****************************************************************//**
 * \file   LinkList.h
 * \brief  Contains definition on (Single) Linked List in C.
 * 
 * \author Xuhua Huang
 * \date   September 2021
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * In the following implementation, ListNode refers to the type of a Node;
 * LinkList refers to the pointer type pointing ti a linked list.
 * LinkList L; ==> ListNode* L;
 */
typedef struct Node
{
public:
    int data;
    struct Node* next;
}ListNode, *LinkList;

/* Providing basic operation of defined LinkList struct. */
/* Function to initialize linked list. */
void InitLinkList(LinkList* head) {
    if ((*head=(LinkList)malloc(sizeof(ListNode))) == NULL)
        exit(-1);
    (*head)->next = nullptr;
}

/* Function to determine whether the linked list is empty. */
int isLinkListEmpty(const LinkList& head) {
    if (head->next == nullptr)
        return 1;
    else
        return 0;
}

/* Function to get element by index. */
ListNode* GetElement(const LinkList& head, int index) {
    if (isLinkListEmpty(head))
        return nullptr;
    else if (index < 1)
        return nullptr;
    
    ListNode* p = head;
    int j = 0;
    // loop through the list and locate the pointer to index position
    while (p->next != nullptr && j < index)
    {
        p = p->next;
        j++;
    }
    // now p has reached the proper position
    if (j == index)
        return p;
    else
        return nullptr;
}

/* Function to get element by content, O(n). */
ListNode* LocElement(const LinkList& head, int e) {
    ListNode* p = head->next;
    while (p)
    {
        if (p->data != e)
            p = p->next;
        else
            return p;
    }
}

/* Function to locate the element by content */
int GetElementPos(LinkList head, int e) {
    if (isLinkListEmpty(head))
        return 0;

    ListNode* p = head->next;
    int index = 1;
    while (p)
    {
        if (p->data == e)
            return index;
        else {
            p = p->next;
            index++;
        }
    }
    if (!p)
        return 0;
}

/* Function to insert an element to the list. */
int InsertList(LinkList head, int index, int e) {
    ListNode* previous = head;
    ListNode* newNode;

    // loop through the list and locate the pointer to index position
    int j = 0;
    while (previous->next != nullptr && j < index-1)
    {
        previous = previous->next;
        j++;
    }
    // now pointer `previous` has reached the proper position
    
    // determine the position of j
    if (j != index - 1) {
        printf("ERROR!Illegal insertion position!\n");
        return 0;
    }

    if ((newNode = (ListNode*)malloc(sizeof(ListNode))) == NULL)
        exit(-1);
    
    newNode->data = e;
    newNode->next = previous->next;
    previous->next = newNode;
    return 1;
}

/* Function to delete an element from the list. */
int DeleteFromList(LinkList head, int index, int* e) {
    /**
     * Delete an element from the linked list.
     * 
     * \param head    operable linked list pointer
     * \param i        index of the element to be deleted
     * \param e        memory to store the deleted element
     * \return 0 for failure, 1 for success, exit(-1) for error
     */
    ListNode* previous = head;
    ListNode* delNode = nullptr;
    
    // loop through the list and locate the pointer to index position
    int j = 0;
    while (previous->next
        && previous->next->next
        && j < index - 1) 
    {
        previous = previous->next;
        j++;
    }
    // now pointer `previous` has reached the proper position

    // determine the position of j
    if (j != index - 1) {
        printf("ERROR!Illegal insertion position!\n");
        return 0;
    }

    delNode = previous->next;
    *e = (int)(delNode->data);
    // disconnect the newNode from the previous node
    previous->next = delNode->next;
    free(delNode);
    return 1;
}

/* Function to determine the length of a list. */
int ListLength(LinkList head) {
    ListNode* p = head;
    int count = 0;
    while (p->next != nullptr)
    {
        p = p->next;
        count++;
    }
    return count;
}

/* Function to clear a linked list. */
void DestroyLinkList(LinkList head) {
    ListNode* p = head;
    ListNode* q = nullptr;
    while (p->next) 
    {
        q = p;
        p = p->next;
        free(q);
    }
}
