/*
 * command_parser.c
 *
 *  Created on: Nov 20, 2021
 *      Author: ngocc
 */
#include "command_parser.h"
#include "main.h"


enum parser_state {WAITING_START, WAITING_END};

enum parser_state parser_State = WAITING_START;

char command[30];
unsigned char command_index = 0;
unsigned char command_done = 0;

UART_HandleTypeDef huart2;
//static uint8_t str[30] = "I was here!";

void command_parser_fsm(uint8_t * buffer, unsigned int index) {
	switch(parser_State) {
	case WAITING_START:
		if (buffer[index-1] == '!') {
//			HAL_UART_Transmit(&huart2, str, sizeof(str), sizeof(str) * 50);
			parser_State = WAITING_END;
			command_index = 0;
		}
		break;
	case WAITING_END:
		if (buffer[index-1] == '#') {
			parser_State = WAITING_START;
			command[command_index] = '\0';
			command_done = 1;
		} else {
			command[command_index++] = buffer[index-1];
			if (command_index == 30) command_index = 0;
		}
		break;
	}
}

char * getCommand() {
	return command;
}

void clear_command() {
	command[0] = '\0';
}
