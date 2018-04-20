/*
 * GPIO.h
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32l4xx_hal.h"
#include "config.h"



	typedef enum {
	IN, OUT
} GPIOtype;

struct GPIO {
	GPIOtype type;
	GPIO_TypeDef* bank;
	uint16_t pin;
};

int changeStateOfGPIO(struct GPIO* gpio, GPIO_PinState state);
GPIO_PinState readStateOfGPIO(struct GPIO GPIO);
#endif /* GPIO_H_ */
