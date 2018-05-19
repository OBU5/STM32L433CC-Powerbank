/*
 * TMR.c
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#include "TMR.h"

void initTimer(struct TMR* tmr, uint32_t tickConstant) {

	tmr->state = OFF;
	tmr->milliseconds = 0;
	tmr->tickConstant = tickConstant;
}

void stop(struct TMR* tmr) {
	tmr->milliseconds = 0;
	tmr->state = OFF;
}
void start(struct TMR* tmr) {
	if (tmr->state == OFF) {
		tmr->state = ON;
		tmr->milliseconds = 0;
	}
}
void tick(struct TMR* tmr, uint32_t milliseconds) {
	if (tmr->state == OFF) {
		tmr->state = ON;
		tmr->milliseconds = milliseconds;
	} else {
		tmr->milliseconds += milliseconds;
		if (tmr->milliseconds > SHORT_TIME_LIMIT
				&& tmr->milliseconds < LONG_TIME_LIMIT) {
			tmr->state = SHORT;
		} else if (tmr->milliseconds >= LONG_TIME_LIMIT) {
			tmr->state = LONG;
		}
	}
}

