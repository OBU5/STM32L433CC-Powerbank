/*
 * ADC.h
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#ifndef ADC_H_
#define ADC_H_


#include "stm32l4xx_hal.h"
#include "config.h"

typedef enum {
	INACTIVE, ACTIVE
} ADCstate;

struct ADC {
	float currValue;
	float prevValue;
	float minValue;
	float maxValue;
	float avgValue;
	ADCstate state;
	uint32_t measuredTimes;
	float adjustingConst;
	char quantiti;
	char name[5];
};


void initADC(char name[5], struct ADC* adc, float adjustingConstant, char quantiti);
void measureADC(struct ADC* adc, uint32_t measuredValue);


#endif /* U8G_ADC_H_ */
