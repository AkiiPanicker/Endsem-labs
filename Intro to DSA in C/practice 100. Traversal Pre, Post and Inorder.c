#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

void preorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);  
    preorder(root->left);       
    preorder(root->right);     
}

void inorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);       
    printf("%d ", root->data);  
    inorder(root->right);      
}

void postorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);      
    postorder(root->right);     
    printf("%d ", root->data); 
}

int main() {
    struct node *root = NULL; 


    printf("Preorder traversal: ");
    preorder(root);  
    printf("\n");

    printf("Inorder traversal: ");
    inorder(root);   
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);  
    printf("\n");

    return 0;
}
