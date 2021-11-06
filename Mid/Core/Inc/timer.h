/*
 * timer.h
 *
 *  Created on: Nov 5, 2021
 *      Author: ngocc
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define NO_OF_TIMER 3
//change this value as interrupt time changed.
#define TIMER_CYCLE 10

void setTimer(int num_of_timer, int duration);

void initTimer(int num_of_timer);

void timer_run(int num_of_timer);

int getTimerFlag(int num_of_timer);

#endif /* INC_TIMER_H_ */
