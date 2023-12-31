#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <malloc.h>

// NODE 구조체 선언
typedef struct NODE {
    char szData[64];
    struct NODE* next;
    struct NODE* prev;
} NODE;

// dummy 할당
NODE* g_pHead; // 동적할당
NODE* g_pTail;
int g_nSize;

void InitList(void){
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));
    g_nSize = 0;

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    strcpy(g_pHead->szData, "Dummy Head");
    strcpy(g_pTail->szData, "Dummy Tail");

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
    printf("PrintList() sizeof : [%d], g_pHead : [%p], g_pTail : [%p] \n",g_nSize, g_pHead->next, g_pTail);
    NODE* pTmp = g_pHead;
    while(pTmp != 0){
        printf("[%p] %s [%p] \n", pTmp->prev, pTmp->szData, pTmp->next);
        pTmp = pTmp -> next;
    }

    printf("\n");
}

int InsertAtHead(const char *pszData){
    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    strcpy(pNewNode->szData, pszData);

    pNewNode->next = g_pHead->next;
    pNewNode->prev = g_pHead;
    g_pHead->next = pNewNode;
    pNewNode->next->prev = pNewNode;

    g_nSize ++;
    return g_nSize;
}

int InsertAtTail(const char *pszData){
    NODE* pNewNode = malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));

    strcpy(pNewNode->szData, pszData);

    pNewNode->next = g_pTail;
    pNewNode->prev = g_pTail->prev;
    g_pTail->prev = pNewNode;
    pNewNode->prev->next = pNewNode;

    g_nSize ++;
    return g_nSize;
}

NODE* FindNode(const char* pszData){
    NODE *pTmp = g_pHead->next; // head를 빼고 데이터 중에 검색
    while(pTmp != g_pTail){
        if (strcmp(pTmp->szData, pszData) == 0){
            return pTmp;
        }
        pTmp = pTmp->next;
    }
    return NULL;
}

int DeleteNode(const char* pszData){
    NODE *pNode=FindNode(pszData);
    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;

    printf("DeleteNode() : %p, %s \n", pNode, pNode->szData);
    free(pNode);
    return 0;
}

int InsertAt(int idx){
    return 0;
}

NODE *GetAt(int idx){
    return NULL;
}

int main() {
    InitList();
    PrintList();
    
    InsertAtTail("TEST 01");
    InsertAtTail("TEST 02");
    InsertAtTail("TEST 03");
    
    PrintList();

    printf("FindNode('TEST 01') : %p, %s \n", FindNode("TEST 01"), FindNode("TEST 01")->szData);
    printf("FindNode('TEST 02') : %p, %s \n", FindNode("TEST 02"), FindNode("TEST 02")->szData);
    DeleteNode("TEST 02");
    DeleteNode("TEST 03");
    DeleteNode("TEST 01");

    PrintList();

    InsertAtTail("TEST 01");
    InsertAtTail("TEST 02");
    InsertAtTail("TEST 03");

    PrintList();

    ReleaseList();
    return 0;
}