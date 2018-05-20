/*
 * events.c
 *
 *  Created on: Apr 19, 2018
 *      Author: obu
 */

#include "power.h"
#include"TMR.h"
#include"GPIO.h"
#include"ADC.h"
#include"lcd.h"
#include"config.h"
#include "events.h"

#include <stdio.h>
#include <math.h>

//method that confirms setted indexes
void confirm() {
	switch (getMenuIndex()) {
	case LCD_STAT:
		switch (getSubMenuIndex()) {
		case 0:
			setLCDindex(0);
			break;
		case 1:
			setLCDindex(1);
			break;
		case 2:
			setLCDindex(2);
			break;
		case 3:
			setLCDindex(3);
			break;
		case 4:
			setLCDindex(4);
			break;
		case 5:
			setLCDindex(5);
			break;
		case 6:
			setLCDindex(6);
			break;
		}
		break;
	case OUTPUT_REG:
		switch (getSubMenuIndex()) {
		case 0:
			changeOutVoltage(_0V);
			resetMenuIndexes();
			break;
		case 1:
			changeOutVoltage(_3_3V);
			resetMenuIndexes();
			break;
		case 2:
			changeOutVoltage(_5V);
			resetMenuIndexes();
			break;
		case 3:
			changeOutVoltage(_9V);
			resetMenuIndexes();
			break;
		case 4:
			changeOutVoltage(_11_5V);
			resetMenuIndexes();
			break;
		}

		break;
	case SEND:
		break;
	case BACKLIGHT:
		switch (getSubMenuIndex()) {
		case 0:
			backlightOnForever();
			break;
		case 1:
			backlightOFF();
		}
		break;
	case TURN_OFF:
		switch (getSubMenuIndex()) {
		case 0:
			exit();
			break;
		case 1:
			resetMenuIndexes();
		}
		break;
	}

}

//method that resets menu index
void resetMenuIndexes() {
	setMenuIndex(0);
	setSubMenuIndex(0);
	set_MENU_LEVEL(0);
}

//run this method when you detect holding button1
void hold_BTN1() {
	set_MENU_LEVEL(1);
}

//run this method when you detect holding button2
void hold_BTN2() {
	set_MENU_LEVEL(1);
}

//run this method when you detect holding button3
void hold_BTN3() {
	set_MENU_LEVEL(1);
}

//run this method when you detect that button1 was pressed
void pressed_BTN1() {
	switch (getMenuLevel()) {
	case NONE:
		backlightON();
		break;
	case MENU:
		goRoundMenuIndex();
		break;
	case SUBMENU:
		goRoundSubMenuIndex();
		break;
	case SUBSUBMENU:
		break;
	}
}

//run this method when you detect that button2 was pressed
void pressed_BTN2() {
	switch (getMenuLevel()) {
	case NONE:
		backlightON();
		break;
	case MENU:
		increase_MENU_LEVEL();
		break;
	case SUBMENU:
		confirm();
		resetMenuIndexes();
		break;
	}
}

//run this method when you detect that button1 was pressed
void pressed_BTN3() {
	switch (getMenuLevel()) {
	case NONE:
		backlightON();
		break;
	case MENU:
		reduce_MENU_LEVEL();
		break;
	case SUBMENU:
		reduce_MENU_LEVEL();
		setSubMenuIndex(0);
		break;
	}
}

//this method determines about button state
void tickButtonsTimer() {
	if (readStateOfGPIO(BTN_1) == 0) {
		tick(&btn1Timer, TMR_BUTTON_CONST);
		if (btn1Timer.state == LONG) {
			hold_BTN1();
		}
	} else if (readStateOfGPIO(BTN_1) == 1 && btn1Timer.state == SHORT) {
		pressed_BTN1();
		stop(&btn1Timer);
	} else if (readStateOfGPIO(BTN_1) == 1 && btn1Timer.state == LONG) {

		stop(&btn1Timer);
	}

	if (readStateOfGPIO(BTN_2) == 0) {
		tick(&btn2Timer, TMR_BUTTON_CONST);
		if (btn2Timer.state == LONG) {
			hold_BTN2();
		}
	} else if (readStateOfGPIO(BTN_2) == 1 && btn2Timer.state == SHORT) {
		pressed_BTN2();
		stop(&btn2Timer);
	} else if (readStateOfGPIO(BTN_2) == 1 && btn2Timer.state == LONG) {
		stop(&btn2Timer);
	}

	if (readStateOfGPIO(BTN_3) == 0) {
		tick(&btn3Timer, TMR_BUTTON_CONST);
		if (btn3Timer.state == LONG) {
			hold_BTN3();
		}
	} else if (readStateOfGPIO(BTN_3) == 1 && btn3Timer.state == SHORT) {
		pressed_BTN3();
		stop(&btn3Timer);
	} else if (readStateOfGPIO(BTN_3) == 1 && btn3Timer.state == LONG) {
		stop(&btn3Timer);
	}
}

//this method helps with estimation of remaining capacity
void tickIntegralTimer() {
	//tick(&integralTimer, TMR_INTEGRAL_CONST);
	dischargingCell(&cell1, currentDischarge.currValue, 50);
	dischargingCell(&cell2, currentDischarge.currValue, 50);
	dischargingCell(&cell3, currentDischarge.currValue, 50);
	dischargingCell(&cell4, currentDischarge.currValue, 50);
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

void refreshCellsVoltage() {
	refreshCellVoltage(&cell1, (float) (voltageCell1P.currValue));

	refreshCellVoltage(&cell2,
			(float) (voltageCell2P.currValue - voltageCell1P.currValue));

	refreshCellVoltage(&cell3,
			(float) (voltageCell3P.currValue - voltageCell2P.currValue));

	refreshCellVoltage(&cell4,
			(float) (voltageCell4P.currValue - voltageCell3P.currValue));

}

void exit() {
	turnOffPowerbank();
}

float getTemperature(float ADC) {
	float tmpVal;
	//změření napětí na termistoru
	tmpVal = ADC / 3.3 * 4096;

	// Konverze změřené hodnoty na odpor termistoru
	tmpVal = 4095 / tmpVal - 1;
	tmpVal = 10000 / tmpVal;
	//Výpočet teploty podle vztahu pro beta faktor
	float temperature;
	temperature = tmpVal / 10000;         		// (R/Ro)

	temperature = log(temperature);             // ln(R/Ro)

	temperature /= 3977;                    	// 1/B * ln(R/Ro)
	temperature += 1.0 / (refTep + 273.15); 	// + (1/To)
	temperature = 1.0 / temperature;            // Převrácená hodnota
	temperature -= 273.15;                  // Převod z Kelvinů na stupně Celsia
	return temperature;
}

checkCellVoltage() {
	if (cell1.voltage < 3 || cell2.voltage < 3 || cell3.voltage < 3
			|| cell4.voltage < 3)
		exit();
}
checkCurrent() {
	if (currentDischarge.currValue > 2)
		exit();
}
checkTemperature() {
	if (tempCell.currValue > 50)
		exit();
	else if (tempBalancer.currValue > 50)
		exit();

}
checkDeviceTurnedOnTime() {
	if (OnHours > 200)
		exit();
}
