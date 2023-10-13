#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

typedef struct NODE{
    // 관리 대상 자료
    void *pData;

    // 자료구조
    struct NODE *prev;
    struct NODE *next;
} NODE;

//////////////////////////////////////
NODE* g_pHead; // 동적할당
NODE* g_pTail;
int g_nSize;
//////////////////////////////////////
void InitList(void){
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));
    g_nSize = 0;

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    g_pHead->next = g_pTail;
    g_pTail->prev = g_pHead;
    puts("InitList() \n");
}

void ReleaseList(void){
    NODE* pTmp = g_pHead;
    while(pTmp != 0){
        NODE* pDelete = pTmp;
        pTmp = pTmp -> next;
        printf("free(%p) \n", pDelete);
        free(pDelete);
    }

    g_pHead = 0;
    g_pTail = 0;
    g_nSize = 0;
    puts("ReleaseList() \n");
}

void PrintList(void) {
    int i = 0;
    printf("PrintList() sizeof : [%d], g_pHead : [%p], g_pTail : [%p] \n",g_nSize, g_pHead->next, g_pTail);
    NODE* pTmp = g_pHead;
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

    printf("\n");
}
//////////////////////////////////////
// 관리 대상 자료에 대해 의존성이 있음.
// pParam: 호출자가 메모리를 동적할당 + 값설정까지 해서 전달
int InsertAtHead(void *pParam){
    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->pData = pParam;
    // pNewNode->pData=pfParam;

    pNewNode->next = g_pHead->next;
    pNewNode->prev = g_pHead;

    g_pHead->next = pNewNode;
    pNewNode->next->prev = pNewNode;
    
    g_nSize ++;

    return g_nSize;
}

void InsertBefore(NODE* pDstNode, void *pParam){
    NODE *pPrev = pDstNode->prev;
    NODE *pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    //  관리 대상 자료에 대한 초기화
    pNewNode->pData = pParam;

    pNewNode->prev = pDstNode->prev;
    pNewNode->next = pDstNode;

    pDstNode->prev = pNewNode;
    pPrev->next = pNewNode;
    
    g_nSize ++;
}

int InsertAtTail(USERDATA *pParam){
    InsertBefore(g_pTail, pParam);
    return g_nSize;
}

NODE* FindNode(const char* pszKey){ 
    const char * (*pfGetKey)(void*) =NULL;
    NODE *pTmp = g_pHead->next; // head를 빼고 데이터 중에 검색
    while(pTmp != g_pTail){
        pfGetKey = pTmp->pData;
        if (strcmp(pfGetKey(pTmp->pData), pszKey) == 0){
            return pTmp;
        }
        pTmp = pTmp->next;
    }
    return NULL;
}

int DeleteNode(const char* pszKey){
    NODE *pNode=FindNode(pszKey);
    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;

    printf("DeleteNode() : %p\n", pNode);
    free(pNode->pData);
    free(pNode);

    g_nSize--;
    return 0;
}

int InsertAt(int idx, void *pParam){
    NODE *pTmp= g_pHead->next;
    int i = 0;
    while(pTmp!=g_pTail){
        if(i == idx){
            InsertBefore(pTmp, pParam);
            return i;
        }
        pTmp=pTmp->next;
        i++;
    }
    return 0;
}

NODE *GetAt(int idx){
    NODE *pTmp = g_pHead -> next;
    int i = 0;
    while(pTmp != g_pTail){
        if(i == idx){
            return pTmp;
        }
        pTmp=pTmp -> next;
        i++;
    }
    return NULL;
}

int main(void){
    InitList();

    USERDATA *pNewData= (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewData, 0, sizeof(USERDATA));
    strcpy(pNewData->szName, "Yong-su");
    strcpy(pNewData->szPhone, "000-0000-0000");
    InsertAtTail(pNewData);

    USERDATA *pNewData2= (USERDATA*)malloc(sizeof(USERDATA));
    memset(pNewData2, 0, sizeof(USERDATA));
    strcpy(pNewData2->szName, "TEST-01");
    strcpy(pNewData2->szPhone, "000-0000-0001");
    InsertAtTail(pNewData2);

    PrintList();

    ReleaseList();
}