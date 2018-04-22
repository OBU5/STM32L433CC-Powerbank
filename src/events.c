/*
 * events.c
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#include"TMR.h"
#include"GPIO.h"
#include"ADC.h"
#include"config.h"

#include "events.h"
void buttonChangeState(buttonHandler btnHandler) {
	switch (btnHandler) {
	case BUTTON1:
		if (readStateOfGPIO(BTN_1) == 0) {
			//pressed button 1
			start(&btn1Timer);
		} else {
			//unpressed button 1

			//unpressed button 1, but pressed button 2
			if (readStateOfGPIO(BTN_2) == 0)
				pressed_BTN1_AND_BTN2();

			//unpressed button 1, but pressed button 3
			else if (readStateOfGPIO(BTN_3) == 0)
				pressed_BTN1_AND_BTN3();

			//unpressed button 1, but pressed button 2 and 3
			else if (readStateOfGPIO(BTN_2) == 0 && readStateOfGPIO(BTN_3) == 0)
				pressed_BTN1_AND_BTN2_AND_BTN3();

			//unpressed button 1 and buttons 2 and 3
			else if (readStateOfGPIO(BTN_1) == 1 && readStateOfGPIO(BTN_2) == 1
					&& readStateOfGPIO(BTN_3) == 1)
				pressed_BTN1();

			stop(&btn1Timer);
		}
		break;
	case BUTTON2:
		if (readStateOfGPIO(BTN_2) == 0) {
			//pressed button 2
			start(&btn2Timer);
		} else {
			//unpressed button 2

			//unpressed button 2, but pressed button 1
			if (readStateOfGPIO(BTN_1) == 0)
				pressed_BTN1_AND_BTN2();

			//unpressed button 2, but pressed button 3
			else if (readStateOfGPIO(BTN_3) == 0)
				pressed_BTN2_AND_BTN3();

			//unpressed button 2, but pressed button 1 and 3
			else if (readStateOfGPIO(BTN_1) == 0 && readStateOfGPIO(BTN_3) == 0)
				pressed_BTN1_AND_BTN2_AND_BTN3();

			//unpressed button 2 and buttons 1 and 3
			else if (readStateOfGPIO(BTN_1) == 1 && readStateOfGPIO(BTN_2) == 1
					&& readStateOfGPIO(BTN_3) == 1)
				pressed_BTN2();
		}
		break;
	case BUTTON3:
		if (readStateOfGPIO(BTN_3) == 0) {
			//pressed button 3
			start(&btn3Timer);
		} else {
			//unpressed button 3

			//unpressed button 3, but pressed button 1
			if (readStateOfGPIO(BTN_1) == 0)
				pressed_BTN1_AND_BTN3();

			//unpressed button 3, but pressed button 2
			else if (readStateOfGPIO(BTN_2) == 0)
				pressed_BTN2_AND_BTN3();

			//unpressed button 2, but pressed button 1 and 3
			else if (readStateOfGPIO(BTN_1) == 0 && readStateOfGPIO(BTN_2) == 0)
				pressed_BTN1_AND_BTN2_AND_BTN3();

			//unpressed button 2 and buttons 1 and 3
			else if (readStateOfGPIO(BTN_1) == 1 && readStateOfGPIO(BTN_2) == 1
					&& readStateOfGPIO(BTN_3) == 1)
				pressed_BTN3();
		}
		break;
	}
}
void hold_BTN1() {
	turnOffPowerbank();
}
void hold_BTN2() {
	setLCDstatus(0);
}
void hold_BTN3() {
	setOutVoltage(0);
}

void pressed_BTN1() {
	toogleBacklight();
}
void pressed_BTN2() {
	goRoundLCDstatus();
}
void pressed_BTN3() {
	goRoundOutVoltage();
}

void pressed_BTN1_AND_BTN2() {
	toogleBacklight();
}
void pressed_BTN1_AND_BTN3() {
	toogleBacklight();
}
void pressed_BTN2_AND_BTN3() {
	toogleBacklight();
}
void pressed_BTN1_AND_BTN2_AND_BTN3() {
	turnOnPowerbank();
}

void tickButtonsTimer() {
	if (readStateOfGPIO(BTN_1) == 0)
		tick(&btn1Timer);
	if (readStateOfGPIO(BTN_2) == 0)
		tick(&btn2Timer);
	if (readStateOfGPIO(BTN_3) == 0)
		tick(&btn3Timer);
}
void tickIntegralTimer() {
	tick(&integralTimer);

}

void turnOnPowerbank() {
	changeStateOfGPIO(&FET_HoldOn, 1);
	HAL_Delay(1);
}

void turnOffPowerbank() {
	changeStateOfGPIO(&FET_HoldOn, 0);
}

void checkAdapterPresence() {
}
void checkBatteryCapacity() {
}
void checkIfUsed() {
}

refreshCellsVoltage() {
	if (refreshCellVoltage(cell1, voltageCell1P.currValue) != -1) {
	} else {
		exit();
	}
	if (refreshCellVoltage(cell1,
			voltageCell2P.currValue - voltageCell1P.currValue) != -1) {
	} else {
		exit();
	}
	if (refreshCellVoltage(cell1,
			voltageCell3P.currValue - voltageCell2P.currValue) != -1) {
	} else {
		exit();
	}
	if (refreshCellVoltage(cell1,
			voltageCell4P.currValue - voltageCell3P.currValue) != -1) {
	} else {
		exit();
	}
}

void exit() {

}
