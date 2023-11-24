#include "../definitions.h"
#include "../pbPlots/pbPlots.h"
#include "../pbPlots/supportLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_total_number_of_nodes(tree_node_t *_class) {
  if (_class == NULL) {
    return 0;
  } else
    return 1 + get_total_number_of_nodes(_class->left) +
           get_total_number_of_nodes(_class->right);
}

void inorder(tree_node_t *node, tree_node_t *arr[], int *i) {
  if (node == NULL) {
    return;
  }
  inorder(node->left, arr, i);
  arr[*i] = node;
  *i = *i + 1;
  inorder(node->right, arr, i);
}

void get_quartiles_for_a_class(tree_node_t *_class) {
  int num_nodes = get_total_number_of_nodes(_class);
  tree_node_t *arr[num_nodes];
  int i = 0;

  inorder(_class, arr, &i); // this will give us an inorder array of students

  float q1, q2, q3;
  q1 = arr[num_nodes / 4]->cgpa;
  q2 = arr[num_nodes / 2]->cgpa;
  q3 = arr[(3 * num_nodes) / 4]->cgpa;

  fprintf(stdout, "Quartiles for the class are: \n");
  fprintf(stdout, "Q1: %f\n", q1);
  fprintf(stdout, "Q2: %f\n", q2);
  fprintf(stdout, "Q3: %f\n", q3);
}

int compare_names(const void *a, const void *b) {
  tree_node_t *student_a = *(tree_node_t **)a;
  tree_node_t *student_b = *(tree_node_t **)b;
  return strcmp(student_a->name, student_b->name);
}

void roll_list_of_each_class(tree_node_t *classes[], int num_classes) {
  for (int i = 0; i < num_classes; i++) {
    int num_nodes = get_total_number_of_nodes(classes[i]);
    tree_node_t *arr[num_nodes];
    int k = 0;

    inorder(classes[i], arr,
            &k); // this will give us an inorder array of students
    // but this is in the order of GPA and not name. so we need to sort it

    qsort(arr, num_nodes, sizeof(tree_node_t *), compare_names);

    printf("\n\nClass %d:\n", i);
    printf("Roll No. %-30s %-16s %-4s\n", "Name", "SRN", "CGPA");
    for (int j = 0; j < num_nodes; j++) {
      printf("%-8d %-30s %-16s %-f\n", j, arr[j]->name, arr[j]->srn,
             arr[j]->cgpa);
    }
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
