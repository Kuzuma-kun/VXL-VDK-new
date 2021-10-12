/*
 * Scheduler.h
 *
 *  Created on: Oct 12, 2021
 *      Author: ngocc
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

struct SCH_Task {
	void (*pFunc)();
	uint32_t delay;
	uint32_t period;
	uint8_t ready;
};

#define MAX_TASK 	5
#define TICK_TIME 	10

struct SCH_Task extern sch_Task[MAX_TASK];

uint32_t SCH_Add_Task(void(*pFunction)(), unit32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_Update(void);
void SCH_Dispactch_Tasks(void);

#endif /* INC_SCHEDULER_H_ */
