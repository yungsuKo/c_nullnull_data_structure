#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylist.h"

//////////////////////////////////////
typedef struct USERDATA {
    // 멤버 함수 포인터
    const char * (*GetKey)(void *);

    char szName[64];
    char szPhone[64];
} USERDATA;

const char* GetKeyFromUserData(USERDATA *pUser){
    return pUser->szName;
}

USERDATA *CreateUserData (const char* pszName, const char *pszPhone){
    USERDATA *pNewData = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewData, 0, sizeof(USERDATA));

    strcpy(pNewData -> szName, pszName);
    strcpy(pNewData -> szPhone, pszPhone);

    // 구조체 멈버함수 초기화
    pNewData -> GetKey = GetKeyFromUserData;
    return pNewData;
}

//////////////////////////////////////
void PrintList(LIST_INFO* pListData) {
    int i = 0;
    printf("PrintList() sizeof : [%d], g_pHead : [%p], g_pTail : [%p] \n",
        pListData->nSize, 
        pListData->pHead->next, 
        pListData->pTail);
    NODE* pTmp = pListData->pHead;
    while(pTmp != 0){
        if(pTmp == pListData->pHead || pTmp == pListData->pTail){
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

    printf("\n");
}

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


//////////////////////////////////////
// 관리 대상 자료에 대해 의존성이 있음.
// pParam: 호출자가 메모리를 동적할당 + 값설정까지 해서 전달

int main(void){
    LIST_INFO userList1 = {0};
    InitList(&userList1);
    
    USERDATA* pNewData = CreateUserData("New User1", "111-111-111");
    InsertAtTail(&userList1, pNewData);
    pNewData = CreateUserData("New User2", "222-222-222");
    InsertAtTail(&userList1, pNewData);
    pNewData = CreateUserData("New User3", "333-333-333");
    InsertAtTail(&userList1, pNewData);

    PrintList(&userList1);
    ReleaseList(&userList1);

    return 0;
}