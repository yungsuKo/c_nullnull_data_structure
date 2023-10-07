#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <malloc.h>

typedef struct NODE {
    char szData[64];
    struct NODE* next;
} NODE;

NODE* g_pHead = NULL;

/*연결 리스트 전체 출력 함수*/
void print_list(void){
    NODE *pHead = g_pHead;
    while(pHead != NULL){
        printf("[%p]%s , next[%p]\n", pHead, pHead->szData, pHead->next);
        pHead = pHead -> next;
    }
    putchar('\n');
}

int InsertNewNode(char *pszData){
    NODE *pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    strcpy(pNode -> szData, pszData);

    if(g_pHead == NULL){
        g_pHead = pNode;
    }else {
        pNode -> next = g_pHead;
        g_pHead = pNode;
    }

    return 1;
}

void ReleaseList(void){
    NODE *pTmp = g_pHead;
    while(pTmp != NULL){
        NODE *pDelete = pTmp;
        pTmp = pTmp -> next;

        printf("Delete: [%p], [%s] \n", pDelete, pDelete->szData);
        free(pDelete);
    }
}

int FindData(char* pszData){
    NODE *pTmp = g_pHead;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData) == 0){
            printf("Find Data Found : %s\n", pTmp->szData);
            return 1;
        }
        pTmp = pTmp -> next;
    }
    return 0;
}

int Delete(char* pszData){
    NODE *pTmp = g_pHead;
    NODE *pPrev = NULL;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData) == 0){
            // 삭제를 해야함.
            printf("Deleted() : %s \n", pTmp->szData);
            if(pPrev != NULL){
                pPrev->next = pTmp->next;
            }
            else{    
                // 삭제할 데이터가 첫번째
                g_pHead = pTmp->next;
            }
            free(pTmp);
            return 1;
        }
        pPrev = pTmp;
        pTmp = pTmp -> next;
    }
    return 0;
}

int main() {
    // 리스트 연결 테스트를 하기 위한 구조
    InsertNewNode("TEST 01");
    print_list();
    InsertNewNode("TEST 02");
    print_list();
    InsertNewNode("TEST 03");
    print_list();

    FindData("TEST 02");
    Delete("TEST 01");
    Delete("TEST 02");
    Delete("TEST 03");

    ReleaseList();
    return 0;
}