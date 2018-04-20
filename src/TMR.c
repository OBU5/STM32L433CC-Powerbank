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
	tmr->state = OFF;
	tmr->milliseconds = 0;
}
void tick(struct TMR* tmr) {
	if (tmr->state == ON) {
		tmr->milliseconds += tmr->tickConstant;
	} else {
		tmr->state = ON;
		tmr->milliseconds = 0;
	}
}

