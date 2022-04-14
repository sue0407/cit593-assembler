/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */

/* open_file: take in the name of the file the user of your program has specified on the command line (see lc4_loader.h for the definition of
open_file()). If the file exists, the function should return a handle to that open file, otherwise a NULL should be returned.
*/
FILE* open_file(char* file_name)
{
  FILE *my_obj_file = fopen(file_name, "rb"); // read the obj file using fopen function, save it to my_obj_file
	if(my_obj_file == NULL) { // if the file does not exist, returns NULL;
		return NULL;
	} else { // if the file exists, return the pointer to that open file 
		return my_obj_file;
	}
}

/*
parse_file:  read in and parse the contents of the open .OBJ file as well as populate the linked_list as it reads the .OBJ file. 
*/
int parse_file (FILE* my_obj_file, row_of_memory** memory)
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
  
{
  int byte_read; // intialize int byte-read
  if (byte_read = fgetc(my_obj_file) == EOF) {
    // imp0lement hash table
    // bitwise
  }
  while ((byte_read = fgetc(my_obj_file)) != EOF) {
    printf("byte_read: %d\n", byte_read); // REMOVE
    return 0;
  }

	return 2 ;
}

