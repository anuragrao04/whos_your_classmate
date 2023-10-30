// header guard
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef struct tree_node {
  char* name;
  char* srn;
  float cgpa;
  struct tree_node* left;
  struct tree_node* right;
} tree_node_t;


typedef struct queue_node {
  tree_node_t* data;
  struct queue_node* next;
} queue_node_t;


#endif
