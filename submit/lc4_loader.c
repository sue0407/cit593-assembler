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
parse_file:  read in and parse the contents of the open .OBJ file as well as populate the linked_list as it reads the .OBJ file. 
*/
int parse_file (FILE* my_obj_file, row_of_memory** memory)
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
  
{
  int byte_read; // intialize int byte-read
 
  if ((byte_read = fgetc(my_obj_file)) == EOF) { // check 
      fclose(my_obj_file);
  // implement free memory
    printf("error: EOF error.");
    return 2;
  } 

  // below is get_header section
  char header_str [5] = {}; // initialize header_str
  char* hex_str; // initialize hex_str length at 5 (4 hex numbers + null terminator)
  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer hex_str

  strcat(header_str, hex_str); // save the first half of hex code of header to header_str
  
  byte_read = fgetc(my_obj_file);
  printf("byte_read %d\n",byte_read);

  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer hex_str

  strcat(header_str, hex_str); // save the second half of hex code of header to header_str

  unsigned short int header = (short unsigned int)strtol(header_str, NULL, 16); // use strtol function to convert hex string to short unsigned int

  printf("0x%x\n", header);

  // below is get_address section
  char address_str [5] = {}; // initialize address_str
  byte_read = fgetc(my_obj_file); // get the next byte
  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer address_str

  strcat(address_str, hex_str); // save the first half of hex code of address to address_str

  byte_read = fgetc(my_obj_file); // get the next byte
  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer hex_str

  strcat(address_str, hex_str); // save the second half of hex code of address to address_str

  unsigned short int address = (short unsigned int)strtol(address_str, NULL, 16); // use strtol function to convert hex string to short unsigned int

  printf("0x%x\n", address);

  // below is get_n section
  char n_str [5] = {}; // initialize n_str
  byte_read = fgetc(my_obj_file); // get the next byte
  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer address_str

  strcat(n_str, hex_str); // save the first half of hex code of address to n_str

  byte_read = fgetc(my_obj_file); // get the next byte
  sprintf(hex_str, "%x", byte_read); // use sprintf function to send formatted hex representation to a string pointer hex_str

  strcat(n_str, hex_str); // save the second half of hex code of address to n_str

  unsigned short int n = (short unsigned int)strtol(n_str, NULL, 16); // use strtol function to convert hex string to short unsigned int

  printf("0x%x\n", n);  

  return (0);

/* TODO: Fix errors related to this, please ignore until then

short unsigned int hex_read = get_two_bytes(my_obj_file); // read the first hex (2 bytes) from the file
if (hex_read == NULL) return 2;
short unsigned int header = hex_read; // assign hex_read to header

hex_read = get_two_bytes(my_obj_file); // read the next hex (2 bytes) from the file
if (hex_read == NULL) return 2;
short unsigned int address = hex_read; // assign hex_read to address

hex_read = get_two_bytes(my_obj_file); // read the next hex (2 bytes) from the file
if (hex_read == NULL) return 2;
short unsigned int n = hex_read; // assign hex_read to n

 return (0);
*/
}


/*
Bottom is all helper functions to make the code cleaner and easier to make
Please ignore for now because they have errors


handle_eof: helper function
*//*
void* handle_eof(FILE* my_obj_file){
  fclose(my_obj_file);
  // implement free memory
  printf("error: EOF error.");
}*/


/*
get_two_bytes: helper function
*/
/*
short unsigned int get_two_bytes(FILE* my_obj_file){
  int byte_read = fgetc(my_obj_file); // intialize int byte-read
 
  if (byte_read == EOF) { // check 
    handle_eof(my_obj_file);
    return NULL;
  } 

  char* hex_str = ""; // initialize hex_str
  strcat(hex_str, num_to_hexstr(byte_read)); // save the first half of hex code of header to header_str
  
  if (byte_read == EOF) { // check 
    handle_eof(my_obj_file);
    return NULL;
  } 
  strcat(hex_str, num_to_hexstr(byte_read)); // save the second half of hex code of header to header_str
  
  unsigned short int two_bytes = str_to_num(hex_str); // convert hex_str to short unsigned int type
  return two_bytes;
}

*/

/*
int_to_hexstr: helper function to cast an int to hex string
input: an int
return: a hex string
*/
/*
char* num_to_hexstr(int num){
  char* hex_str; // initialize hex_str length at 5 (4 hex numbers + null terminator)
  sprintf(hex_str, "%x", num); // use sprintf function to send formatted hex representation to a string pointer hex_str
  puts(hex_str); // write to hex_str
  return hex_str;
}
*/
/*
str_to_num: helper function to convert a hex string to short unsigned int
*/
/*
short unsigned int str_to_num(char *hex_str){
  return (short unsigned int)strtol(hex_str, NULL, 16); // use strtol function to convert hex string to short unsigned int
}

*/

