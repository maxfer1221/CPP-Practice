#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

float calcShortWalk(int treeCount, int **trees);
float distance(int *tree1, int *tree2);

int main() {
    int caseCount;
    scanf("%d", &caseCount);
    
    for(int i = 0; i < caseCount; i++){
        int ropeCount;
        scanf("%d", &ropeCount);
    
        // Memory Allocation and Tree Storage
        int treeCount = ropeCount * 2;
        int **trees = (int **)malloc(sizeof(int *) * treeCount);
        for(int i = 0; i < treeCount; i++){
            trees[i] = (int *)malloc(sizeof(int) * 2);
            scanf("%d %d", &trees[i][0], &trees[i][1]);
        }
        printf("%.3f", calcShortWalk(treeCount, trees));    

    }
    
    
    return 0;
}

float calcShortWalk(int treeCount, int **trees){
    // Check if final two trees
    if(treeCount == 2){
        // If they are the final two trees, return the distance between them
        return distance(trees[0], trees[1]);
    }
    
    // Starting value for smallest rope
    float ropeSmall = FLT_MAX;
    
    // Logic explanation below
    
    // Crete sub-trees
    int **newTrees = (int **)malloc(sizeof(int *) * (treeCount - 2));
    for(int j = 0; j < treeCount - 2; j++){
        newTrees[j] = (int *)malloc(sizeof(int) * 2);
    }
    
    // Large loop. Will iterate over the pair of trees: (trees[0], trees[i])
    for(int i = 1; i < treeCount; i++){
        // Inside loop. Will fill sub-trees array with every value except trees[0] and trees[i]
        for(int j = 0; j < treeCount; j++){
            if(j >= i-1){
                newTrees[j] = trees[j+2];
            } else {
                newTrees[j] = trees[j+1];
            }
        }
        
        // Rope length for 1st tree and ith tree
        float ropeLen = distance(trees[0], trees[i]);
        
        // Find shortest rope length for sub-trees
        ropeLen += calcShortWalk(treeCount - 2, newTrees);
    
        // Check if value is smallest yet
        if(ropeLen < ropeSmall){
            ropeSmall = ropeLen;
        }
    }
    
    // example:
    /*
    trees: [a, b, c, d, e, f]
    a & b -> calcShortWalk([c, d, e, f])
    a & c -> calcShortWalk([b, d, e, f])
    a & d -> calcShortWalk([b, c, e, f])
    a & e -> calcShortWalk([b, c, d, f])
    a & f -> calcShortWalk([b, c, d, e])

    trees: [c, d, e, f]             |  trees: [b, d, e, f]
    c & d -> calcShortWalk([e, f])  |  b & d -> calcShortWalk([e, f])
    c & e -> calcShortWalk([d, f])  |  b & e -> calcShortWalk([d, f])
    c & f -> calcShortWalk([e, d])  |  b & f -> calcShortWalk([d, e])
    
    trees: [e, f]
    e & f -> distance(e, f)

    */
    
    return ropeSmall;
    
}

// Simple distance formula
float distance(int *tree1, int* tree2){
    return sqrt(pow(tree1[0] - tree2[0], 2) + pow(tree1[1] - tree2[1], 2));
}
