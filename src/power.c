/*
 * charger.c
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#include "power.h"
#include "config.h"

uint8_t outVoltageStatus;
uint8_t chargerCurrentStatus;

void powerInit() {
	chargerCurrentStatus = -1;
	changeChargerCurrent();
	changeStateOfGPIO(&CHRG_nSHDN, 0);

	outVoltageStatus = -1;
	changeOutVoltage();
	changeStateOfGPIO(&FET_BuckConv_EN, 0);
}


void chargerCurrentOFF() {
	chargerCurrentStatus = 0;
	changeChargerCurrent();
}

void increaseChargerCurrent() {
	if (chargerCurrentStatus < MAX_CHARGER_CURRENT_STATUS)
		chargerCurrentStatus++;
	changeChargerCurrent();
}

void reduceChargerCurrent() {
	if (chargerCurrentStatus > 0)
		chargerCurrentStatus--;
	changeChargerCurrent();

}

void goRoundChargerCurrent() {
	if (chargerCurrentStatus < MAX_CHARGER_CURRENT_STATUS)
		chargerCurrentStatus++;
	else
		chargerCurrentStatus = 0;
	changeChargerCurrent();

}

void changeChargerCurrent() {
	switch (chargerCurrentStatus) {
	case 0:
		changeStateOfGPIO(&FET_Charger_CurrentMode, 0);
		changeStateOfGPIO(&CHRG_nSHDN, 0);
		break;
	case 1:
		changeStateOfGPIO(&FET_Charger_CurrentMode, 0);
		changeStateOfGPIO(&CHRG_nSHDN, 1);
		break;
	case 2:
		changeStateOfGPIO(&FET_Charger_CurrentMode, 1);
		changeStateOfGPIO(&CHRG_nSHDN, 1);
		break;
	}
}

void outVoltageOFF() {
	outVoltageStatus = 0;
	changeOutVoltage();
}

void increaseOutVoltage() {
	if (outVoltageStatus < MAX_OUT_VOLTAGE_STATUS)
		outVoltageStatus++;
	changeOutVoltage();
}

void reduceOutVoltage() {
	if (outVoltageStatus > 0)
		outVoltageStatus--;
	changeOutVoltage();

}

void goRoundOutVoltage() {
	if (outVoltageStatus < MAX_OUT_VOLTAGE_STATUS)
		outVoltageStatus++;
	else
		outVoltageStatus = 0;
	changeOutVoltage();

}

void changeOutVoltage() {
	switch (outVoltageStatus) {
	case 0:
		changeStateOfGPIO(&FET_BuckConv_5V, 0);
		changeStateOfGPIO(&FET_BuckConv_9V, 0);
		changeStateOfGPIO(&FET_BuckConv_12V, 0);
		changeStateOfGPIO(&FET_BuckConv_EN, 0);

		break;
	case 1:
		changeStateOfGPIO(&FET_BuckConv_5V, 1);
		changeStateOfGPIO(&FET_BuckConv_9V, 0);
		changeStateOfGPIO(&FET_BuckConv_12V, 0);
		changeStateOfGPIO(&FET_BuckConv_EN, 1);
		break;
	case 2:
		changeStateOfGPIO(&FET_BuckConv_5V, 0);
		changeStateOfGPIO(&FET_BuckConv_9V, 1);
		changeStateOfGPIO(&FET_BuckConv_12V, 0);
		changeStateOfGPIO(&FET_BuckConv_EN, 1);

		break;
	case 3:
		changeStateOfGPIO(&FET_BuckConv_5V, 0);
		changeStateOfGPIO(&FET_BuckConv_9V, 0);
		changeStateOfGPIO(&FET_BuckConv_12V, 1);
		changeStateOfGPIO(&FET_BuckConv_EN, 1);

		break;
	}
}

