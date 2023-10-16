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

}

void PrintList() {
    NODE *pTmp = g_pHead;
    printf("PrintList() \n");
    while(pTmp != NULL){
        printf("[%p] %s \n", pTmp, pTmp->szData);
        pTmp = pTmp -> next;
    }
};

void FindNode(char *pszData){

}

void Delete(){

}



int main(void) {
    // InsertNode("TEST 01");
    // InsertNode("TEST 02");
    // InsertNode("TEST 03");

    PrintList();
    return 0;
};