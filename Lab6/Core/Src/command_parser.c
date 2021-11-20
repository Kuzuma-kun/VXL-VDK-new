/*
 * command_parser.c
 *
 *  Created on: Nov 20, 2021
 *      Author: ngocc
 */



enum parser_state {WAITING_START, WAITING_END};

parser_state parser_State = WAITING_START;

unsigned char command[30];
unsigned char command_index = 0;

void command_parser_fsm(char * buffer, unsigned int index) {
	switch(parser_State) {
	case WAITING_START:
		if (buffer[index-1] == '!') {
			parser_State = WAITING_END;
			command_index = 0;
		}
		break;
	case WAITING_END:
		if (buffer[index-1] == '#') {
			parser_State = WAITING_START;
			command[command_index] = '\0';
		} else {
			command[command_index++] = buffer[index-1];
			if (command_index == 30) command_index = 0;
		}
		break;
	}
}

unsigned char * getCommand() {
	return command;
}

void clear_command() {
	command[0] = '\0';
}
