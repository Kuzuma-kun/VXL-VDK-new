/*
 * Scheduler.c
 *
 *  Created on: Oct 12, 2021
 *      Author: ngocc
 */
#include "Scheduler.h"
#include "string.h"		//needed for memmove
#include "main.h"

#define MAX_TASK 	5
#define TICK_TIME 	10

struct SCH_Task sch_Task[MAX_TASK];

static int queue_size = 0;

UART_HandleTypeDef huart1;
void SCH_Init(void) {
	for(int i = 0; i < MAX_TASK; i++) {
		sch_Task[i].delay = 0;
		sch_Task[i].pFunc = NULL;
		sch_Task[i].period = 0;
		sch_Task[i].ready = 0;
	}
}

uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {

	//find an empty slot to put the task in.
	if (queue_size >= MAX_TASK) return -1;
	//if a slot is found (queue still have some space)
	sch_Task[queue_size].delay = DELAY;
	sch_Task[queue_size].pFunc = pFunction;
	sch_Task[queue_size].period = PERIOD;
	sch_Task[queue_size].ready = 0;
	queue_size++;
	return (queue_size - 1);
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
	if (taskID < 0 || taskID >= queue_size || sch_Task[taskID].pFunc == NULL) {
		return -1;
	}
	//if that taskID exist, we have to move data
	//shift data to the left or if task is at the end of queue, simply initialize it with zero
	if (taskID == queue_size - 1) {
		sch_Task[taskID].delay = 0;
		sch_Task[taskID].pFunc = NULL;
		sch_Task[taskID].period = 0;
		sch_Task[taskID].ready = 0;
	} else {
		//need an address. sch_Task[taskID] do not return an address but a struct Sch_Task. that why we need &
		memmove(&sch_Task[taskID], &sch_Task[taskID + 1], (sizeof(struct SCH_Task) * (MAX_TASK - (taskID + 1))));
	}
	queue_size--;
//
	return taskID;
}

void SCH_Update(void) {
	for(int i = 0; i < queue_size; i++) {
		if (sch_Task[i].pFunc != 0) {
			if (sch_Task[i].delay > 0) {
				sch_Task[i].delay -= TICK_TIME;
			}
			else {
				sch_Task[i].ready += 1;
				if (sch_Task[i].period != 0) {
					//make the task wait for "period" and run again
					sch_Task[i].delay = sch_Task[i].period;
				} //if period == 0, we don't want it to execute again, so we do nothing here
			}
		}
	}
}

void SCH_Dispactch_Tasks(void) {
	//for loop: present FIFO, the first task will execute first.
	for(int i = 0; i < queue_size; i++) {
		if (sch_Task[i].pFunc != NULL && sch_Task[i].ready > 0) {
			//run the task
			//dereference it first, and then run.
			(*sch_Task[i].pFunc)();
			char timeFormat[30];
			uint32_t time_ms = HAL_GetTick();
			int strlength = sprintf(timeFormat, "task done: %ld\r\n", time_ms);
			HAL_UART_Transmit(&huart1, (uint8_t*)timeFormat, strlength, 10 * strlength);
			sch_Task[i].ready -= 1;
			//in case the task only run once, if it's scheduled to run, we need to run it first
			//(keep the function there to run) and then only after it has done, delete the task.
			if (sch_Task[i].period == 0) {	//if period = 0, we don't want it to execute again
				SCH_Delete_Task(i);
			}
		}
	}
}

uint32_t getTaskDelay(int index) {
	return sch_Task[index].delay;
}


