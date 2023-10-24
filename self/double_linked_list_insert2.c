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

NODE *g_pHead;
NODE *g_pTail;
int g_nSize = 0;

void InitList(){
    printf("---InitNode()--- \n");
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    strcpy(g_pHead->szData, "Dummy Head");
    strcpy(g_pTail->szData, "Dummy Tail");

    g_pHead->next = g_pTail;
    g_pTail->prev = g_pHead;

}

int InsertAtHead(char *pszData){
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    memset(newNode, 0, sizeof(NODE));
    strcpy(newNode->szData, pszData);

    newNode->prev = g_pHead;
    newNode->next = g_pHead->next;
    g_pHead->next->prev=newNode;
    g_pHead->next=newNode;

    g_nSize ++;
    return g_nSize;
}

void InsertBefore(NODE *pDstNode, char *pszData){
    NODE *prev = pDstNode -> prev;
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    memset(newNode, 0, sizeof(NODE));
    strcpy(newNode->szData, pszData);

    newNode -> prev = prev;
    newNode -> next = pDstNode;
    prev -> next = newNode;
    pDstNode->prev = newNode;

    g_nSize ++;
}

int InsertAtTail(char *pszData){
    InsertBefore(g_pTail, pszData);
    return g_nSize;
}

void PrintList(){
    NODE *pTmp = g_pHead->next;
    printf("---PrintList()--- \n");
    while(pTmp != g_pTail){
        printf("[%p] %s \n", pTmp, pTmp->szData);
        pTmp = pTmp->next;
    }
}

void ReleaseList(){
    NODE *pTmp = g_pHead;
    printf("---ReleaseList()---\n");
    while(pTmp == NULL){
        NODE *pDelete = pTmp;
        pTmp = pTmp->next;
        free(pDelete);
    }
    g_nSize = 0;
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));
    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));
    strcpy(g_pHead->szData, "Dummy Head");
    strcpy(g_pTail->szData, "Dummy Tail");
    g_pHead->next = g_pTail;
    g_pTail->prev = g_pHead;
}

NODE* FindNode(char *pszData){
    NODE *pTmp = g_pHead->next;
    printf("---FindNode()--- \n");
    while(pTmp != g_pTail){
        if(strcmp(pTmp->szData, pszData) == 0){
            return pTmp;
        }
        pTmp = pTmp->next;
    }
    return NULL;
}

int DeleteNode(char *pszData){
    NODE *pNode = FindNode(pszData);
    printf("---DeleteNode()---\n");
    pNode->prev->next= pNode->next;
    pNode->next->prev= pNode->prev;

    free(pNode);
    g_nSize --;
    return 0;
}

int InsertAt(int idx, char *pszData){
    int i = 0;
    NODE *pTmp = g_pHead->next;
    while(pTmp != NULL){
        if(i == idx){
            InsertBefore(pTmp, pszData);
            return i;
        }
        pTmp = pTmp -> next;
        i++;
    }
    return 0;
}

NODE *GetAt(int idx){
    NODE *pTmp = g_pHead->next;
    int i = 0;

    while(pTmp != NULL){
        if(i == idx){
            return pTmp;
        }
        pTmp = pTmp -> next;
        i ++;
    }
    return NULL;
}

int main(){
    InitList();
    InsertAtTail("TEST 01");
    InsertAtTail("TEST 02");
    InsertAtTail("TEST 03");
    NODE *FindOnde = FindNode("TEST 02");
    printf("FindOnde : [%p] %s \n", FindOnde, FindOnde->szData);
    PrintList();
    DeleteNode("TEST 02");
    InsertAt(1, "RENEW TEST 02");
    PrintList();

    printf("GetAt() [%p] %s \n", GetAt(1), GetAt(1)->szData);

    ReleaseList();
    return 0;
}