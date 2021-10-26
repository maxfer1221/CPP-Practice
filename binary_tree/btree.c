// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

void createNode(node *parent, int left, int data);
node **findNeighbours(node *nodePtr, int old_val, int new_val);
void recursiveFill(node *root, int old_val, int new_val);
void print2DUtil(node *root, int space);
void print2D(node *root);

int main() {
    node *root =  (node *)malloc(sizeof(node *));
    root -> data = 10;
    root -> left = NULL;
    root -> right = NULL;
    
    createNode(root, 0, 10);
    createNode(root, 1, 10);
    createNode(root -> left, 0, 10);
    createNode(root -> left, 1, 10);
    createNode(root -> right, 0, 20);
    createNode(root -> right, 1, 10);
    createNode(root -> right -> right, 0, 10);
    createNode(root -> right -> right, 1, 20);
    createNode(root -> right -> left, 0, 10);
    createNode(root -> right -> left, 1, 10);



    print2D(root);



    recursiveFill(root, 10, 40);

    // printf("%i", root -> left -> data);
    
    print2D(root);
    
}

void createNode(node *parent, int right, int data){
    node *nn = (node *)malloc(sizeof(node *));
    nn -> data = data;
    nn -> left = NULL;
    nn -> right = NULL;
    if(right){
        parent -> right = nn;

    } else {
        parent -> left = nn;
    }
}

node **findNeighbours(node *nodePtr, int old_val, int new_val){
    node **neighbors = (node **)calloc(2, sizeof(node **));
    // printf("%i", node -> )
    // *(node) = *NULL;
    // *(node + 1) = *NULL;
    if(nodePtr -> left != NULL && nodePtr -> left -> data == old_val){
        neighbors[0] = nodePtr -> left;
    }
    if(nodePtr -> right != NULL && nodePtr -> right -> data == old_val){
        neighbors[1] = nodePtr -> right;
    }
    
    return neighbors;
}

void recursiveFill(node *root, int old_val, int new_val){
    if(root -> data == old_val){
        root -> data = new_val;
    } else {
        return;
    }
    node **tempN = findNeighbours(root, old_val, new_val);
    
    if(tempN[0] != NULL){
        recursiveFill(tempN[0], old_val, new_val);
    }
    if(tempN[1] != NULL){
        recursiveFill(tempN[1], old_val, new_val);
    }
}

void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}