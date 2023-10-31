#include <stdio.h>
#include <stdlib.h>
#include "../definitions.h"

// A utility function to get the height of the tree 
int height(tree_node_t *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

tree_node_t* newNode(char *name, char*srn, float cgpa) 
{ 
    tree_node_t* node = (tree_node_t*) malloc(sizeof(tree_node_t)); 
    node->name = name;
    node->srn = srn;
    node->cgpa = cgpa;
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
}

tree_node_t *rightRotate(tree_node_t *y) 
{ 
    tree_node_t *x = y->left; 
    tree_node_t *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 
    x->height = max(height(x->left), 
                    height(x->right)) + 1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
tree_node_t *leftRotate(tree_node_t *x) 
{ 
    tree_node_t *y = x->right; 
    tree_node_t *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left),    
                    height(x->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(tree_node_t *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
}

tree_node_t* insert(tree_node_t* node, char *name, char *srn, float cgpa) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(name, srn, cgpa)); 
  
    if (cgpa <= node->cgpa) 
        node->left  = insert(node->left, name, srn, cgpa); 
    else if (cgpa > node->cgpa) 
        node->right = insert(node->right, name, srn, cgpa); 
    else // Equal cgpas are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && cgpa < node->left->cgpa) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && cgpa > node->right->cgpa) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && cgpa > node->left->cgpa) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && cgpa < node->right->cgpa) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 

void preOrder(tree_node_t *root) 
{ 
    if(root != NULL) 
    { 
        printf("%f ", root->cgpa); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 
