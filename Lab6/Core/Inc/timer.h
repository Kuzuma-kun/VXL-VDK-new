/*
 * timer.h
 *
 *  Created on: Nov 20, 2021
 *      Author: ngocc
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void initTimer(int timer_index);

void setTimer(int timer_index, int duration);

void timer_run(int timer_index);

int getTimerFlag(int timer_index);

void stopTimer(int index_timer);

#endif /* INC_TIMER_H_ */
