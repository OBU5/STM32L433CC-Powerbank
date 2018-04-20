/*
 * BTN.h
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#ifndef BTN_H_
#define BTN_H_

#include "stm32l4xx_hal.h"
#include "config.h"
#include "GPIO.h"

struct BTN {
	struct GPIO* gpio;
	uint32_t pressedMilliseconds;
};

void pressedButton(struct BTN* btn, uint32_t milliseconds);
void unPressedButton(struct BTN* btn, uint32_t milliseconds);



#endif /* BTN_H_ */
