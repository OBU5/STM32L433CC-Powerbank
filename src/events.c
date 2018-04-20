/*
 * events.c
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#include"TMR.h"
#include"GPIO.h"
#include"BTN.h"
#include"ADC.h"
#include"config.h"

void pressed_BTN1() {
}
void pressed_BTN2() {
}
void pressed_BTN3() {
}
void pressed_BTN1_AND_BTN2() {
}
void pressed_BTN1_AND_BTN3() {
}
void pressed_BTN2_AND_BTN3() {
}
void pressed_BTN1_AND_BTN2_AND_BTN3() {
}

void tickButtonsTimer() {
	if (readStateOfGPIO(BTN_1) == 0)
		tick(&button1Timer);
	if (readStateOfGPIO(BTN_2) == 0)
		tick(&button2Timer);
	if (readStateOfGPIO(BTN_3) == 0)
		tick(&button3Timer);
}
void tickIntegralTimer() {
}

void checkAdapterPresence() {
}
void checkBatteryCapacity() {
}
void checkIfUsed() {
}
