/*
 * events.h
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#ifndef EVENTS_H_
#define EVENTS_H_

typedef enum {
	BUTTON1, BUTTON2, BUTTON3
} buttonHandler;

#include "lcd.h"

void confirm();
void resetMenuIndexes();
void buttonChangeState(buttonHandler btnHandler);
void hold_BTN1();
void pressed_BTN1();
void pressed_BTN2();
void pressed_BTN3();
void tickButtonsTimer();
void tickIntegralTimer();

void turnOnPowerbank();

void turnOffPowerbank();

void checkAdapterPresence();
void checkBatteryCapacity();
void checkIfUsed();
void refreshCellsVoltage();

void exit();

float calculateCelsiusBySimplifiedSteinhart(float t0Celsius, float r0Nominal, float bCoefficient,
                                            float r2, float r1DigitalValue);
float getTemperature(float ADC);




#endif /* EVENTS_H_ */
