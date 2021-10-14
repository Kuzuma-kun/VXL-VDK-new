/*
 * Scheduler.c
 *
 *  Created on: Oct 12, 2021
 *      Author: ngocc
 */
//REJECT HUMANITY, RETURN TO MONNKEY
//THIS WON'T ACT AS A QUEUE, BUT THE COMPLEXITY OF THE CODE IS REDUCED
//DELETE TASK NO LONGER O(N^2), BUT O(1)
//ADD TASK IS O(N), UPDATE TOO.
#include "Scheduler.h"
#include "string.h"		//needed for memmove
#include "main.h"

static struct SCH_Task sch_Task[MAX_TASK];

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
	uint32_t index = 0;
	while ((sch_Task[index].pFunc != NULL) && (index < MAX_TASK)) {
		index++;
	}
	//if the queue is full
	if (index >= MAX_TASK) return -1;
	//if a slot is found (queue still have some space)
	sch_Task[index].delay = DELAY;
	sch_Task[index].pFunc = pFunction;
	sch_Task[index].period = PERIOD;
	sch_Task[index].ready = 0;
	return (index);
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
	if (taskID < 0 || taskID >= MAX_TASK || sch_Task[taskID].pFunc == NULL) {
		return -1;
	}
	//if index is at the end of queue, simply assign everything = 0.
	sch_Task[taskID].delay = 0;
	sch_Task[taskID].pFunc = NULL;
	sch_Task[taskID].period = 0;
	sch_Task[taskID].ready = 0;
	// return 1 if success
	return 1;
}

void SCH_Update(void) {
	for(int i = 0; i < MAX_TASK; i++) {
		if (sch_Task[i].pFunc != 0) {
			if (sch_Task[i].delay > 0) {
				sch_Task[i].delay -= TICK_TIME;
				//time is over!
				if (sch_Task[i].delay == 0) {
					sch_Task[i].ready += 1;
					if (sch_Task[i].period != 0) {
						//make the task wait for "period" and run again
						sch_Task[i].delay = sch_Task[i].period;
					} //if period == 0, we don't want it to execute again, so we do nothing here
				}
			} else {
				//if the task has delay = 0 from the beginning, we want it to be execute right away
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
	for(int i = 0; i < MAX_TASK; i++) {
		if (sch_Task[i].pFunc != NULL && sch_Task[i].ready > 0) {
			//run the task
			//dereference it first, and then run.
			(*sch_Task[i].pFunc)();
			//----------------------------------send data to terminal----------------------------------------------
			//use static so the buffer will live longer, long enough to send all data to the UART.
			static char timeFormat[30];
			uint32_t time_ms = HAL_GetTick();
			int strlength = sprintf(timeFormat, "task done: %ld\r\n", time_ms);
			HAL_UART_Transmit_IT(&huart1, (uint8_t*)timeFormat, strlength);
			//call, and then return. This function does not "block" as HAL_UART_Transmit that wait for all byte to send.
			//since _IT will end quickly, if the buffer is not static, buffer might be destroyed before all the data
			//has been send.
			//------------------------------------------------------------------------------------------------------
			sch_Task[i].ready -= 1;
			//in case the task only run once, if it's scheduled to run, we need to run it first
			//(keep the function there to run) and then only after it has done, delete the task.
			//if period = 0, we don't want it to execute again
			if (sch_Task[i].period == 0) {
				SCH_Delete_Task(i);
			}
		}
	}
}

uint32_t getTaskDelay(int index) {
	return sch_Task[index].delay;
}


