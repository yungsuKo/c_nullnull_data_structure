#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylist.h"

void InitList(LIST_INFO *pListData) {
    pListData->pHead = (NODE*)malloc(sizeof(NODE));
    pListData->pTail = (NODE*)malloc(sizeof(NODE));
    pListData->nSize = 0;

    memset(pListData->pHead, 0, sizeof(NODE));
    memset(pListData->pTail, 0, sizeof(NODE));

    pListData->pHead->next = pListData->pTail;
    pListData->pTail->prev = pListData->pHead;
}

void ReleaseList(LIST_INFO *pListData) {
    NODE *pTmp = pListData->pHead;
    while(pTmp != NULL){
        NODE *pDelete = pTmp;
        pTmp = pTmp -> next;
        free(pDelete->pData);
        free(pDelete);
    }

    pListData -> nSize = 0;
    pListData -> pHead = NULL;
    pListData -> pTail = NULL;
    puts("Release() \n");
}

int InsertAtHead(LIST_INFO *pListData, void *pParam) {
    NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    pNewNode->pData = pParam;
    pNewNode->next = pListData->pHead->next;
    pNewNode->prev = pListData->pHead;

    pListData->pHead->next->prev = pNewNode;
    pListData->pHead->next = pNewNode;
    pListData->nSize ++;
    return pListData->nSize;
}

void InsertBefore(LIST_INFO *pListData, NODE* pDstNode, void *pParam) {
    NODE *pPrev = pDstNode -> prev;
    NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    pNewNode->pData = pParam;

    pNewNode -> next = pDstNode;
    pNewNode -> prev = pPrev;
    pPrev->next = pNewNode;
    pDstNode->prev = pNewNode;

    pListData->nSize ++;
}

int InsertAtTail(LIST_INFO *pListData, void *pParam) {
    InsertBefore(pListData, pListData->pTail,pParam);
    return pListData->nSize;
}

NODE *FindNode(LIST_INFO *pListData, char *pszKey) {
    char (*pfGetKey)(void *) = NULL;
    NODE *pTmp = pListData -> pHead;
    while(pTmp != pListData->pTail){
        pfGetKey = pTmp -> pData;
        if(strcmp(pfGetKey(pTmp->pData), pszKey) == 0){
            return pTmp;
        }
        pTmp = pTmp -> next;
    }
    return NULL;
}

int Delete(LIST_INFO *pListData, char *pszKey) {
    NODE *pDelete = FindNode(pListData, pszKey);
    pDelete->prev->next = pDelete->next;
    pDelete->next->prev = pDelete->prev;
    free(pDelete->pData);
    free(pDelete);
    pListData -> nSize --;
    return 0;
}

int InsertAt(LIST_INFO *pListData, int idx, void *pParam) {
    NODE *pTmp = pListData->pHead->next;
    int i = 0;
    while(pTmp->next != pListData->pTail){
        if(idx == i){
            InsertBefore(pListData, pTmp, pParam);
            return 1;
        }
        i++;
        pTmp = pTmp->next;
    }
    return 0;
}

NODE *GetAt(LIST_INFO *pListData, int idx) {
    NODE *pTmp = pListData->pHead->next;
    int i = 0;
    while(pTmp->next != pListData->pTail){
        if(i == idx){
            return pTmp;
        }
        i++;
        pTmp = pTmp->next;
    }
    return NULL;
}