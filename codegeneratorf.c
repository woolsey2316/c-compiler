#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "lexerf.h"
#include "parserf.h"
#include "./hashmap/hashmap.h"

void traverse_tree(Node *node, int is_left, FILE *file){
  if(node == NULL){
    return;
  }
  if(strcmp(node->value, "EXIT") == 0){
    fprintf(file, "  mov rax, 60\n");
  }
  if(strcmp(node->value, "(") == 0){

  }
  if(node->type == OPERATOR){
	if(strcmp(node->value, "/") == 0){
	      fprintf(file, "  mov rax, %s\n", node->right->value);
	      fprintf(file, "  mov rbx, %s\n", node->left->value);
	      fprintf(file, "  idiv rbx\n");
	      fprintf(file, "  mov rdi, rax\n");
	      fprintf(file, "  mov rax, 60\n");
	      node->left = NULL;
	      node->right = NULL;
	    } else {
		 fprintf(file, "  mov rdi, %s\n", node->left->value);
		  Node *tmp = node;
		  while(tmp->right->type == OPERATOR){
		    printf("VASJKLDL %s\n", tmp->right->value);
		    char *oper = search(tmp->value[0])->data;
		    tmp = tmp->right;
		    fprintf(file, "  %s rdi, %s\n", oper, tmp->left->value);
		  }
		  fprintf(file, "  %s rdi, %s\n", search(tmp->value[0])->data, tmp->right->value);
          	node->left = NULL;
         	node->right = NULL;
    		} 
  }
  if(node->type == INT){
    fprintf(file, "  mov rdi, %s\n", node->value);
  }
  if(strcmp(node->value, ")") == 0){

  }
  if(strcmp(node->value, ";") == 0){
    fprintf(file, "  syscall\n");
  }
  if(is_left){

  } else {

  }
  for(size_t i = 0; node->value[i] != '\0'; i++){
    printf("%c", node->value[i]);
  }
  printf("\n");
  traverse_tree(node->left, 1, file);
  traverse_tree(node->right, 0, file);

}

int generate_code(Node *root){
	insert('-',"sub");
	insert("+","add");
	insert("*", "imul");
	insert("/","idiv");
  FILE *file = fopen("generated.asm", "w");
  assert(file != NULL && "FILE COULD NOT BE OPENED\n");

  fprintf(file, "section .text\n");
  fprintf(file, "  global _start\n\n");
  fprintf(file, "_start:\n");
  //print_tree(root, 0, "root");

  traverse_tree(root, 0, file);
  fclose(file);

  return 0;
}
