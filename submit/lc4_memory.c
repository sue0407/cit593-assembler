/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"


/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

    /* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
		if (*head != NULL) { // check if *head points to NULL
      row_of_memory* temp = *head; // if no, make temp also point to head
      while(temp->next != NULL) { // traverse the list by using while loop
        if (temp->address == address) { // check if there is already an entry for the input address
          temp->contents = contents; // if yes, update the contents using the input contents
          return 0;
        }
        temp = temp->next; // move to the next node
      }
    }
    
  /* allocate memory for a single node */
  row_of_memory* newMemory = malloc(sizeof(row_of_memory));
  if (newMemory == NULL) { // if memory allocation failed return -1
    return -1;                
  }

	/* populate fields in newly allocated node w/ address&contents, NULL for label and assembly */
  newMemory->address = address;
  newMemory->contents = contents;
  newMemory->label = NULL;
  newMemory->assembly = NULL;
  newMemory->next = NULL;

	/* if *head is NULL, node created is the new head of the list! */
  if (*head == NULL) {
    *head = newMemory;
  }

	/* otherwise, insert node into the list in address ascending order */
  else {
    row_of_memory *curr = *head; // make *curr also points to *head
    if (newMemory->address < curr->address) { // if newMemory's address < curr's address
      newMemory->next = *head; // make newMemory's next point to *head
      *head = newMemory;  // make newMemory become the head

      return 0; 
    }

    if (curr->next == NULL) { // if curr's next is NULL (only 1 node)
      curr->next = newMemory; // make curr's next point to newMemory
      return 0; 
    }

    row_of_memory *prev = *head; // create a new pointer prev which points to *head
    curr = prev->next; // make prev's next point to curr

    while(prev->next != NULL & curr->next != NULL) { // while both prev and curr are not the last node in the list
      if (prev->address < address & curr->address > address) { // if the input address is in-between prev's address and curr's address
        prev->next = newMemory; // make prev's next link to newMemory
        newMemory->next = curr; // make newMemory's next link with curr
        return 0; 
      }
      prev = prev->next; // advance prev to next node
      curr = curr->next; // advance curr to next node
    }

    curr->next = newMemory; // if curr is the last node in the list, make curr's next link to newMemory
  }

	/* return 0 for success, -1 if malloc fails */

	return 0 ;
}



/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	/* traverse linked list, searching each node for "address"  */
  row_of_memory *curr = head;

  while(curr != NULL) {
    /* return pointer to node in the list if item is found */
    if (curr->address == address) return curr;
    curr = curr->next;
  }
	
	/* return NULL if list is empty or if "address" isn't found */
	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
    if (head == NULL) return NULL;
    /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */ 

    /* traverse linked list until node is found with matching opcode
	   AND "assembly" field of node is NULL */
    row_of_memory* curr = head;

    while(curr != NULL) {
      // We just need first hex so remove all rest to do easy compare
      short unsigned int temp = curr->contents & 0b1111000000000000;
      temp = temp >> 12;
      
      if (temp == opcode & curr->assembly == NULL & curr->contents != 0) {
        if ((curr->address < 0x2000)  | ((curr->address >= 0x8000) & (curr->address < 0xA000))) {
          /* return pointer to node in the list if item is found */
          return curr;
        }
      } 
      curr= curr->next;
    }

	/* return NULL if list is empty or if no matching nodes */

	return NULL ;
}

/*
 * add spaces to a string
 */
void add_spaces(char** str_ptr, int n) {
  char space [2] = " ";
  for (int i = 0; i < n; i++) {
    strcat(*str_ptr, space);
  }
}

void print_node(row_of_memory* node, int total_length) {
  // 10 is the length of <assembly>
  if (node->assembly != NULL) {
    if (strlen(node->assembly) > 10) {
      total_length = strlen(node->assembly) - 8 + total_length;
    }
  } 
    
  char* node_str = (char*) malloc(sizeof(char) * total_length);   
    
  // label is a string or empty if NULL
  int after_label_len = 25; // this is length of <label> and the 18 spaces after
  if (node->label != NULL) {
    strcpy(node_str, node->label);
    after_label_len = after_label_len - strlen(node->label);
  } else {
    strcpy(node_str, "       ");
    after_label_len = after_label_len - 7; // 7 is length of <label>
  }
  add_spaces(&node_str, after_label_len);
    
  // address is a four-digit hex
  char* address = (char*) malloc(sizeof(char) * 11); // 10 is length of <address> + 1 for nul
  sprintf(address, "%04X      ", node->address);
  strcat(node_str, address);
  free(address);
    
  // contents is a four-digit hex or 0 if NULL
  char* contents = (char*) malloc(sizeof(char) * 11); // 10 is length of <contents> + 1 for nul
  sprintf(contents, "%04X      ", node->contents);    
  strcat(node_str, contents);
  free(contents);
    
  // assembly is a string or empty (newline) if NULL
  if (node->assembly != NULL) {
    strcat(node_str, node->assembly);
  } 
    
  printf("%s\n", node_str);
  free(node_str);
}

/*
 * print list
 */
void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */
  if (head == NULL) return;
  row_of_memory *curr = head;

	/* print out a header */
  char label_header [8] = "<label>";
  char address_header [10] = "<address>";
  char contents_header [11] = "<contents>";
  char assembly_header [11] = "<assembly>";

  int total_length = 22 + strlen(label_header) + strlen(label_header) + strlen(contents_header) + strlen(assembly_header);

  char* headers_str = (char*) malloc(sizeof(char) * total_length + 1);
    
  strcpy(headers_str, label_header);
  add_spaces(&headers_str, 18);
  strcat(headers_str, address_header);
  add_spaces(&headers_str, 1);
  strcat(headers_str, contents_header);
  add_spaces(&headers_str, 1);
  strcat(headers_str, assembly_header);
    
  printf("%s\n", headers_str);
  free(headers_str);

  /* don't print assembly directives for non opcode 1 instructions if you are doing extra credit */

	/* traverse linked list, print contents of each node */
  while (curr != NULL) {
     print_node(curr, total_length);
    curr = curr->next;
  }
	return ;
}

/*
 * delete entire linked list
 */
int delete_list    (row_of_memory** head )
{
  if (head == NULL) return 0;

  row_of_memory *prev = *head;
  row_of_memory *curr = *head;
  curr = curr->next;
	/* delete entire list node by node */
  while (curr != NULL) {
    if (prev->label != NULL) free(prev->label);
    if (prev->assembly != NULL) free(prev->assembly);
    free(prev);

    prev = curr;
    curr = curr->next;
  }
  /* free up node that weren't accounted for in while loop */
  if (prev->label != NULL) free(prev->label);
  if (prev->assembly != NULL) free(prev->assembly);
  free(prev);

	/* set the list head pointer to NULL upon deletion */
  *head = NULL;
	return 0 ;
}
