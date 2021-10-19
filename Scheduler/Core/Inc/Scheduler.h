/*
 * Scheduler.h
 *
 *  Created on: Oct 12, 2021
 *      Author: ngocc
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include <stdio.h>

struct SCH_Task {
	void (*pFunc)(void);
	int delay;
	int period;
	int ready;
};

#define MAX_TASK 	5
#define TICK_TIME 	10

void SCH_Init();
uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_Update(void);
void SCH_Dispactch_Tasks(void);
void SCH_Check_Ready_Task();

#endif /* INC_SCHEDULER_H_ */
