#include "../arjun/arjun.h"
#include "../definitions.h"
#include <stdio.h>
#include <stdlib.h>

void classroom_div(tree_node_t **classes, int num_classes,
                   queue_node_t *queue_head) {
  int go_forward = 1;
  while (queue_head != NULL) {
    if (go_forward) {
      for (int i = 0; i < num_classes; i++) {
        if (queue_head != NULL) {
          tree_node_t *student = queue_head->data;
          classes[i] = insert(classes[i], student);
          queue_node_t *temp = queue_head->next;
          free(queue_head);
          queue_head = temp;
        } else {
          return;
        }
      }
      go_forward = 0;
    } else {
      for (int i = num_classes - 1; i >= 0; i--) {
        if (queue_head != NULL) {
          tree_node_t *student = queue_head->data;
          classes[i] = insert(classes[i], student);
          queue_node_t *temp = queue_head->next;
          free(queue_head);
          queue_head = temp;
        } else {
          return;
        }
      }
      go_forward = 1;
    }
  }
}

int treeSize(tree_node_t *root) {
  if (root == NULL) {
    return 0;
  } else {
    return 1 + treeSize(root->left) + treeSize(root->right);
  }
}

void classroom_sizes(tree_node_t *classes[], int num_classes) {
  for (int i = 0; i < num_classes; i++) {
    int size = treeSize(classes[i]);
    printf("size of class %d is:%d\n", i, size);
  }
}
