/*
 * command_parser.h
 *
 *  Created on: Nov 20, 2021
 *      Author: ngocc
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_
#include "main.h"

extern unsigned char command_done;

void command_parser_fsm(uint8_t * buffer, unsigned int index);

char * getCommand();

void clear_command();

#endif /* INC_COMMAND_PARSER_H_ */
