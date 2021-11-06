/*
 * timer.c
 *
 *  Created on: Nov 5, 2021
 *      Author: ngocc
 */

#include "timer.h"

static int timer_flag[NO_OF_TIMER];
static int timer_counter[NO_OF_TIMER];

void setTimer(int num_of_timer, int duration) {
	if (num_of_timer >= NO_OF_TIMER) return;
	timer_counter[num_of_timer] = duration / TIMER_CYCLE;
	timer_flag[num_of_timer] = 0;
}

void initTimer(int num_of_timer) {
	if (num_of_timer >= NO_OF_TIMER) return;
	timer_flag[num_of_timer] = 1;
}

void timer_run(int num_of_timer) {
	if (num_of_timer >= NO_OF_TIMER) return;
	if (timer_counter[num_of_timer] > 0) {
		timer_counter[num_of_timer]--;
		if (timer_counter[num_of_timer] == 0) {
			timer_flag[num_of_timer] = 1;
		}
	}
}

int getTimerFlag(int num_of_timer) {
	if (num_of_timer >= NO_OF_TIMER) return -1;
	return timer_flag[num_of_timer];
}

