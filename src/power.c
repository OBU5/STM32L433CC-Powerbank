/*
 * charger.c
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#include "power.h"
#include "config.h"

OutVoltageStatus outVoltageStatus;
ChargerCurrentStatus chargerCurrentStatus;
float outputVoltage;
float curretnCharge;
void checkCharger() {
	if (voltageAdapter.currValue >= 17.0) {
		if (cell1.voltage < 5)
			setChargerCurrent(_200mA);
		else
			setChargerCurrent(_0mA);
	} else {
		setChargerCurrent(_0mA);

		//setChargerCurrent(_2A);

	}
}

void initOutVoltage() {
	outputVoltage = 0;
	outVoltageStatus = -1;
	changeOutVoltage(_0V);
	changeStateOfGPIO(&FET_BuckConv_EN, 1);
}

void chargerCurrentOFF() {
	chargerCurrentStatus = 0;
	changeChargerCurrent();
}

void increaseChargerCurrent() {
	if (chargerCurrentStatus < MAX_CHARGER_CURRENT_STATUS)
		chargerCurrentStatus++;
}

void reduceChargerCurrent() {
	if (chargerCurrentStatus > 0)
		chargerCurrentStatus--;

}

void goRoundChargerCurrent() {
	if (chargerCurrentStatus < MAX_CHARGER_CURRENT_STATUS)
		chargerCurrentStatus++;
	else
		chargerCurrentStatus = 0;
	changeChargerCurrent();
}

void setChargerCurrent(ChargerCurrentStatus status) {
	if (status >= 0 && status <= MAX_CHARGER_CURRENT_STATUS)
		chargerCurrentStatus = status;
	else
		chargerCurrentStatus = 0;
	changeChargerCurrent();

}

void changeChargerCurrent() {
	switch (chargerCurrentStatus) {
	case _0mA:
		changeStateOfGPIO(&FET_Charger_CurrentMode, 0);
		changeStateOfGPIO(&CHRG_nSHDN, 0);
		curretnCharge =0;

		break;
	case _200mA:
		changeStateOfGPIO(&FET_Charger_CurrentMode, 0);
		setAdjustingConstant(&currentCharge, 0.2 / 1.2085);
		changeStateOfGPIO(&CHRG_nSHDN, 1);
		curretnCharge =0.2;
		break;
	case _2A:
		changeStateOfGPIO(&FET_Charger_CurrentMode, 1);
		setAdjustingConstant(&currentCharge, 2 / 1.2085);
		changeStateOfGPIO(&CHRG_nSHDN, 1);
		curretnCharge = 2;
		break;
	}
}

void outVoltageOFF() {
	outVoltageStatus = 0;
	changeOutVoltage(_0V);
}


void changeOutVoltage(uint16_t status) {
	switch (status) {
	case _0V:
		changeStateOfGPIO(&FET_BuckConv_5V, 0);
		changeStateOfGPIO(&FET_BuckConv_9V, 0);
		changeStateOfGPIO(&FET_BuckConv_12V, 0);
		changeStateOfGPIO(&FET_BuckConv_EN, 1);
		outputVoltage = 0;
		break;
	case _3_3V:
		changeStateOfGPIO(&FET_BuckConv_5V, 0);
		changeStateOfGPIO(&FET_BuckConv_9V, 0);
		changeStateOfGPIO(&FET_BuckConv_12V, 0);
		changeStateOfGPIO(&FET_BuckConv_EN, 0);
		outputVoltage = 3.3;
		break;
	case _5V:
		changeStateOfGPIO(&FET_BuckConv_5V, 1);
		changeStateOfGPIO(&FET_BuckConv_9V, 0);
		changeStateOfGPIO(&FET_BuckConv_12V, 0);
		changeStateOfGPIO(&FET_BuckConv_EN, 0);
		outputVoltage = 5;

		break;
	case _9V:
		changeStateOfGPIO(&FET_BuckConv_5V, 0);
		changeStateOfGPIO(&FET_BuckConv_9V, 1);
		changeStateOfGPIO(&FET_BuckConv_12V, 0);
		changeStateOfGPIO(&FET_BuckConv_EN, 0);
		outputVoltage = 9;
		break;
	case _11_5V:
		changeStateOfGPIO(&FET_BuckConv_5V, 0);
		changeStateOfGPIO(&FET_BuckConv_9V, 0);
		changeStateOfGPIO(&FET_BuckConv_12V, 1);
		changeStateOfGPIO(&FET_BuckConv_EN, 0);
		outputVoltage = 11.5;

		break;
	}
}

float getOutputVoltage() {
	return outputVoltage;
}

float getCurrentCharge(){
	return curretnCharge;
}
