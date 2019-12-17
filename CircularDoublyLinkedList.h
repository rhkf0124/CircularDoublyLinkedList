#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLE_LINKED_LIST_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* elementType;

typedef struct tagNode {
    elementType data;
    int hasList;
    struct tagNode* prevNode;
    struct tagNode* nextNode;
} Node;

/* 함수 원형 선언 */
char* createString(char* newString);
void destroyString(char* string);
Node* createNode(elementType newData);
void destroyNode(Node* node);
char* getStringAsNode(Node* node);
int appendNode(Node** list, Node* newNode);
int removeNode(Node** list, Node* node);
int removeNodeAt(Node** list, int location);
int insertNode(Node** list, Node* current, Node* newNode);
int insertNewHead(Node** list, Node* newHead);
int insertNodeAt(Node** list, int location, Node* newNode);
int insertNodeAfter(Node** list, Node* current, Node* newNode);
int insertNodeAfterAt(Node** list, int location, Node* newNode);
Node* getNodeAt(Node* list, int location);
int isEmpty(Node* list);
int getSize(Node* list);
int destroyList(Node** list);
int destroyListAndStrings(Node** list);
int isNoHasList(Node* node);
int currentNode(Node* list, Node* node);
int getIndex(Node* list, Node* node);

#endif