/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"


/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

    /* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
		if (*head != NULL) {
      row_of_memory* temp = *head;
      while(temp->next != NULL) {
        if (temp->address == address) {
          temp->contents = contents;
          return 0;
        }
        temp = temp->next;
      }
    }
    
  /* allocate memory for a single node */
  row_of_memory *newMemory = malloc(sizeof(row_of_memory));
  if (newMemory == NULL) {
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
    row_of_memory *curr = *head;
    if (newMemory->address < curr->address) {
      newMemory->next = *head;
      *head = newMemory; 

      return 0;
    }

    if (curr->next == NULL) {
      curr->next = newMemory;
      return 0;
    }

    row_of_memory *prev = *head;
    curr = prev->next;

    while(prev->next != NULL & curr->next != NULL) {
      if (prev->address < address & curr->address > address) {
        prev->next = newMemory;
        newMemory->next = curr;
        return 0;
      }
      prev = prev->next;
      curr = curr->next;
    }

    curr->next = newMemory;
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
    /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */
    
    /* traverse linked list until node is found with matching opcode
	   AND "assembly" field of node is NULL */

	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if no matching nodes */

	return NULL ;
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */
  if (head == NULL) return;
  row_of_memory *curr = head;

	/* print out a header */
  printf("header: TODO\n");
    
  /* don't print assembly directives for non opcode 1 instructions if you are doing extra credit */

	/* traverse linked list, print contents of each node */
  while (curr != NULL) {
    printf("address: 0x%X\n", curr->address);
    printf("contents: 0x%X\n", curr->contents);
    printf("label: %s\n", curr->label);
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
    free(prev);

    prev = curr;
    curr = curr->next;
  }

	/* set the list head pointer to NULL upon deletion */
  *head = NULL;
	return 0 ;
}
