#include "../definitions.h"
#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

// A utility function to get the height of the tree
int height(tree_node_t *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// To create a new student node for the bin  tree.
tree_node_t *newNode(char *name, char *srn, float cgpa) {
  tree_node_t *node = (tree_node_t *)malloc(sizeof(tree_node_t));
  node->name = name;
  node->srn = srn;
  node->cgpa = cgpa;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; // new node is initially added at leaf
  return (node);
}

tree_node_t *rightRotate(tree_node_t *y) {
  tree_node_t *x = y->left;
  tree_node_t *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  // Return new root
  return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
tree_node_t *leftRotate(tree_node_t *x) {
  tree_node_t *y = x->right;
  tree_node_t *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  //  Update heights
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  // Return new root
  return y;
}

// Get Balance factor of node N
int getBalance(tree_node_t *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// The parameters are the root node of class and student node
tree_node_t *insert(tree_node_t *root, tree_node_t *student) {
  /* 1.  Perform the normal BST insertion */
  if (root == NULL)
    return (student);

  if (student->cgpa <= root->cgpa)
    root->left = insert(root->left, student);
  else if (student->cgpa > root->cgpa)
    root->right = insert(root->right, student);
  else // Equal cgpas are not allowed in BST
    return root;

  /* 2. Update height of this ancestor root */
  root->height = 1 + max(height(root->left), height(root->right));

  /* 3. Get the balance factor of this ancestor
        root to check whether this root became
        unbalanced */
  int balance = getBalance(root);

  // If this root becomes unbalanced, then
  // there are 4 cases

  // Left Left Case
  if (balance > 1 && student->cgpa < root->left->cgpa)
    return rightRotate(root);

  // Right Right Case
  if (balance < -1 && student->cgpa > root->right->cgpa)
    return leftRotate(root);

  // Left Right Case
  if (balance > 1 && student->cgpa > root->left->cgpa) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Right Left Case
  if (balance < -1 && student->cgpa < root->right->cgpa) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  /* return the (unchanged) root pointer */
  return root;
}

// Display as diagram
void display_roll_list(tree_node_t *root, int space) {
  // Base case
  if (root == NULL)
    return;

  // Increase distance between levels
  space += COUNT;

  // Process right child first
  display_roll_list(root->right, space);

  // Print current node after space
  // count
  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  printf("%f\n", root->cgpa);

  // Process left child
  display_roll_list(root->left, space);
}

// Display for every class
void roll_list_of_each_class(tree_node_t *classes[], int num_classes) {
  for (int i = 0; i < num_classes; i++) {
    printf("Class %d:\n", i);
    // roll_list(classes[i]);
    display_roll_list(classes[i], 0);
    printf("\n\n");
  }
}

// int main(){
//     tree_node_t *root = NULL;
//     tree_node_t *root2 = NULL;
//
//     // Example data to test
//     root = insert(root, newNode("Arjun", "PES095", 8.8));
//     root = insert(root, newNode("Arjun", "PES096", 4));
//     root = insert(root, newNode("Arjun", "PES097", 2.8));
//     root = insert(root, newNode("Arjun", "PES098", 3.8));
//     root = insert(root, newNode("Arjun", "PES099", 6.8));
//     root = insert(root, newNode("Arjun", "PES100", 7.8));
//     // display_roll_list(root, 0);
//     root2 = insert(root2, newNode("Arjun", "PES095", 8.8));
//     root2 = insert(root2, newNode("Arjun", "PES096", 4));
//     root2 = insert(root2, newNode("Arjun", "PES097", 2.8));
//     root2 = insert(root2, newNode("Arjun", "PES098", 3.8));
//     root2 = insert(root2, newNode("Arjun", "PES099", 6.8));
//     root2 = insert(root2, newNode("Arjun", "PES100", 7.8));
//
//     tree_node_t* classes[2];
//     classes[0] = root;
//     classes[1] = root;
//
//     roll_list_of_each_class(classes, 2);
// }
