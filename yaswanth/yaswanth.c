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
