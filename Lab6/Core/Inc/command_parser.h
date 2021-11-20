/*
 * command_parser.h
 *
 *  Created on: Nov 20, 2021
 *      Author: ngocc
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_

void command_parser_fsm(char * buffer, unsigned int index);

unsigned char * getCommand();

void clear_command();

#endif /* INC_COMMAND_PARSER_H_ */
