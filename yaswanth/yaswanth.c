#include "../anurag/anurag.h"
#include "../definitions.h"
#include "../pbPlots/pbPlots.h"
#include "../pbPlots/supportLib.h"
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

void get_gpa_distribution_for_a_class(tree_node_t *_class) {
  if (_class == NULL) {
    printf("Empty Classroom");
  } else {
    int total_students = get_total_number_of_nodes(_class);
    tree_node_t *arr[total_students];
    double xs[11];
    double ys[11];
    _Bool success;
    int i = 0;
    inorder(_class, arr, &i);

    for (int j = 0; j < 11; j++) {
      xs[j] = j;
      ys[j] = 0;
    }

    for (int j = 0; j < total_students; j++) {
      ys[(int)(arr[j]->cgpa)] += 1;
    }

    StartArenaAllocator();

    RGBABitmapImageReference *canvasReference =
        CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);
    success = DrawScatterPlot(canvasReference, 600, 400, xs, 11, ys, 11,
                              errorMessage);

    if (success) {
      size_t length;
      ByteArray *pngdata = ConvertToPNG(canvasReference->image);
      WriteToFile(pngdata, "distribution.png");
      DeleteImage(canvasReference->image);
      printf("\nOpen distribution.png to see the plot!\n");
    } else {
      fprintf(stderr, "Error: ");
      for (int i = 0; i < errorMessage->stringLength; i++) {
        fprintf(stderr, "%c", errorMessage->string[i]);
      }
      fprintf(stderr, "\n");
    }

    FreeAllocations();
  }
}
