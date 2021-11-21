/*
 * timer.c
 *
 *  Created on: Nov 20, 2021
 *      Author: ngocc
 */

#define NUM_OF_TIMER 3
#define PERIOD_DURATION 10

static int timerFlag[NUM_OF_TIMER];
static int timerCounter[NUM_OF_TIMER];

void initTimer(int timer_index) {
	timerFlag[timer_index] = 1;
}

void setTimer(int timer_index, int duration) {
	timerCounter[timer_index] = duration / PERIOD_DURATION;
	timerFlag[timer_index] = 0;
}

void timer_run(int timer_index) {
	if (timerCounter[timer_index] > 0){
		timerCounter[timer_index]--;
		if (timerCounter[timer_index] == 0) {
			timerFlag[timer_index] = 1;
		}
	}
}

int getTimerFlag(int timer_index) {
	if (timer_index >= NUM_OF_TIMER) return -1;
	return timerFlag[timer_index];
}

void stopTimer(int index_timer) {
	timerFlag[index_timer] = 0;
	timerCounter[index_timer] = 0;
}


