/*
 * Scheduler.c
 *
 *  Created on: Oct 12, 2021
 *      Author: ngocc
 */
//REJECT HUMANITY, RETURN TO MONNKEY
//THIS WON'T ACT AS A QUEUE, BUT THE COMPLEXITY OF THE CODE IS REDUCED
//DELETE TASK NO LONGER O(N^2), BUT O(1)
//ADD TASK IS O(N), UPDATE TOO (but better).
#include "Scheduler.h"
#include "string.h"		//needed for memmove
#include "main.h"

static struct SCH_Task sch_Task[MAX_TASK];

static uint32_t tick_time = 0; //TICK_TIME
static uint32_t min_delay = 0xffffffff;

UART_HandleTypeDef huart1;
void SCH_Init(void) {
	for(int i = 0; i < MAX_TASK; i++) {
		sch_Task[i].delay = 0;
		sch_Task[i].pFunc = NULL;
		sch_Task[i].period = 0;
		sch_Task[i].ready = 0;
	}
}

//in this add_task function, to make sure that min_delay is working, we will:
// + if tick_time (current time) + DELAY < min_delay, update min_delay
// + newtask.delay of the new task will be tick_time + DELAY, no matter this value is greater or lesser than current min_delay.
// 		because, if the value is greater, it will be subtract by SCH_Update when tick_time == min_delay.
//		or if value is lesser, this will be our new min_delay, and with SCH_Update, tick_time will soon = min_delay = newtask.delay, and task will be
// 		executed.
uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {

	//find an empty slot to put the task in.
	uint32_t index = 0;
	while ((sch_Task[index].pFunc != NULL) && (index < MAX_TASK)) {
		index++;
	}
	//if the queue is full
	if (index >= MAX_TASK) return -1;
	//if a slot is found (queue still have some space)
	if (tick_time + DELAY < min_delay) {
		min_delay = tick_time + DELAY;
	}
	sch_Task[index].delay = tick_time + DELAY;
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

//in this function, every time it's called, it will increase tick_time by TICK_TIME.
//if tick_time == min_delay, we search through the array and subtract each delay by
//the current min_delay. While searching, we also find the new min_delay.
//after update all the delay value, we have a new min_delay, and tick_time is set to 0.
//this tick_time will continue to count up till reach the min_delay, and then we go update everything again.
//remember, we only update the new_min delay value if the delay value is > 0.
//with this, we only search through the array if tick_time == min_delay.

void SCH_Update(void) {
	tick_time += TICK_TIME;
//	this 3 lines printout min_time and tick_time.
//	static char timeFormat[30];
//	int strlength = sprintf(timeFormat, "min: %ld, tick: %ld\r\n", min_delay, tick_time);
//	HAL_UART_Transmit_IT(&huart1, (uint8_t*)timeFormat, strlength);
	if (tick_time == min_delay) {		//if tick_time equal min_delay, there must be at least one task will be executed.
		uint32_t new_min = 0xffffffff;
		for(int i = 0; i < MAX_TASK; i++) {
			if (sch_Task[i].pFunc != 0) {
				sch_Task[i].delay -= min_delay;
				if (sch_Task[i].delay == 0) {
					//schedule the task to run
					sch_Task[i].ready += 1;
					if (sch_Task[i].period != 0) {
						//make the task wait for "period" and run again
						sch_Task[i].delay = sch_Task[i].period;
					} //if period == 0, we don't want it to execute again, so we do nothing here
				}
				if (sch_Task[i].delay < new_min && sch_Task[i].delay > 0) {
					new_min = sch_Task[i].delay;
				}
			}
		}
		min_delay = new_min;
		tick_time = 0;
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
			int strlength = sprintf(timeFormat, "%ld :task done\r\n", time_ms);
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


