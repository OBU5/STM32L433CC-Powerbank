/*
 * buttons.c
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#include "BTN.h"

void pressedButton(struct BTN* btn, uint32_t milliseconds) {
		btn->pressedMilliseconds = milliseconds;
}

void unPressedButton(struct BTN* btn, uint32_t milliseconds) {
	btn->pressedMilliseconds = 0;
}

