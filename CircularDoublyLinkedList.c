#include "CircularDoublyLinkedList.h"

/* 문자열 생성 */
char* createString(char* newString)
{
    if (strlen(newString) == 0)
        return NULL;

    char* _newString = (char*)malloc(sizeof(char) * strlen(newString));
    strcpy(_newString, newString);

    return _newString;
}

/* 문자열 삭제 */
void destroyString(char* string)
{
    free(string);
}

/* 노드 생성 */
Node* createNode(elementType newData)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    newNode->hasList = 0;
    
    strcpy(newNode->data, newData);

    return newNode;
}

/* 노드 삭제 */
void destroyNode(Node* node)
{
    free(node);
}

/* 노드에서 문자열 얻기 */
char* getStringAsNode(Node* node)
{
    return node->data;
}

/* 노드 추가 */
int appendNode(Node** list, Node* newNode)
{
    int index;

    if (!isNoHasList(newNode))
        return -1;

    if (isEmpty(*list))
    {
        (*list) = newNode;

        newNode->nextNode = newNode;
        newNode->prevNode = newNode;

        index = 0;
    }
    else
    {
        int oldSize = getSize(*list);
        Node* oldTail = (*list)->prevNode;

        oldTail->nextNode = newNode;
        (*list)->prevNode = newNode;

        index = oldSize;
    }

    newNode->hasList = 1;
    return index;
}

/* 노드 제거 */
int removeNode(Node** list, Node* node)
{
    int index;

    if (isEmpty(*list) || isNoHasList(node))
        return -1;

    if ((*list) == node)
    {
        (*list) = NULL;
        node->nextNode = NULL;
        node->prevNode = NULL;

        index = 0;
    }
    else
    {
        if (!currentNode(*list, node))
            return -1;

        index = getIndex(*list, node);
        node->prevNode->nextNode = node->nextNode;
        node->nextNode->prevNode = node->prevNode;
        node->prevNode = NULL;
        node->nextNode = NULL;
    }

    node->hasList = 0;
    return index;
}

/* 위치의 노드 제거 */
int removeNodeAt(Node** list, int location)
{
    if (isEmpty(*list) || (getSize(*list) <= location))
        return -1;

    Node* remove = getNodeAt(*list, location);
    if (remove == NULL)
        return -1;

    int index = removeNode(list, remove);
    return index;
}

/* 노드 삽입 */
int insertNode(Node** list, Node* current, Node* newNode)
{
    int index;

    if (isEmpty(*list) || isNoHasList(current) || (!isNoHasList(newNode)))
        return -1;
    
    if ((*list) == current)
    {
        current->nextNode = newNode;
        current->prevNode = newNode;
        newNode->nextNode = current;
        newNode->prevNode = current;

        index = 0;
    }
    else
    {
        if (!currentNode(*list, current))
            return -1;
        
        Node* oldNext = current->prevNode;

        current->nextNode = newNode;
        oldNext->prevNode = newNode;
        newNode->nextNode = oldNext;
        newNode->prevNode = current;

        index = getIndex(*list, newNode);
    }

    newNode->hasList = 1;
    return index;
}

/* 새 헤드 삽입 */
int insertNewHead(Node** list, Node* newHead)
{
    if (!isNoHasList(newHead))
        return -1;

    if (isEmpty(*list))
    {
        (*list) = newHead;

        newHead->nextNode = newHead;
        newHead->prevNode = newHead;
    }
    else
    {
        Node* oldTail = (*list)->prevNode;

        oldTail->nextNode = newHead;
        (*list)->prevNode = newHead;

        (*list) = newHead;
    }

    newHead->hasList = 1;
    return 0;
}

/* 위치에 노드 삽입 */
int insertNodeAt(Node** list, int location, Node* newNode)
{
    if (isEmpty(*list) || (!isNoHasList(newNode)))
        return -1;
    
    Node* current = getNodeAt(*list, location);
    if (current == NULL)
        return -1;

    int index = insertNode(list, current, newNode);
    return index;
}

/* 노드 앞에 삽입 */
int insertNodeAfter(Node** list, Node* current, Node* newNode)
{
    int index;

    if (isEmpty(*list) || isNoHasList(current) || (!isNoHasList(newNode)))
        return -1;

    if ((*list) == current)
    {
        current->nextNode = newNode;
        current->prevNode = newNode;
        newNode->nextNode = current;
        newNode->prevNode = current;
        (*list) = newNode;

        index = 0;
    }
    else
    {
        if (!currentNode(*list, current))
            return -1;

        Node* oldPrev = current->prevNode;

        oldPrev->nextNode = newNode;
        current->prevNode = newNode;
        newNode->prevNode = oldPrev;
        newNode->nextNode = current;

        index = getIndex(*list, newNode);
    }

    newNode->hasList = 1;
    return index;
}

/* 위치에 노드 앞에 삽입 */
int insertNodeAfterAt(Node** list, int location, Node* newNode)
{
    if (isEmpty(*list) || (!isNoHasList(newNode)))
        return -1;

    Node* current = getNodeAt(*list, location);
    if (current == NULL)
        return -1;

    int index = insertNodeAfter(list, current, newNode);
    return index;
}

/* 노드 얻기 */
Node* getNodeAt(Node* list, int location)
{
    if (isEmpty(list))
        return NULL;

    if (getSize(list) <= location)
        return NULL;

    if (location < 0)
        return NULL;
    
    Node* current = list;
    while (0 <= (--location))
        current = current->nextNode;

    return current;
}

/* 비어있는지 확인 */
int isEmpty(Node* list)
{
    if (getSize(list) == 0)
        return 1;
    else
        return 0;
}

/* 리스트 크기 확인 */
int getSize(Node* list)
{
    if (list == NULL)
        return 0;

    int size = 0;
    Node* current = list;

    do
    {
        current = current->nextNode;
        size++;
    }
    while (current != list);

    return size;
}

/* 리스트 삭제 */
int destroyList(Node** list)
{
    if (isEmpty(*list))
        return -1;

    int size = getSize(*list);
    for (int i = 0; i < size; i++)
    {
        Node* current = getNodeAt(*list, i);
        removeNode(list, current);
        destroyNode(current);
    }

    return 0;
}

/* 문자열 리스트 삭제 */
int destroyListAndStrings(Node** list)
{
    if (isEmpty(*list))
        return -1;

    int size = getSize(*list);
    for (int i = 0; i < size; i++)
    {
        Node* current = getNodeAt(*list, i);
        char* str = getStringAsNode(current);
        removeNode(list, current);
        destroyNode(current);
        destroyString(str);
    }
    
    return 0;
}

/* 노드가 리스트에 포함되어 있지 않은지 확인 */
int isNoHasList(Node* node)
{
    if (node == NULL)
        return 1;

    if (node->hasList)
        return 0;
    else
        return 1;
}

/* 리스트에 노드가 있는지 확인 */
int currentNode(Node* list, Node* node)
{
    if (isEmpty(list) || isNoHasList(node))
        return 0;

    Node* findCurrent = list;
    do
    {
        if (findCurrent == node)
            return 1;

        findCurrent = findCurrent->nextNode;
    }
    while (findCurrent != list);

    return 0;
}

/* 인덱스 얻기 */
int getIndex(Node* list, Node* node)
{
    if (isEmpty(list) || isNoHasList(node) || (!currentNode(list, node)))
        return -1;

    Node* current = list;
    int index = 0;
    while (1)
    {
        if (current == node)
            return index;
        current = current->nextNode;
        index++;
    }
}