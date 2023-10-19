#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
    char szData[30];
    struct NODE* next;
} NODE;

NODE g_pHead = {0};
NODE *g_pTail = NULL;

int isEmpty(){
    if(g_pHead.next == NULL){
        return 1;
    }
    return 0;
}

void PrintList(void){
    NODE *pHead = &g_pHead;
    printf("PrintList() \n");
    while(pHead != NULL){
        printf("[%p] %s [%p]\n", pHead, pHead->szData, pHead->next);
        pHead = pHead -> next;
    }
    putchar('\n');
}

int InsertAtHead(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode->szData, pszData);

    if(isEmpty()){
        g_pTail = pNode;
        g_pHead.next = pNode;
    }else{
        pNode->next = g_pHead.next;
        g_pHead.next = pNode;
    }
    return 0;
}

int InsertAtTail(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode->szData, pszData);

    if(isEmpty()){
        g_pHead.next = pNode;
    }else{
        g_pTail->next = pNode;
    }
    g_pTail = pNode;
    printf("[%p] %s Inserted At Tail \n", pNode, pNode->szData);
    return 0;
}

void ReleaseList(void){
    NODE *pHead = g_pHead.next;
    while(pHead!=NULL){
        NODE* pDelete = pHead;
        printf("Delete [%p] %s \n", pDelete, pDelete->szData);
        pHead = pHead -> next;
        free(pDelete);
    }
    g_pHead.next = 0;
    g_pTail = 0;
    printf("Release complete\n");
    putchar('\n');
}

NODE *FindData(char *pszData){
    return NULL;
}
int Delete(char *pszData){
    return 1;
}

void Enqueue(char *pszData){
    InsertAtTail(pszData);
}

int PopData(NODE *pPopNode){
    NODE *sfp = g_pHead.next;
    if(isEmpty()){
        return 0;
    }
    memcpy(pPopNode, sfp, sizeof(NODE));
    g_pHead.next = sfp->next;
    free(sfp);
    return 1;
}

int Dequeue(NODE *pGetData){
    return PopData(pGetData);
}

int main(void)
{
    Enqueue("TEST 01");
    Enqueue("TEST 02");
    PrintList();

    NODE example = {0};
    Dequeue(&example);
    printf("[%p] %s \n", &example, example.szData);
    return 0;
}
