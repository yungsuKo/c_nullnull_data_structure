// double linked list를 사용하는 이유
// 앞뒤에서 조회할 수 있음
// double linked list가 갖는 장점은
    // 하나의 node에서 prev, next값 2개를 모두 갖고 있기 때문에
    // 굳이 이전의 값에 대한 node를 넘겨줄 필요가 없음

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char szData[20];
    struct NODE *prev;
    struct NODE *next;
} NODE;

NODE *g_pHead = NULL;
NODE *g_pTail = NULL;
int g_nSize;

void InitNode(void){
    g_pHead = (NODE *)malloc(sizeof(NODE));
    g_pTail = (NODE *)malloc(sizeof(NODE));
    g_nSize = 0;

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    strcpy(g_pHead->szData, "Dummy Head");
    strcpy(g_pTail->szData, "Dummy Tail");

    g_pHead -> next= g_pTail;
    g_pTail -> prev= g_pHead;
    puts("InitNode() \n");
}

void ReleaseList(){
    NODE *pTmp = g_pHead;
    while(pTmp != NULL){
        NODE *pDelete = pTmp;
        pTmp = pTmp->next;
        free(pDelete);
    }
    g_pHead = (NODE *)malloc(sizeof(NODE));
    g_pTail = (NODE *)malloc(sizeof(NODE));
    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));
    g_pHead -> next= g_pTail;
    g_pTail -> prev= g_pHead;
    g_nSize = 0;
}

void PrintList(){
    NODE *pTmp = g_pHead;
    while(pTmp != 0){
        printf("[%p] %s \n", pTmp, pTmp->szData);
        pTmp = pTmp -> next;
    }
    puts("\n");
}

int InsertAtHead(char *pszData){
    NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode,0,sizeof(NODE));
    strcpy(pNewNode->szData, pszData);
    pNewNode->next=g_pHead->next;
    pNewNode->prev=g_pHead;
    g_pHead->next->prev= pNewNode;
    g_pHead->next= pNewNode;
    
    printf("InsertAtHead() [%p] %s \n", pNewNode, pNewNode->szData);

    g_nSize ++;
    return g_nSize;
}

int InsertAtTail(char *pszData){
    NODE *pNewNode = (NODE *)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    strcpy(pNewNode->szData, pszData);

    pNewNode->next = g_pTail;
    pNewNode->prev = g_pTail->prev;
    g_pTail->prev = pNewNode;
    pNewNode->prev->next = pNewNode;

    printf("InsertAtTail() [%p] %s \n", pNewNode, pNewNode->szData);
    g_nSize ++;
    return g_nSize;
}

NODE *FindData(char *pszData){
    NODE *findNode = g_pHead->next;
    while(findNode != g_pTail){
        if(strcmp(findNode->szData, pszData) == 0){
            return findNode;
        }
        findNode = findNode -> next;
    }
    return 0;
}

void Delete(char *pszData){
    NODE *pNode = FindData(pszData);
    if(pNode == 0){
        printf("Nothing Deleted \n");
    }else {
        NODE *pDelete = pNode;
        pNode -> prev -> next = pNode -> next;
        pNode -> next -> prev = pNode -> prev;
        printf("Deleted [%p] %s \n", pDelete, pDelete->szData);
        free(pDelete);
    }
}



int main(){
    InitNode();
    InsertAtTail("TEST 01");
    InsertAtTail("TEST 02");
    InsertAtTail("TEST 03");

    printf("FindData [%p] %s \n", FindData("TEST 01"), FindData("TEST 02")->szData);

    PrintList();

    Delete("TEST 03");

    PrintList();

    ReleaseList();
    return 0;
}