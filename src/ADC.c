/*
 * ADC.c
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */
#include "ADC.h"

void initADC(char name[5], struct ADC* adc, float adjustingConstant,
		char quantiti) {
	adc->measuredTimes = 0;
	adc->currValue = 0;
	adc->minValue = 0;
	adc->maxValue = 0;
	adc->avgValue = 0;
	adc->state = INACTIVE;
	adc->adjustingConst = adjustingConstant;
	adc->quantiti = quantiti;
	int i;
	for (i = 0; i < 5; i++) {
		adc->name[i] = name[i];
	}
}

void measureADC(struct ADC* adc, uint32_t measuredValue) {
	adc->currValue = (((float) measuredValue) / ADC_DISTORTION) * V_REF
			* adc->adjustingConst;
	if (adc->state == ENABLE) {
		adc->measuredTimes++;
		adc->currValue = (measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
		adc->avgValue = (adc->avgValue + adc->currValue) / adc->measuredTimes;
		if (adc->maxValue < adc->currValue)
			adc->maxValue = adc->currValue;
		if (adc->minValue > adc->currValue)
			adc->minValue = adc->currValue;
	} else {
		adc->state = ENABLE;
		adc->measuredTimes++;
		adc->currValue = (measuredValue / ADC_DISTORTION) * V_REF;
		adc->minValue = (measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
		adc->maxValue = (measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
		adc->avgValue = (measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
	}
}
