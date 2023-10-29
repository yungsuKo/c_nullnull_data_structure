// 지금까지 만든 구조는 전역변수 때문에 재사용하기 어려움
// 연결리스트 헤드/테일 노드를 개별화함
// 재사용성을 높이기위해 분할 컴파일

// 코드를 볼 때는 2가지 관점으로 봐야함
    // 자료구조를 만드는 부분과 만들어진 것을 가져다 사용하는 것

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylist.c"

// typedef struct NODE {
//     void *pData;

//     // 자료구조
//     struct NODE *prev;
//     struct NODE *next;
// } NODE;

// typedef struct LIST_INFO {
//     NODE *pHead;
//     NODE *pTail;
//     int nSize;
// } LIST_INFO;


typedef struct USERDATA {
    const char *(*GetKey)(struct USERDATA *);
    char szName[64];
    char szPhone[64];
} USERDATA;

const char *GetKeyFromUserData(USERDATA *pUser){
    return pUser -> szName;
}

USERDATA *CreateUserData (const char* pszName, const char* pszPhone){
    USERDATA *pNewNode = (USERDATA *)malloc(sizeof(USERDATA));
    memset(pNewNode, 0, sizeof(USERDATA));
    strcpy(pNewNode->szName, pszName);
    strcpy(pNewNode->szPhone, pszPhone);

    pNewNode -> GetKey = GetKeyFromUserData;
    return pNewNode;
}

void PrintList(LIST_INFO *pListData){
    int i = 0;
    NODE *pTmp = pListData->pHead;
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
}

// void InitList(LIST_INFO *pListData) {
//     pListData -> pHead = (NODE*)malloc(sizeof(NODE));
//     pListData -> pTail = (NODE*)malloc(sizeof(NODE));
//     pListData -> nSize = 0;

//     memset(pListData->pHead, 0, sizeof(NODE));
//     memset(pListData->pTail, 0, sizeof(NODE));

//     pListData -> pHead -> next = pListData -> pTail;
//     pListData -> pTail -> prev = pListData -> pHead;
// }

// void ReleaseList(LIST_INFO *pListData){
//     NODE* pTmp = pListData->pHead;
//     while(pTmp != 0){
//         NODE* pDelete = pTmp;
//         pTmp = pTmp -> next;
//         free(pDelete->pData);
//         free(pDelete);
//     }

//     pListData->pHead = NULL;
//     pListData->pTail = NULL;
//     pListData->nSize = 0;
//     puts("ReleaseList() \n");
// }

// int InsertAtHead(LIST_INFO *pListData, void *pParam){
//     NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
//     memset(pNewNode, 0, sizeof(NODE));
//     pNewNode -> pData = pParam;
    
//     pNewNode -> next = pListData->pHead->next;
//     pNewNode -> prev = pListData->pHead;
//     pListData->pHead->next->prev = pNewNode;
//     pListData->pHead->next = pNewNode;
    
//     pListData->nSize ++;
//     return pListData->nSize;
// }

// void InsertBefore(LIST_INFO *pListData, NODE *pDstNode, void *pParam){
//     NODE *pPrev = pDstNode -> prev;
//     NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
//     memset(pNewNode, 0, sizeof(NODE));
//     pNewNode->pData = pParam;

//     pNewNode -> next = pDstNode;
//     pNewNode -> prev = pPrev;
//     pPrev -> next = pNewNode;
//     pDstNode -> prev = pNewNode;

//     pListData->nSize++;
// }

// int InsertAtTail(LIST_INFO *pListData, void *pParam){
//     InsertBefore(pListData, pListData->pTail, pParam);
//     return pListData->nSize;
// }

// NODE *FindNode(LIST_INFO *pListData, char *pszKey){
//     char *(*pfGetKey)(void*) = NULL; // 이 부분은 아직 모르겠음
//     NODE *pTmp = pListData->pHead->next;
//     while(pTmp != pListData->pTail){
//         pfGetKey = pTmp->pData;
//         if(strcmp(pfGetKey(pTmp->pData), pszKey)==0){
//             return pTmp;
//         }
//         pTmp = pTmp->next;
//     }
//     return NULL;
// }

// int DeleteNode(LIST_INFO *pListData, char *pszKey){
//     NODE *pDelete = FindNode(pListData, pszKey);

//     pDelete -> prev -> next = pDelete -> next;
//     pDelete -> next -> prev = pDelete -> prev;
//     free(pDelete -> pData);
//     free(pDelete);
//     pListData->nSize --;

//     return 0;
// }

// int InsertAt(LIST_INFO *pListData, int idx, void *pParam){
//     NODE *pTmp = pListData->pHead->next;
//     int i = 0;
//     while(pTmp != NULL){
//         if(i == idx){
//             InsertBefore(pListData, pTmp, pParam);
//             return 1;
//         }
//         pTmp = pTmp -> next;
//         i++;
//     }
//     return 0;
// }

// NODE *GetAt(LIST_INFO *pListData, int idx){
//     NODE *pTmp = pListData -> pHead -> next;
//     int i = 0;
//     while(pTmp->next != pListData -> pTail){
//         if(idx == i){
//             return pTmp;
//         }
//         pTmp = pTmp->next;
//         i ++;
//     }
//     return NULL;
// }


int main(){
    LIST_INFO userList01 = {0};
    InitList(&userList01);

    USERDATA *pNewData = CreateUserData("TOM", "01000000000");
    InsertAtTail(&userList01, pNewData);
    PrintList(&userList01);

    ReleaseList(&userList01);
    

}