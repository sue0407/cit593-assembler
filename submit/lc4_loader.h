/************************************************************************/
/* File Name : lc4_loader.h		 										*/
/* Purpose   : This file declares the functions for lc4_loader.c		*/
/*             															*/
/*             															*/
/* Author(s) : tjf														*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */



/**
 * opens up name of the file passed in, returns a pointer
 * to the open file
 *
 * returns the FILE pointer upon success, else NULL.
 */
FILE* open_file(char* file_name) ;



/**
 * parses the given input file into an ordered (by memory address)
 * linked list with the passed in row_of_memory as the head.
 *
 * returns 0 upon successs, non-zero if an error occurs.
 */
int parse_file (FILE* my_obj_file, row_of_memory** memory) ;


/**
 * reads two bytes from my_obj_file, casts them into strings
 * to allow concat, then converts back into short unsigned int
 *
 * returns 0 upon success, non-zero if an error occurs.
 */
short unsigned int get_two_bytes (FILE* my_obj_file) ;