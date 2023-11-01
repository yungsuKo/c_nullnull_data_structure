#pragma once

typedef struct NODE {
    void *pData;
    struct NODE *prev;
    struct NODE *next;
} NODE;

typedef struct LIST_INFO {
    struct NODE *pHead;
    struct NODE *pTail;
    int nSize;
} LIST_INFO;

// mylist.c 선언

void InitList(LIST_INFO *pListData);
void ReleaseList(LIST_INFO *pListData);
int InsertAtHead(LIST_INFO *pListData, void *pData);
void InsertBefore(LIST_INFO *pListData, NODE* pDstNode, void *pData);
int InsertAtTail(LIST_INFO *pListData, void *pData);
NODE *FindNode(LIST_INFO *pListData, char *pszKey);
int Delete(LIST_INFO *pListData, char *pszKey);
int InsertAt(LIST_INFO *pListData, int idx, void *pParam);
NODE *GetAt(LIST_INFO *pListData, int idx);