/**
 * @file LinkedList.h
 * @author Zhang Hai
 */

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_


#include "Common.h"


#define LINKED_LIST_FOR_EACH(list, node) \
    for (node = list->fields->head; node != null; node = node->next)


typedef struct tagLinkedListNode LinkedListNode;
typedef struct tagLinkedListNode {
    void *data;
    LinkedListNode *previous;
    LinkedListNode *next;
} LinkedListNode;


typedef struct {
    LinkedListNode *head;
    LinkedListNode *tail;
    size_t size;
} LinkedList_Fields;


typedef struct tagLinkedList LinkedList;

typedef LinkedList *(*LinkedList_MethodNew)();
typedef void (*LinkedList_MethodDelete)(LinkedList *this);
typedef LinkedListNode *(*LinkedList_MethodNewNode)(void *data,
        LinkedListNode *previous,
        LinkedListNode *next);
typedef void (*LinkedList_MethodDeleteNode)(
        LinkedListNode *node);
typedef LinkedListNode *(*LinkedList_MethodAddStart)(
        LinkedList *this, void *book);
typedef LinkedListNode *(*LinkedList_MethodAddEnd)(LinkedList *this,
        void *book);
typedef LinkedListNode *(*LinkedList_MethodInsertBefore)(
        LinkedList *this, LinkedListNode *node, void *book);
typedef LinkedListNode *(*LinkedList_MethodInsertAfter)(
        LinkedList *this, LinkedListNode *node, void *book);
typedef LinkedListNode *(*LinkedList_MethodRemoveNode)(
        LinkedList *this, LinkedListNode *node);
typedef void (*LinkedList_MethodRemove)(LinkedList *this,
        void *book);
typedef void (*LinkedList_MethodSwap)(LinkedList *this,
        LinkedListNode *node1, LinkedListNode *node2);
typedef void (*LinkedList_MethodSort)(LinkedList *this,
        Comparator comparator);
typedef LinkedList *(*LinkedList_MethodSearch)(LinkedList *this,
        Filter filter);

typedef struct {

    LinkedList_MethodNew new;
    LinkedList_MethodDelete delete;

    LinkedList_MethodNewNode newNode;
    LinkedList_MethodDeleteNode deleteNode;
    LinkedList_MethodAddStart addStart;
    LinkedList_MethodAddEnd addEnd;
    LinkedList_MethodInsertBefore insertBefore;
    LinkedList_MethodInsertAfter insertAfter;
    LinkedList_MethodRemoveNode removeNode;
    LinkedList_MethodRemove remove;
    LinkedList_MethodSwap swap;
    LinkedList_MethodSort sort;
    LinkedList_MethodSearch search;
} LinkedList_Methods;


typedef struct tagLinkedList {
    LinkedList_Fields *fields;
    LinkedList_Methods *methods;
} LinkedList;


void LinkedList_initialize(LinkedList *this);

void LinkedList_finalize(LinkedList *this);

LinkedListNode *LinkedList_newNode(void *data, LinkedListNode *prev,
        LinkedListNode *next);

void LinkedList_deleteNode(LinkedListNode *node);

LinkedList *LinkedList_new();

void LinkedList_delete(LinkedList *this);

LinkedListNode *LinkedList_addStart(LinkedList *this, void *data);

LinkedListNode *LinkedList_addEnd(LinkedList *this, void *data);

LinkedListNode *LinkedList_insertBefore(LinkedList *this,
        LinkedListNode *node, void *data);

LinkedListNode *LinkedList_insertAfter(LinkedList *this,
        LinkedListNode *node, void *data);

LinkedListNode *LinkedList_removeNode(LinkedList *this,
        LinkedListNode *node);

void LinkedList_remove(LinkedList *this, void *data);

void LinkedList_swap(LinkedList *this, LinkedListNode *node1,
        LinkedListNode *node2);

void LinkedList_sort(LinkedList *this, Comparator comparator);

LinkedList *LinkedList_search(LinkedList *this, Filter filter);


#endif /* _LINKED_LIST_H_ */
