/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
get_two_bytes: helper function
*/

short unsigned int get_two_bytes(FILE* my_obj_file){
  int byte_read = fgetc(my_obj_file); // intialize int byte-read

  if (feof(my_obj_file)) {
    // handle_eof(my_obj_file);
    return 2;
  }

  char two_bytes_str [5] = {}; // initialize header_str
  char hex_str [3] = {}; // initialize hex_str length at 5 (4 hex numbers + null terminator)

  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer hex_str
  strcat(two_bytes_str, hex_str); // save the second half of hex code of two_bytes to two_bytes_str
  
  byte_read = fgetc(my_obj_file);
  if (feof(my_obj_file)) {
    // handle_eof(my_obj_file);
    return 2;
  }

  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer hex_str
  strcat(two_bytes_str, hex_str); // save the second half of hex code of two_bytes to two_bytes_str

  
  short unsigned int two_bytes = (short unsigned int)strtol(two_bytes_str, NULL, 16); // use strtol function to convert hex string to short unsigned int
  return two_bytes;
}

/*
parse_file:  read in and parse the contents of the open .OBJ file as well as populate the linked_list as it reads the .OBJ file. 
*/
int parse_file (FILE* my_obj_file, row_of_memory** memory)
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
  
{
  short unsigned int header = get_two_bytes(my_obj_file);

  printf("header: 0x%x\n", header);

  short unsigned int address = get_two_bytes(my_obj_file);

  printf("address:0x%x\n", address);

  short unsigned int n = get_two_bytes(my_obj_file);

  printf("n: 0x%x\n", n);  

  row_of_memory *list = NULL;
  add_to_list(&list, address, header);
  print_list(list);

  return (0);
}