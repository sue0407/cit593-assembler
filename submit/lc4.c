/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {
  
/* leave plenty of room for the filename */

  char* filename = NULL; // name of the obj file

	/**
	 * main() holds the linked list &
	 * only calls functions in other files
	 */

	/* step 1: create head pointer to linked list: memory 	*/
	/* do not change this line - there should be malloc calls in main() */
	
	row_of_memory* memory = NULL ;


	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
  FILE *my_obj_file; // initialize my_obj_file
  printf ("# of arguments passed: %d\n", argc) ; // print the number of arguments passed (argc) // REMOVE
	if (argc < 2){ // if no file is passed in, print error message
    printf("error1: usage: ./lc4 <object_file.obj>"); 
  } else {
    filename = argv[1]; // else, pass the element of argv at index 1 to filename
    printf("filename: %s\n", filename); // print filename - REMOVE
		my_obj_file = open_file(filename); // call open_file function and save the file to my_obj_file
    }
  
  
	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
  int parse_file_status = parse_file (my_obj_file, &memory);
  if (parse_file_status == 2) {
    printf("error: parsing file");
    return (2);
  }


	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
  reverse_assemble(memory);

	/* step 5: call function: print_list() in lc4_memory.c 	*/
	print_list(memory);


	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
  delete_list(&memory);


	/* only return 0 if everything works properly */
	return 0 ;
}
