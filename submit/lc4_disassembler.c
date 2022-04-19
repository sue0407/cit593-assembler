/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"

int reverse_assemble (row_of_memory* memory)
{
  /* binary constants should be proceeded by a 0b as in 0b011 for decimal 3 */
  row_of_memory* searched_memory = search_opcode(memory, 0x0001);

  while (searched_memory != NULL) {
    // inspect node returned from search, translate contents field into assembly
    short unsigned int opcode = searched_memory->contents & 0b0000000000111000;
    opcode = opcode >> 3;
    char instr[5] = {};

    int reg_d = searched_memory->contents & 0b0000111000000000;
    reg_d = reg_d >> 9;
    char reg_d_str [5] = {};
    sprintf(reg_d_str, "R%d, ", reg_d);

    int reg_s = searched_memory->contents & 0b0000000111000000;
    reg_s = reg_s >> 6;
    char reg_s_str [5] = {};
    sprintf(reg_s_str, "R%d, ", reg_s);

    int reg_t = searched_memory->contents & 0b0000000000000111;
    char reg_t_str [3] = {};
    sprintf(reg_t_str, "R%d", reg_t);

    short signed int imm_val = 50; // set it to a value that isn't possible to reach

    switch(opcode) {
      case 0: // ADD
        strcpy(instr, "ADD ");
        break;
      case 1: // MUL
        strcpy(instr, "MUL ");
        break;
      case 2: // SUB
        strcpy(instr, "SUB ");
        break;
      case 3: // DIV
        strcpy(instr, "DIV ");
        break;

      // ADD IMM5
      case 4:
      case 5:
      case 6:
      case 7:
        strcpy(instr, "ADD ");
        imm_val = searched_memory->contents & 0b0000000000011111;
        if (imm_val & 0b0000000000010000) {
          short signed int negative_or = 0b1111111111110000;
          imm_val = imm_val | negative_or;
        }
        
        break;
    }
    int imm_length = 0;
    if (imm_val != 50) {
      // char* imm_val_str = malloc(sizeof(char) * 5);
       // sprintf(reg_t_str, "#%d", imm_val);
      if (imm_val < 10 & imm_val >= 0) imm_length = 1;
      else if (imm_val > 10) imm_length = 2;
      else if (imm_val < 0) imm_length = 2;
      else imm_length = 3;
    }


    int tot_str_len = strlen(instr) + strlen(reg_d_str) + strlen(reg_s_str) + 1;
    if (imm_length != 0) {
      tot_str_len = tot_str_len + imm_length + 1; // +1 for the #
    } else {
      tot_str_len = tot_str_len + strlen(reg_t_str);
    }

    char* assembly = malloc(sizeof(char) * tot_str_len);
    strcpy(assembly, instr);
    strcat(assembly, reg_d_str);
    strcat(assembly, reg_s_str);

    if ((imm_val != 50) & (imm_length != 0)) {
      char* imm_val_str = malloc(sizeof(char) * (imm_length + 1));
      sprintf(imm_val_str, "#%d", imm_val);
      strcat(assembly, imm_val_str);

      free(imm_val_str);
    } else {
      strcat(assembly, reg_t_str);
    }
    

    searched_memory->assembly = assembly;

    searched_memory = search_opcode(memory, 0x0001);
  }


	return 0 ;
}
