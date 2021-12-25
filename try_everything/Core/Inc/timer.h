/*
 * timer.h
 *
 *  Created on: Dec 10, 2021
 *      Author: ngocc
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define NUM_OF_TIMER	2


void init_timer(int index);
void set_timer(int index, int duration, int TIME_CYCLE);

void run_timer(int index);

int get_timer_flag(int index);

void stop_timer(int index);

#endif /* INC_TIMER_H_ */
