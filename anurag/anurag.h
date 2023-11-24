#include "../definitions.h"

void get_quartiles_for_a_class(
    tree_node_t *_class); // since class is a reserved keyboard in C, we use
                          // _class instead
void roll_list_of_each_class(tree_node_t *classes[], int num_classes);

void inorder(tree_node_t *node, tree_node_t *arr[], int *i);

int get_total_number_of_nodes(tree_node_t *_class);

void get_gpa_distribution_for_a_class(tree_node_t *_class);
