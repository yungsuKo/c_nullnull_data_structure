#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <malloc.h>

// NODE 구조체 선언
typedef struct NODE {
    char szData[64];
    struct NODE* next;
} NODE;

// dummy 할당
NODE g_pHead = {0}; // 동적할당
NODE* g_pTail = 0;

// NODE 구조체가 비어있는지 확인하는 isEmpty 함수
int isEmpty(){
    if(g_pHead.next == NULL)
        return 1;
    return 0;
}

/*연결 리스트 전체 출력 함수*/
void PrintList(void){
    NODE* pHead = &g_pHead;
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
        // 리스트에 추가된 첫 번째 데이터 처리
        g_pTail = pNode; 
        g_pHead.next = pNode;
    }else {
        pNode -> next = g_pHead.next;
        g_pHead.next = pNode;
    }
    printf("g_pHead : %s \n",g_pHead.next->szData);

    return 1;
}

int InsertAtTail(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode -> szData, pszData);

    if(isEmpty()){
        // 리스트에 추가된 첫 번째 데이터 처리
        g_pHead.next = pNode;
    }else {
        g_pTail->next = pNode;
    }
    g_pTail = pNode; 
    

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
    g_pHead.next = 0;
    g_pTail = 0;
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
        if(pDelete == g_pTail){
            g_pTail = 0;
        }
        free(pDelete);

        return 1;
    }
    return 0;
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

int main() {
    // Queue 테스트를 위한 코드
    // InsertAtTail("TEST01");
    // InsertAtTail("TEST02");
    // InsertAtTail("TEST03");
    PrintList();
    Enqueue("TEST01");
    Enqueue("TEST02");
    Enqueue("TEST03");

    NODE node = {0};
    Dequeue(&node);
    printf("Get: %s \n", node.szData);

    ReleaseList();

    return 0;
}