#pragma once

typedef struct NODE {
    void *pData;
    NODE *prev;
    NODE *next;
} NODE;

typedef struct LIST_INFO {
    NODE *pHead;
    NODE *pTail;
    int nSize;
} LIST_INFO;

// mylist.c 선언

void InitList(LIST_INFO *pListData);
void ReleaseList(LIST_INFO *pListData);
void InsertAtHead(LIST_INFO *pListData, void *pData);
void InsertBefore(LIST_INFO *pListData, NODE* pDstNode, void *pData);
void InsertAtTail(LIST_INFO *pListData, void *pData);
NODE *FindNode(LIST_INFO *pListData, char *pszKey);
int Delete(LIST_INFO *pListData, char *pszKey);
int InsertAt(LIST_INFO *pListData, int idx, void *pParam);
NODE *GetAt(LIST_INFO *pListData, int idx);