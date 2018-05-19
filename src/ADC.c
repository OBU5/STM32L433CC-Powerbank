/*
 * ADC.c
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */
#include "ADC.h"

void setAdjustingConstant(struct ADC* adc, float cons) {
	adc->adjustingConst = cons;
}

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
		adc->currValue = ((float) measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
		adc->avgValue = (adc->avgValue + adc->currValue) / 2;
		if (adc->maxValue < adc->currValue)
			adc->maxValue = adc->currValue;
		if (adc->minValue > adc->currValue)
			adc->minValue = adc->currValue;
	} else {
		adc->measuredTimes = 0;
		adc->state = ENABLE;
		adc->currValue = (((float) measuredValue) / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
		adc->minValue = ((float) measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
		adc->maxValue = ((float) measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
		adc->avgValue = ((float) measuredValue / ADC_DISTORTION) * V_REF
				* adc->adjustingConst;
	}
}
