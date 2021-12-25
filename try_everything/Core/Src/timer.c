/*
 * timer.c
 *
 *  Created on: Dec 10, 2021
 *      Author: ngocc
 */

#include "timer.h"

static int timer_flag[NUM_OF_TIMER];
static int timer_counter[NUM_OF_TIMER];

void init_timer(int index) {
	timer_flag[index] = 1;
}

void set_timer(int index, int duration, int TIME_CYCLE) {
	timer_counter[index] = duration / TIME_CYCLE;
	timer_flag[index] = 0;
}

void run_timer(int index) {
	if (timer_counter[index] > 0) {
		timer_counter[index]--;
		if (timer_counter[index] == 0) {
			timer_flag[index] = 1;
		}
	}
}

int get_timer_flag(int index) {
	return timer_flag[index];
}

void stop_timer(int index) {
	timer_flag[index] = 0;
	timer_counter[index] = 0;
}
