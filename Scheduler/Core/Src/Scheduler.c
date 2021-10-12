/*
 * Scheduler.c
 *
 *  Created on: Oct 12, 2021
 *      Author: ngocc
 */

struct SCH_Task {
	void (*pFunc)();
	uint32_t delay;
	uint32_t period;
	uint8_t ready;
};

#define MAX_TASK 	5
#define TICK_TIME 	10

struct SCH_Task sch_Task[MAX_TASK];


uint32_t SCH_Add_Task(void(*pFunction)(), unit32_t DELAY, uint32_t PERIOD) {
	uint32_t index;
	//find an empty slot to put the task in.
	while (sch_Task[index].pFunc != 0 && index < MAX_TASK) {
		index++;
	}
	if (index >= MAX_TASK) return -1;
	//if a slot is found:
	sch_Task[index].delay = DELAY;
	sch_Task[index].pFunc = pFunction;
	sch_Task[index].period = PERIOD;
	sch_Task[index].ready = NULL;
	return index;
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
	if (taskID < 0 || taskID >= MAX_TASK || sch_Task[taskID].pFunc == NULL) {
		return -1;
	}
	sch_Task[taskID].delay = 0;
	sch_Task[taskID].pFunc = NULL;
	sch_Task[taskID].period = 0;
	sch_Task[taskID].ready = 0;
	return taskID;
}

void SCH_Update(void) {
	for(int i = 0; i < MAX_TASK; i++) {
		if (sch_Task[i].pFunc != 0) {
			if (sch_Task[i].delay > 0) {
				sch_Task[i].delay -= TICK_TIME;
			}
			else {
				sch_Task[i].ready = 1;
			}
		}
	}
}

void SCH_Dispactch_Tasks(void) {
	//for loop: present FIFO, the first task will execute first.
	for(int i = 0; i < MAX_TASK; i++) {
		if (sch_Task[i].pFunc != NULL && sch_Task[i].ready == 1) {
			//run the task
			sch_Task[i].pFunc();
			//make the task wait for "period" and run again
			if (sch_Task[i].period != 0) {
				sch_Task[i].delay = sch_Task[i].period;
				sch_Task[i].ready = 0;
			} else {	//if period = 0, we don't want it to execute again
				SCH_Delete_Task(i);
			}
		}
	}
}


