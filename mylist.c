#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylist.h"

void InitList(LIST_INFO *pListData){
    pListData->pHead = (NODE*)malloc(sizeof(NODE));
    pListData->pTail = (NODE*)malloc(sizeof(NODE));

    pListData->nSize = 0;
    memset(pListData->pHead, 0, sizeof(NODE));
    memset(pListData->pTail, 0, sizeof(NODE));

    pListData->pHead->next = pListData->pTail;
    pListData->pTail->prev = pListData->pHead;
}

void ReleaseList(LIST_INFO *pListData){
    NODE* pTmp = pListData->pHead;
    while(pTmp != 0){
        NODE* pDelete = pTmp;
        pTmp = pTmp -> next;
        free(pDelete->pData);
        free(pDelete);
    }

    pListData->pHead = NULL;
    pListData->pTail = NULL;
    pListData->nSize = 0;
    puts("ReleaseList() \n");
}

int InsertAtHead(LIST_INFO* pListData, void *pParam){
    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->pData = pParam;
    // pNewNode->pData=pfParam;

    pNewNode->next = pNewNode->prev->next;
    pNewNode->prev = pListData->pHead;

    pListData->pHead->next = pNewNode;
    pNewNode->next->prev = pNewNode;
    
    pListData->nSize ++;

    return pListData->nSize;
}

void InsertBefore(LIST_INFO* pListData, NODE* pDstNode, void *pParam){
    NODE *pPrev = pDstNode->prev;
    NODE *pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    //  관리 대상 자료에 대한 초기화
    pNewNode->pData = pParam;

    pNewNode->prev = pDstNode->prev;
    pNewNode->next = pDstNode;

    pDstNode->prev = pNewNode;
    pPrev->next = pNewNode;
    
    pListData->nSize ++;
}

int InsertAtTail(LIST_INFO* pListData, void *pParam){
    InsertBefore(pListData, pListData->pTail, pParam);
    return pListData->nSize;
}

NODE* FindNode(LIST_INFO* pListData, const char* pszKey){ 
    const char * (*pfGetKey)(void*) =NULL;
    NODE *pTmp = pListData->pHead->next; // head를 빼고 데이터 중에 검색
    while(pTmp != pListData->pTail){
        pfGetKey = pTmp->pData;
        if (strcmp(pfGetKey(pTmp->pData), pszKey) == 0){
            return pTmp;
        }
        pTmp = pTmp->next;
    }
    return NULL;
}

int DeleteNode(LIST_INFO* pListData, const char* pszKey){
    NODE *pNode=FindNode(pListData, pszKey);
    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;

    printf("DeleteNode() : %p\n", pNode);
    free(pNode->pData);
    free(pNode);

    pListData->nSize--;
    return 0;
}

int InsertAt(LIST_INFO* pListData,int idx, void *pParam){
    int i = 0;
    NODE *pTmp= pListData->pHead->next;
    while(pTmp!=pListData->pTail){
        if(i == idx){
            InsertBefore(pListData, pTmp, pParam);
            return i;
        }
        pTmp=pTmp->next;
        i++;
    }
    return 0;
}

NODE *GetAt(LIST_INFO* pListData, int idx){
    int i = 0;
    NODE *pTmp = pListData-> pHead -> next;
    while(pTmp != pListData->pTail){
        if(i == idx){
            return pTmp;
        }
        pTmp=pTmp -> next;
        i++;
    }
    return NULL;
}
