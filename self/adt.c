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
    int i = 0;
    NODE *pTmp = g_pHead;
    while(pTmp != 0){
        if(pTmp == g_pHead || pTmp == g_pTail){
            printf("DUMMY \n");
        }else{
            USERDATA* pUser = pTmp->pData;
            printf("[[%d]] [%p] %s [%p] \n", 
                i, 
                pTmp->prev, 
                pUser->GetKey(pUser), 
                pTmp->next);
        }
        pTmp = pTmp -> next;
        ++i;
    }
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

int DeleteNode(char *pszKey){
    NODE *pDelete = FindNode(pszKey);

    pDelete -> prev -> next = pDelete -> next;
    pDelete -> next -> prev = pDelete -> prev;
    free(pDelete -> pData);
    free(pDelete);
    g_nSize --;

    return 0;
}

int InsertAt(int idx, void *pParam){
    NODE *pTmp = g_pHead->next;
    int i = 0;
    while(pTmp != NULL){
        if(i == idx){
            InsertBefore(pTmp, pParam);
            return 1;
        }
        pTmp = pTmp -> next;
        i++;
    }
    return 0;
}

NODE *GetAt(){}
USERDATA *CreateUserData(const char *pszName, const char *pszPhone){
    USERDATA *pNewData = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewData, 0, sizeof(USERDATA));

    strcpy(pNewData->szName, pszName);
    strcpy(pNewData->szPhone, pszPhone);

    pNewData -> GetKey = GetKeyFromUserData;
    return pNewData;
}

int main(){
    InitList();
    USERDATA *pNewData = NULL;
    pNewData = CreateUserData("TEST 01", "010-0000-0000");
    InsertAtTail(pNewData);
    pNewData = CreateUserData("TEST 02", "010-0000-0002");
    InsertAt(1, pNewData);

    PrintList();

    return 0;
}

