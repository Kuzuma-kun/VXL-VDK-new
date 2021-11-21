/*
 * uart_communication.c
 *
 *  Created on: Nov 20, 2021
 *      Author: ngocc
 */
#include "command_parser.h"
#include "main.h"
#include "uart_communication.h"
#include <string.h>
#include <stdio.h>
#include "timer.h"

ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;

enum commu {WAIT_RTS, WAIT_OK, SEND_ADC};
enum commu commu_state = WAIT_RTS;
int ADC_value = 0;
char str[20];

static uint8_t strs[30];

void uart_communication_fsm() {
	switch (commu_state) {
	case WAIT_RTS:
		if (command_done == 1) {
			command_done = 0;
			HAL_UART_Transmit(&huart2, strs, sprintf((char*)strs, "\r\ninput string is: %s \r\n", getCommand()), 1000);
			if (strcmp(getCommand(), "RTS") == 0) {
				ADC_value = HAL_ADC_GetValue(&hadc1);
//				HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC=%d#\r\n", ADC_value), 1000);
				commu_state = SEND_ADC;
//				counter_uart = TIME_OUT;
				setTimer(2,3000);
			}
		}
		break;
	case SEND_ADC:
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC=%d#\r\n", ADC_value), 1000);
			commu_state = WAIT_OK;
			break;
	case WAIT_OK:
		if (command_done == 1) {
			command_done = 0;

			HAL_UART_Transmit(&huart2, strs, sprintf((char*)strs, "\r\ninput string is: %s \r\n", getCommand()), 1000);
			if (strcmp(getCommand(), "OK") == 0) {
				commu_state = WAIT_RTS;
				stopTimer(2);
			}
		}
		if (getTimerFlag(2) == 1) {
			commu_state = SEND_ADC;
			setTimer(2, 3000);
		}

		break;
	}
}
