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

int insertAtTail(char *pszData){
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
}

// void ReleaseList(void){
//     NODE *pTmp = g_pHead;
//     while(pTmp != NULL){
//         NODE *pDelete = pTmp;
//         pTmp = pTmp -> next;

//         printf("Delete: [%p], [%s] \n", pDelete, pDelete->szData);
//         free(pDelete);
//     }
// }

int FindData(char* pszData){
    NODE *pCur = g_pHead.next;
    NODE *pPrev = &g_pHead;
    while(pCur != NULL){
        if(strcmp(pCur->szData, pszData) == 0){
            printf("Find Data Found : %s\n", pCur->szData);
            return 1;
        }
        pCur = pCur -> next;
        pPrev = pPrev -> next;
    }
    return 0;
}

int Delete(char* pszData){
    NODE *pCur = g_pHead.next;
    NODE *pPrev = &g_pHead;
    while(pCur != NULL){
        if(strcmp(pCur->szData, pszData) == 0){
            // 삭제를 해야함.
            printf("Deleted() : %s \n", pCur->szData);
            pPrev->next = pCur->next;
            free(pCur);
            return 1;
        }
        pCur = pCur -> next;
        pPrev = pPrev -> next;
    }
    return 0;
}

int main() {
    // 리스트 연결 테스트를 하기 위한 구조
    InsertAtHead("TEST 01");
    InsertAtHead("TEST 02");
    InsertAtHead("TEST 03");
    PrintList();

    if(FindData("TEST 02")==1){
        printf("ddd test found \n");
    };
    Delete("TEST 01");
    Delete("TEST 02");
    Delete("TEST 03");

    // ReleaseList();
    return 0;
}