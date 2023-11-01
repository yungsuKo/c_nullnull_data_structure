#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.c"

typedef struct USERDATA {
    const char *(*GetKey)(struct USERDATA *); // 다시 생각해보기
    char szName[64];
    char szPhone[64];
} USERDATA;

const char* GetKeyFromUserData(USERDATA *pUser) {
    return pUser -> szName;
}

USERDATA *CreateUserData(const char* pszName, const char *pszPhone){
    USERDATA *pNewNode = (USERDATA *)malloc(sizeof(USERDATA));
    memset(pNewNode, 0, sizeof(USERDATA));
    strcpy(pNewNode -> szName, pszName);
    strcpy(pNewNode -> szPhone, pszPhone);

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
            printf("[[%d]] %s \n", i, pUser->GetKey(pUser));
        }
        pTmp = pTmp -> next;
        ++i;
    }
}


int main () {
    LIST_INFO userList01 = {0};
    InitList(&userList01);

    USERDATA *pNewData = CreateUserData("SAM", "01000000000");
    InsertAtTail(&userList01, pNewData);
    PrintList(&userList01);

    ReleaseList(&userList01);
}