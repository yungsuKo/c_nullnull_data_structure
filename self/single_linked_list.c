#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
    char szData[64];
    struct NODE* next;
} NODE;

NODE *g_pHead = NULL;

void PrintList(void){
    NODE *pHead = g_pHead;
    while(pHead != NULL){
        printf("[%p]. %s \n", pHead, pHead->szData);
        pHead = pHead -> next;
    }
}
void InsertNode(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode->szData, pszData);

    if(g_pHead == NULL){
        g_pHead = pNode;
    }else{
        pNode->next = g_pHead;
        g_pHead = pNode;
    }
    printf("Insert Complete [%p] : %s \n", pNode, pNode->szData);
}
void ReleaseList(void){
    NODE *pTmp = g_pHead;
    while(pTmp != NULL){
        NODE *pDelete = pTmp;
        pTmp = pTmp -> next;
        free(pDelete);
    }
    g_pHead = NULL;

    printf("Release Complete \n");
    printf("And g_pHead Reset Complete [%p]\n", g_pHead);
}
int FindData(char *pszData){
    NODE *pTmp = g_pHead;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData)==0){
            printf("%p Found : %s \n", pTmp, pTmp->szData);
            return 1;
        }
        pTmp->next = pTmp;
    }
    return 0;
}
int Delete(char* pszData){
    NODE *pTmp = g_pHead;
    NODE *pPrev = NULL;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData)==0){
            printf("%p Delete : %s \n", pTmp, pTmp->szData);
            if(pPrev != NULL){
                pPrev->next = pTmp->next;
            }else{
                g_pHead = pTmp -> next;
            }
            return 1;   
        }
        pPrev = pTmp;
        pTmp->next = pTmp;
    }
    return 0;
}

int main(){
    InsertNode("TEST 01");
    ReleaseList();

    InsertNode("TEST 02");
    InsertNode("TEST 03");
    InsertNode("TEST 04");
    ReleaseList();
    return 0; 
}