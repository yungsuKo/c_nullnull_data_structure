#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <malloc.h>

typedef struct NODE {
    char szData[64];
    struct NODE* next;
} NODE;

NODE g_pHead = {0}; // 동적할당

int isEmpty(){
    if(g_pHead.next == NULL)
        return 1;
    return 0;
}

/*연결 리스트 전체 출력 함수*/
void PrintList(void){
    NODE* pHead = g_pHead.next;
    while(pHead != NULL){
        printf("[%p]%s , next[%p]\n", pHead, pHead->szData, pHead->next);
        pHead = pHead->next;
    }
    putchar('\n');
}

int InsertAtHead(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode -> szData, pszData);

    if(isEmpty()){
        g_pHead.next = pNode;
    }else {
        pNode -> next = g_pHead.next;
        g_pHead.next = pNode;
    }

    return 1;
}

int InsertAtTail(char *pszData){
    // 비효율적인 구조임
    NODE *pTmp = &g_pHead;
    while(pTmp -> next != 0){
        pTmp = pTmp -> next;
    }
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode -> szData, pszData);

    pTmp->next = pNode;

    // 효율적인 구조로 만들려면
    // Double 구조로 만들어야 함.
    return 0;
}

void ReleaseList(void){
    printf("<RleaseList Start> \n");
    NODE *pTmp = g_pHead.next;
    while(pTmp != NULL){
        NODE *pDelete = pTmp;
        pTmp = pTmp -> next;

        printf("Delete: [%p], [%s] \n", pDelete, pDelete->szData);
        free(pDelete);
    }
    // g_pHead.next = 0;
}

NODE* FindData(char* pszData){
    NODE *pCur = g_pHead.next;
    NODE *pPrev = &g_pHead;
    while(pCur != NULL){
        if(strcmp(pCur->szData, pszData) == 0){
            printf("Find Data Found : %s\n", pCur->szData);
            return pPrev;
        }
        pCur = pCur -> next;
        pPrev = pPrev -> next;
    }
    return 0;
}

int Delete(char* pszData){
    // NODE *pCur = g_pHead.next;
    NODE *pPrev = FindData(pszData);
    if(pPrev != NULL){
        NODE *pDelete = pPrev -> next;
        printf("Deleted() : %s \n", pDelete->szData);
        pPrev->next = pDelete->next;
        free(pDelete);
        return 1;
    }
    return 0;
}

void PushData(char *pszData){
    InsertAtHead(pszData);
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

int main() {
    // 리스트 연결 테스트를 하기 위한 구조
    // InsertAtHead("TEST 01");
    // InsertAtHead("TEST 02");
    // InsertAtHead("TEST 03");
    // PrintList();

    // if(FindData("TEST 02")){
    //     printf("ddd test found \n");
    // };
    // Delete("TEST 01");
    // Delete("TEST 02");
    // Delete("TEST 03");

    // InsertAtTail("TEST 01");
    // InsertAtTail("TEST 02");
    // InsertAtTail("TEST 03");
    // PrintList();

    // if(FindData("TEST 02")){
    //     printf("ddd test found \n");
    // };
    // // Delete("TEST 01");
    // // Delete("TEST 02");
    // // Delete("TEST 03");

    // ReleaseList();
    // InsertAtTail("TEST 04");
    // ReleaseList();

    // Stack 테스트를 위한 코드
    PushData("TEST01");
    PushData("TEST02");
    PushData("TEST03");

    NODE node = {0};
    PopData(&node);
    printf("Pop: %s \n", node.szData);

    ReleaseList();

    return 0;
}