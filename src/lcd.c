/*
 * lcd.c
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */
#include "config.h"
#include "lcd.h"
#include "u8g/u8g.h"
#include "u8g/u8g_arm.h"
u8g_t lcd;

char tmpForSprintf[10];
uint8_t lcdStatus;

void initLCD() {
	changeStateOfGPIO(&LCD_RST, 1);
	HAL_Delay(1);
	changeStateOfGPIO(&LCD_RST, 0);
	HAL_Delay(1);
	changeStateOfGPIO(&LCD_RST, 1);
	HAL_Delay(1);

	u8g_InitComFn(&lcd, &u8g_dev_uc1701_dogs102_hw_spi, u8g_com_hw_spi_fn);

}

void toogleBacklight() {
	if (readStateOfGPIO(LCD_BL) == 0)
		changeStateOfGPIO(&LCD_BL, 1);
	else
		changeStateOfGPIO(&LCD_BL, 0);
	HAL_Delay(1);
}

void printADCFloat(char adcName[5], float adcValue, char adcQuantiti,
		uint16_t x, uint16_t y) {
	sprintf(tmpForSprintf, "%s=%2.3f%c", adcName, adcValue, adcQuantiti);
	u8g_DrawStr(&lcd, x, y, tmpForSprintf);
}

void printADCInt(char adcName[5], float adcValue, char adcQuantiti, uint16_t x,
		uint16_t y) {
	sprintf(tmpForSprintf, "%s=%2d%c", adcName, adcValue, adcQuantiti);
	u8g_DrawStr(&lcd, x, y, tmpForSprintf);
}

void printCellFloat(struct cell cell, uint16_t x, uint16_t y) {
	sprintf(tmpForSprintf, "%s=%2.3f %c", cell.name, cell.voltage, "V");
	u8g_DrawStr(&lcd, x, y, tmpForSprintf);
}

void writeCurrentOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		printADCFloat(voltageCell1P.name, voltageCell1P.currValue,
				voltageCell1P.quantiti, 0, 10);
		printADCFloat(voltageCell2P.name, voltageCell2P.currValue,
				voltageCell2P.quantiti, 0, 20);
		printADCFloat(voltageCell3P.name, voltageCell3P.currValue,
				voltageCell3P.quantiti, 0, 30);
		printADCFloat(voltageCell4P.name, voltageCell4P.currValue,
				voltageCell4P.quantiti, 0, 40);
		printADCFloat(currentCharge.name, currentCharge.currValue,
				currentCharge.quantiti, 0, 50);
		printADCFloat(currentDischarge.name, currentDischarge.currValue,
				currentDischarge.quantiti, 0, 60);

		printADCInt(voltageAdapter.name, voltageAdapter.currValue,
				voltageAdapter.quantiti, 65, 10);
		printADCInt(tempCell.name, tempCell.currValue, tempCell.quantiti, 65,
				20);
		printADCInt(tempBalancer.name, tempBalancer.currValue,
				tempBalancer.quantiti, 65, 30);
		printADCInt(tempMCU.name, tempMCU.currValue, tempMCU.quantiti, 65, 40);

	} while (u8g_NextPage(&lcd));
}

void writeAverageOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		printADCFloat(voltageCell1P.name, voltageCell1P.avgValue,
				voltageCell1P.quantiti, 0, 10);
		printADCFloat(voltageCell2P.name, voltageCell2P.avgValue,
				voltageCell2P.quantiti, 0, 20);
		printADCFloat(voltageCell3P.name, voltageCell3P.avgValue,
				voltageCell3P.quantiti, 0, 30);
		printADCFloat(voltageCell4P.name, voltageCell4P.avgValue,
				voltageCell4P.quantiti, 0, 40);
		printADCFloat(currentCharge.name, currentCharge.avgValue,
				currentCharge.quantiti, 0, 50);
		printADCFloat(currentDischarge.name, currentDischarge.avgValue,
				currentDischarge.quantiti, 0, 60);

		printADCInt(voltageAdapter.name, voltageAdapter.avgValue,
				voltageAdapter.quantiti, 65, 10);
		printADCInt(tempCell.name, tempCell.avgValue, tempCell.quantiti, 65,
				20);
		printADCInt(tempBalancer.name, tempBalancer.avgValue,
				tempBalancer.quantiti, 65, 30);
		printADCInt(tempMCU.name, tempMCU.avgValue, tempMCU.quantiti, 65, 40);

	} while (u8g_NextPage(&lcd));
}

void writeMaxOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		printADCFloat(voltageCell1P.name, voltageCell1P.maxValue,
				voltageCell1P.quantiti, 0, 10);
		printADCFloat(voltageCell2P.name, voltageCell2P.maxValue,
				voltageCell2P.quantiti, 0, 20);
		printADCFloat(voltageCell3P.name, voltageCell3P.maxValue,
				voltageCell3P.quantiti, 0, 30);
		printADCFloat(voltageCell4P.name, voltageCell4P.maxValue,
				voltageCell4P.quantiti, 0, 40);
		printADCFloat(currentCharge.name, currentCharge.maxValue,
				currentCharge.quantiti, 0, 50);
		printADCFloat(currentDischarge.name, currentDischarge.maxValue,
				currentDischarge.quantiti, 0, 60);

		printADCInt(voltageAdapter.name, voltageAdapter.maxValue,
				voltageAdapter.quantiti, 65, 10);
		printADCInt(tempCell.name, tempCell.maxValue, tempCell.quantiti, 65,
				20);
		printADCInt(tempBalancer.name, tempBalancer.maxValue,
				tempBalancer.quantiti, 65, 30);
		printADCInt(tempMCU.name, tempMCU.maxValue, tempMCU.quantiti, 65, 40);

	} while (u8g_NextPage(&lcd));
}

void writeMinOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		printADCFloat(voltageCell1P.name, voltageCell1P.minValue,
				voltageCell1P.quantiti, 0, 10);
		printADCFloat(voltageCell2P.name, voltageCell2P.minValue,
				voltageCell2P.quantiti, 0, 20);
		printADCFloat(voltageCell3P.name, voltageCell3P.minValue,
				voltageCell3P.quantiti, 0, 30);
		printADCFloat(voltageCell4P.name, voltageCell4P.minValue,
				voltageCell4P.quantiti, 0, 40);
		printADCFloat(currentCharge.name, currentCharge.minValue,
				currentCharge.quantiti, 0, 50);
		printADCFloat(currentDischarge.name, currentDischarge.minValue,
				currentDischarge.quantiti, 0, 60);

		printADCInt(voltageAdapter.name, voltageAdapter.minValue,
				voltageAdapter.quantiti, 65, 10);
		printADCInt(tempCell.name, tempCell.minValue, tempCell.quantiti, 65,
				20);
		printADCInt(tempBalancer.name, tempBalancer.minValue,
				tempBalancer.quantiti, 65, 30);
		printADCInt(tempMCU.name, tempMCU.minValue, tempMCU.quantiti, 65, 40);

	} while (u8g_NextPage(&lcd));
}

void writeCellsOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		printADCFloat(cell1.name, cell1.voltage, 'V', 0, 10);
		printADCFloat(cell2.name, cell2.voltage, 'V', 0, 20);
		printADCFloat(cell3.name, cell3.voltage, 'V', 0, 30);
		printADCFloat(cell4.name, cell4.voltage, 'V', 0, 40);
		printADCFloat(currentCharge.name, currentCharge.minValue,
				currentCharge.quantiti, 0, 50);
		printADCFloat(currentDischarge.name, currentDischarge.minValue,
				currentDischarge.quantiti, 0, 50);

	} while (u8g_NextPage(&lcd));
}

void writeCellsCapacityOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		float tmp = (cell1.estimatedStart_mAh + cell2.estimatedStart_mAh
				+ cell3.estimatedStart_mAh + cell4.estimatedStart_mAh) / 4;
		printADCFloat("Start  mAh", tmp, 'mAh', 0, 10);

		tmp =
				(cell1.used_mAh + cell2.used_mAh + cell3.used_mAh
						+ cell4.used_mAh) / 4;
		printADCFloat("Used   mAh", tmp, 'mAh', 0, 20);

		tmp = (cell1.used_Wh + cell2.used_Wh + cell3.used_Wh + cell4.used_Wh);
		printADCFloat("used    Wh", tmp, 'mAh', 0, 30);

		tmp = (estimateRemaining_mAh_ByDeliveredEnergy(cell1)
				+ estimateRemaining_mAh_ByDeliveredEnergy(cell2)
				+ estimateRemaining_mAh_ByDeliveredEnergy(cell3)
				+ estimateRemaining_mAh_ByDeliveredEnergy(cell4)) / 4;
		printADCFloat("Remain mAh", tmp, 'mAh', 0, 40);

		tmp = (estimateRemainingCapacityPercentByVoltage(cell1)
				+ estimateRemainingCapacityPercentByVoltage(cell2)
				+ estimateRemainingCapacityPercentByVoltage(cell3)
				+ estimateRemainingCapacityPercentByVoltage(cell4)) / 4;
		printADCFloat("Remain mAh", tmp, 'mAh', 0, 50);

	} while (u8g_NextPage(&lcd));
}

void writeCapacityEstimatedTime() {
// dodělat
	u8g_FirstPage(&lcd);
	do {

	} while (u8g_NextPage(&lcd));
}

writeOnLCDByStatus() {
	switch (lcdStatus) {
	case 0:
		writeCurrentOnLCD();
		break;
	case 1:
		writeAverageOnLCD();
		break;
	case 2:
		writeMaxOnLCD();
		break;
	case 3:
		writeMinOnLCD();
		break;
	case 4:
		writeCellsOnLCD();
		break;
	case 5:
		writeCellsCapacityOnLCD();
		break;
	case 6:
		writeCapacityEstimatedTime();
	}
}

void increaseLCDstatus() {
	if (lcdStatus < MAX_LCD_STATUS)
		lcdStatus++;
}

void reduceLCDstatus() {
	if (lcdStatus > 0)
		lcdStatus--;

}

void setLCDstatus(uint8_t status) {
	if (status >= 0 && status <= MAX_LCD_STATUS)
		lcdStatus = status;
	else
		lcdStatus = 0;

}

void goRoundLCDstatus() {
	if (lcdStatus < MAX_LCD_STATUS)
		lcdStatus++;
	else
		lcdStatus = 0;

}
