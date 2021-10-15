/*
 * software_timer.h
 *
 *  Created on: Oct 15, 2021
 *      Author: ngocc
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define NO_OF_TIMER 3
#define TIME_PERIOD	10

void initTimer(int num_of_timer);
void setTimer(int num_of_timer, int duration);
void timer_run(int num_of_timer);
int getTimerFlag(int num_of_timer);

#endif /* INC_SOFTWARE_TIMER_H_ */
