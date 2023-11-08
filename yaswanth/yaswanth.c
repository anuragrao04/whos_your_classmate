void add_to_queue(char* student_name, char* student_srn, float student_gpa)
{
 queue_node_t *new_node = (queue_node_t*)malloc(sizeof(queue_node_t));
 new_node->data = (tree_node_t*)malloc(sizeof(tree_node_t));

 new_node->data->name = (char*)malloc(strlen(student_name) + 1);
 strcpy(new_node->data->name, student_name);

 new_node->data->srn = (char*)malloc(strlen(student_srn) + 1);
 strcpy(new_node->data->srn, student_srn);

 new_node->data->cgpa = student_gpa;

 new_node->data->left = NULL;
 new_node->data->right = NULL;

 new_node->next = NULL;

 if(head == NULL || head->data->cgpa < student_gpa)
 {
   new_node->next = head;
   head = new_node;
 } 
 else
 {
   queue_node_t *current = head;
   while(current->next != NULL && current->next->data->cgpa > student_gpa)
   {
       current = current->next;
   }
   new_node->next = current->next;
   current->next = new_node;
 }
}

typedef struct Node{
    char range[20]; 
    int count; 
} Node;

Node nodes[20];


void array_creator() {

    for(int i = 0; i < 20; i++) {
        sprintf(nodes[i].range, "%.1f - %.1f", i * 0.5, (i * 0.5) + 0.5);
        nodes[i].count = 0;
    }
  
}

void roll_list(tree_node_t *root)
{
   if (root != NULL)
   { 
       roll_list(root->right);
       int index = (int)(root->GPA * 4);
       nodes[index].count++;
       roll_list(root->left);
   }
}

void get_gpa_distribution_for_a_class(tree_node_t *classes[section])
{   
    if(root==NULL)
    {
        printf("Empty Classroom");
    }
    else 
    {   
        printf("\nGPA Distribution :");
        array_creator();
        
    }
}
