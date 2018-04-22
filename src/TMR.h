/*
 * TMR.h
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#ifndef TMR_H_
#define TMR_H_

#include "stm32l4xx_hal.h"
#include "config.h"

typedef enum {
	OFF, ON, SHORT, LONG
} TMRstate;

struct TMR {
	uint32_t milliseconds;
	uint32_t tickConstant;
	TMRstate state;
};

void initTimer(struct TMR* tmr, uint32_t tickConstant);
void stop(struct TMR* tmr);
void tick(struct TMR* tmr);

#endif /* TMR_H_ */
