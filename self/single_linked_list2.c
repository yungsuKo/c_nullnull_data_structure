#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char szData[30];
    struct NODE* next;
} NODE;

NODE* g_pHead = NULL;

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
    printf("[%p] %s Inserted \n", pNode, pNode->szData);
    
}

void ReleaseList(){
    NODE *pTmp = g_pHead;
    printf("ReleaseList() \n");
    while(pTmp == NULL){
        NODE *pDelete = pTmp;
        free(pDelete);
        pTmp = pTmp -> next;
    }
    g_pHead = NULL;
}

void PrintList() {
    NODE *pTmp = g_pHead;
    printf("PrintList() \n");
    while(pTmp != NULL){
        printf("[%p] %s \n", pTmp, pTmp->szData);
        pTmp = pTmp -> next;
    }
};

int FindNode(char *pszData){
    NODE *pTmp = g_pHead;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData) == 0){
            printf("Find %s : [%p] \n", pTmp->szData, pTmp);
            return 1;
        }
        pTmp = pTmp->next;
    }
    return 0;
}

void Delete(char *pszData){
    NODE *pTmp = g_pHead;
    NODE *pPrev = NULL;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData)==0){
            if(pPrev == NULL){
                g_pHead = pTmp->next;
            }else{
                pPrev->next = pTmp->next;
            }
            printf("Delete [%p] %s \n", pTmp, pTmp->szData);
            free(pTmp);
        }
        pPrev = pTmp;
        pTmp = pTmp->next;
    }
}


int main(void) {
    InsertNode("TEST 01");
    InsertNode("TEST 02");
    InsertNode("TEST 03");

    PrintList();
    Delete("TEST 01");
    
    PrintList();
    ReleaseList();
    return 0;
};