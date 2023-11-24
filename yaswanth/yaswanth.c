#include "../anurag/anurag.h"
#include "../definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_to_queue(queue_node_t **queue_head, char *student_name,
                  char *student_srn, float student_gpa) {
  queue_node_t *new_node = (queue_node_t *)malloc(sizeof(queue_node_t));
  new_node->data = (tree_node_t *)malloc(sizeof(tree_node_t));

  new_node->data->name = (char *)malloc(strlen(student_name) + 1);
  strcpy(new_node->data->name, student_name);

  new_node->data->srn = (char *)malloc(strlen(student_srn) + 1);
  strcpy(new_node->data->srn, student_srn);

  new_node->data->cgpa = student_gpa;

  new_node->data->left = NULL;
  new_node->data->right = NULL;

  new_node->next = NULL;

  if (*queue_head == NULL || (*queue_head)->data->cgpa < student_gpa) {
    new_node->next = *queue_head;
    *queue_head = new_node;
  } else {
    queue_node_t *current = *queue_head;
    while (current->next != NULL && current->next->data->cgpa > student_gpa) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

typedef struct Node {
  char range[20];
  int count;
} Node;

Node nodes[20];

void roll_list(tree_node_t *root) {
  if (root != NULL) {
    roll_list(root->right);
    int index = (int)(root->cgpa * 4);
    nodes[index].count++;
    roll_list(root->left);
  }
}
