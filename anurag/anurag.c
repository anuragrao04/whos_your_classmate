#include "../definitions.h"
#include <stdio.h>
#include <stdlib.h>

int get_total_number_of_nodes(tree_node_t *_class) {
  if (_class == NULL) {
    return 0;
  } else
    return 1 + get_total_number_of_nodes(_class->left) +
           get_total_number_of_nodes(_class->right);
}

void inorder(tree_node_t *node, float arr[], int *i) {
  if (node == NULL) {
    return;
  }
  inorder(node->left, arr, i);
  arr[*i] = node->cgpa;
  *i = *i + 1;
  inorder(node->right, arr, i);
}

void get_quartiles_for_a_class(tree_node_t *_class) {
  int num_nodes = get_total_number_of_nodes(_class);
  float arr[num_nodes];
  int i = 0;

  inorder(_class, arr, &i); // this will give us an inorder array of cgpas

  float q1, q2, q3;
  q1 = arr[num_nodes / 4];
  q2 = arr[num_nodes / 2];
  q3 = arr[(3 * num_nodes) / 4];

  fprintf(stdout, "Quartiles for the class are: \n");
  fprintf(stdout, "Q1: %f\n", q1);
  fprintf(stdout, "Q2: %f\n", q2);
  fprintf(stdout, "Q3: %f\n", q3);
}
