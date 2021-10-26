#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int num;
    struct node *next;
} node;

node *insertNode(node *root, int dist, int val);
node *deleteNode(node *root, int dist);
node *createGroup(int pNum);
int findGroupWinner(node *root, int pNum, int sNum, int tNum);

int main() {
    int caseNum, groupNum, pNum, sNum, tNum;
    scanf("%d", &caseNum);
    
    int *currentWinner = (int *)malloc(sizeof(int) * 2);
    currentWinner[0] = 10001;
    currentWinner[1] = 11;
    
    int *tempWinner = (int *)malloc(sizeof(int) * 2);
    
    for(int i = 0; i < caseNum; i++){
        scanf("%d", &groupNum);
        for(int j = 0; j < groupNum; j++){
            scanf("%d %d %d", &pNum, &sNum, &tNum);
            printf("Group #%d:\n", j+1);
            node *g = createGroup(pNum);
            
            // printf("LIST:\n");
            // for(int i = 0; i < 2 * pNum; i++){
            //     printf("%d\n", g -> num);
            //     g = g -> next;
            // }
            
            tempWinner[0] = findGroupWinner(g, pNum, sNum, tNum);
            tempWinner[1] = j;
            
            if(tempWinner[0] < currentWinner[0]){
                currentWinner[0] = tempWinner[0];
                currentWinner[1] = tempWinner[1];
                
                // printf("New current winner: n %d, g %d\n", currentWinner[0], currentWinner[1]);
            } else if(tempWinner[0] == currentWinner[0] && tempWinner[1] < currentWinner[1]){
                currentWinner[0] = tempWinner[0];
                currentWinner[1] = tempWinner[1];
                // printf("New current winner: n %d, g %d\n", currentWinner[0], currentWinner[1]);
            }
        }
        printf("Lottery winner is person %d from group %d.",
            currentWinner[0],
            currentWinner[1] + 1
        );
    }
}

node *insertNode(node *root, int dist, int val){
    for(int i = 0; i < dist; i++){
        root = root -> next;
    }
    node *temp = root -> next;
    
    root -> next = (node *)malloc(sizeof(node));
    root -> next -> num = val;
    root -> next -> next = temp;
    
    return root -> next;
}

node *deleteNode(node *root, int dist){
    node *prev = root;
    node *del  = root -> next;
    
    for(int i = 0; i < dist; i++){
        prev = del;
        del = del -> next;
    }
    
    prev -> next = del -> next;
    printf("%d\n", del -> num);
    free(del);
    
    return prev;
}

node *createGroup(int pNum){
    node *gRoot = (node *)malloc(sizeof(node));
    gRoot -> num = 1;
    gRoot -> next = gRoot;
    // node *ret;
    for(int i = 0; i < pNum - 1; i++){
        gRoot = insertNode(gRoot, 0, i+2);
    }
    
    return gRoot;
}

int findGroupWinner(node *root, int pNum, int sNum, int tNum){
    for(; pNum - tNum > 0; pNum--){
        root = deleteNode(root, sNum);
    }
    
    int min = root -> num;
    for(int i = 0; i < pNum - 1; i++){
        // printf("curr num:%d\n", root -> num);
        root = root -> next;
        if(root -> num < min){
            min = root -> num;
        }
    }
    
    // printf("%d", min);
    
    return min;
}
