#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <malloc.h>

// NODE 구조체 선언
typedef struct NODE {
    char szData[64];
    
    struct NODE* left;
    struct NODE* right;
} NODE;

// dummy 할당
NODE* g_pRoot;
int g_nSize;

void ReleaseTree(NODE * pParent){
    if(pParent == NULL){
        return ;
    }
    ReleaseTree(pParent -> left);
    ReleaseTree(pParent -> right);
    printf("free(): %p, %s\n", pParent, pParent -> szData);
    free(pParent);
    g_pRoot = NULL;
}

/// @brief
/// @param  
void PrintTree(NODE * pParent) {
    if(pParent == NULL){
        return ;
    }
    PrintTree(pParent -> left);
    printf("[%p] %p, %s [%p]\n", pParent -> left, pParent, pParent -> szData, pParent -> right);
    PrintTree(pParent -> right);
    
    
    // printf("PrintList() sizeof : [%d], g_pHead : [%p], g_pTail : [%p] \n",g_nSize, g_pHead->next, g_pTail);
    // NODE* pTmp = g_pHead;
    // while(pTmp != 0){
    //     printf("[%p] %s [%p] \n", pTmp->prev, pTmp->szData, pTmp->next);
    //     pTmp = pTmp -> next;
    // }

    // printf("\n");
}

/// @brief 
/// @param pszData 
/// @return 
int InsertNode(const char *pszData){
    NODE *pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    strcpy(pNewNode->szData, pszData);
    if(g_pRoot == NULL){
        g_pRoot = pNewNode;
        return 1;
    }

    NODE *pTmp = g_pRoot;
    // 비교를 해서 왼쪽으로 갈지 오른쪽으로 갈지 결정함
    while(pTmp != NULL){
        if(strcmp(pTmp -> szData, pNewNode->szData) > 0){
            // left : 왼쪽으로 감
            if(pTmp -> left  == NULL){
                pTmp -> left = pNewNode;
                break;
            }else{
                pTmp = pTmp -> left;
                continue;
            }
        }else{
            // 오른쪽으로 감
            if(pTmp -> right  == NULL){
                pTmp -> right = pNewNode;
                break;
            }else{
                pTmp = pTmp -> right;
                continue;
            }
        }
    }
        
    return 0;
}

/// @brief 
/// @param pszData 
/// @return 
NODE* FindNode(const char* pszData){
    // NODE *pTmp = g_pHead->next; // head를 빼고 데이터 중에 검색
    // while(pTmp != g_pTail){
    //     if (strcmp(pTmp->szData, pszData) == 0){
    //         return pTmp;
    //     }
    //     pTmp = pTmp->next;
    // }
    return NULL;
}

int DeleteNode(const char* pszData){
    // 차후 구현
    return 0;
}

int main() {
    InsertNode("5번 항목");
    InsertNode("4번 항목");
    InsertNode("7번 항목");
    InsertNode("6번 항목");
    InsertNode("8번 항목");

    PrintTree(g_pRoot);
    ReleaseTree(g_pRoot);

    return 0;
}