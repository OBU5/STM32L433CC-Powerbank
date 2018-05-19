/*
 * GPIO.c
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#include "GPIO.h"

int changeStateOfGPIO(struct GPIO* gpio, GPIO_PinState state) {
	if (gpio->type == OUT) {
		HAL_GPIO_WritePin(gpio->bank, gpio->pin, state);
		return 0;
	}
	else
		return -1;
}

void initGPIO(struct GPIO* gpio,GPIOtype type, GPIO_TypeDef* bank, uint16_t pin){
	gpio->bank = bank;
	gpio->pin = pin;
	gpio->type = type;
}

GPIO_PinState readStateOfGPIO(struct GPIO gpio) {
	return HAL_GPIO_ReadPin(gpio.bank, gpio.pin);
}

