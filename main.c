#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "yaswanth/yaswanth.h"
#include "arjun/arjun.h"
#include "anshita/anshita.h"
#include "anurag/anurag.h"


int main(int argc, char *argv[])
{
  // defining the queue of students
  queue_node_t* queue_head = NULL;
  
  // input file containing the contents for student details
  // this file will contain the number of classes, total number of students and the students, their srn and their gpa. This can be in any order
  FILE* input_file = fopen("input_students.txt", "r");

  // defining the number of classes
  int num_classes;
  fscanf(input_file, "%d", &num_classes);
  tree_node_t* classes[num_classes];


  // defining total number of students
  int total_num_students;
  fscanf(input_file, "%d", &total_num_students);


  // inserting each student into the priority queue
  char student_name[100];
  char student_srn[16];
  float student_gpa;


  for(int i = 0; i < total_num_students; i++){
    fscanf(input_file, "%[^\n]s", student_name);
    fscanf(input_file, "%[^\n]s", student_srn);
    fscanf(input_file, "%f", &student_gpa);
    add_to_queue(&queue_head, student_name, student_srn, student_gpa);
  }
  
  // inserting each student into the tree
  classroom_div(classes, num_classes, queue_head);

  int choice;
  int section;
  while(1){
    printf("\n\n1. Roll List Of Each Class\n2. Classroom Sizes\n3. Get Quartiles For A Class\n 4. Get GPA Distribution For A Class\n0. Exit\n\nEnter Choice: ");
    scanf("%d", &choice);
    switch(choice){
      case 1:
        roll_list_of_each_class(classes, num_classes);
        break;

      case 2:
        classroom_sizes(classes, num_classes);
        break;
      
      case 3:
        printf("Enter the section: ");
        scanf("%d", &section);
        get_quartiles_for_a_class(classes[section]);
        break;

      case 4:
        printf("Enter the section: ");
        scanf("%d", &section);
        get_gpa_distribution_for_a_class(classes[section]);
        break;

      case 0:
        return EXIT_SUCCESS;
        break;
    }

  }

  return EXIT_SUCCESS;
}
