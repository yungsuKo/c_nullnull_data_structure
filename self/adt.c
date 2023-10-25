// 재사용이 가능한 연결리스트

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct USERDATA{
    const char *(*GetKey)(void *);
    char szName[64];
    char szPhone[64];
} USERDATA;

const char* GetKeyFromUserData(USERDATA *pUser){
    return pUser->szName;
}

typedef struct NODE{
    void *pData;

    struct NODE *prev;
    struct NODE *next;
} NODE;

NODE* g_pHead;
NODE* g_pTail;
int g_nSize;

void InitList(){
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));
    g_nSize = 0;

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    g_pHead -> next = g_pTail;
    g_pTail -> prev = g_pHead;
    puts("InitList() \n");
}

void ReleaseList(){}

void PrintList(){

}

int InsertAtHead(void *pParam){
    NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    pNewNode -> pData = pParam;
    
    pNewNode -> next = g_pHead->next;
    pNewNode -> prev = g_pHead;
    g_pHead->next->prev = pNewNode;
    g_pHead->next = pNewNode;
    
    g_nSize ++;
    return g_nSize;
}

void InsertBefore(NODE *pDstNode, void *pParam){
    NODE *pPrev = pDstNode -> prev;
    NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    pNewNode->pData = pParam;

    pNewNode -> next = pDstNode;
    pNewNode -> prev = pPrev;
    pPrev -> next = pNewNode;
    pDstNode -> prev = pNewNode;

    g_nSize++;
}

int InsertAtTail(USERDATA *pParam){
    InsertBefore(g_pTail, pParam);
    return g_nSize;
}

NODE *FindNode(char *pszKey){
    char *(*pfGetKey)(void*) = NULL; // 이 부분은 아직 모르겠음
    NODE *pTmp = g_pHead->next;
    while(pTmp != g_pTail){
        pfGetKey = pTmp->pData;
        if(strcmp(pfGetKey(pTmp->pData), pszKey)==0){
            return pTmp;
        }
        pTmp = pTmp->next;
    }
    return NULL;
}

int DeleteNode(){}

int InsertAt(){}

NODE *GetAt(){}
USERDATA *CreateUserData(){}

