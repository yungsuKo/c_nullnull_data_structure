#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
    char szData[30];
    struct NODE* next;
} NODE;

NODE g_Head = {0};
NODE* g_pTail = NULL;

int isEmpty(){
    if(g_pTail == NULL){
        return 1;
    }
    return 0;
}

void PrintList(void){
    NODE *pTmp = g_Head.next;
    printf("PrintList()\n \n");
    while(pTmp != NULL){
        printf("[%p] %s \n", pTmp, pTmp->szData);
        pTmp = pTmp->next;
    }
}

int InsertAtHead(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode->szData, pszData);
    if(g_pTail == NULL){
        g_pTail = pNode;
        g_Head.next = pNode;
    }else {
        pNode->next = g_Head.next;
        g_Head.next = pNode;
    }
    return 1;
}

int InsertAtTail(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode->szData, pszData);
    if(g_pTail == NULL){
        g_Head.next = pNode;
    }else{
        g_pTail->next = pNode;
    }
    g_pTail = pNode;
    
    return 1;
}

void ReleaseList(void){
    NODE *pTmp = g_Head.next;
    printf("Release() \n");
    while(pTmp != NULL){
        NODE *pDelete = pTmp;
        pTmp = pTmp -> next;
        free(pDelete);
    }
    g_Head.next = NULL;
    g_pTail = NULL;
}

NODE *FindData(char *pszData){
    NODE *pTmp = g_Head.next;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData)== 0){
            printf("Find Data Found : %s\n", pTmp->szData);
            return pTmp;
        }
        pTmp = pTmp -> next;
    }
    return 0;
}

int Delete(char *pszData){
    
}



int main(void)
{
    PrintList();
    InsertAtTail("TEST 01");
    InsertAtTail("TEST 02");
    PrintList();
    ReleaseList();
    // PrintList();
    // InsertAtHead("TEST 01");
    // InsertAtHead("TEST 02");
    // FindData("TEST 01");
    NODE *pFindData = FindData("TEST 01");
    printf("pFindData : %s \n", pFindData->szData);
    
    return 0;
}
