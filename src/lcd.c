/*
 * lcd.c
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */
#include "config.h"
#include "events.h"
#include "lcd.h"
#include "power.h"
#include "u8g/u8g.h"
#include "u8g/u8g_arm.h"

//structure that works with u8g library
u8g_t lcd;

//temporary variables
volatile char tmpForSprintf[10];
float tmp;

//variable that determines level of menu (no menu, menu, submenu)
MenuLevel menuLevel;
//variable that determines index of menu (lcd stat, ouput voltage, send data, backlight, turn off)
MenuIndex menuIndex;
//variable that determines index of submenu (depends on menu index)
uint8_t subMenuIndex;
//variable that determines backlight status (OFF, ON for some time, ON forever)
BacklightStatus backlightStatus;
//variable that turn off backlight, when it reach  vaue of BACKLIGHT_TIME_OFF
uint16_t backlightTime;
//variable that determines index of lcd screen
uint16_t lcdIndex;

//CTU logo (lion)
static unsigned char logoCVUT[] U8G_PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xF3,
		0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xDF, 0x80, 0x00, 0x00, 0x00, 0xFC,
		0x00, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x01, 0x80,
		0x00, 0x07, 0xEE, 0xFD, 0x80, 0x70, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x0C, 0x1F, 0x80, 0x00, 0x87, 0xEC, 0xFD, 0xE0, 0xE0, 0x70, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x03, 0x80, 0x00, 0xC6, 0x71, 0xFB,
		0xA1, 0xC0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1B, 0x80,
		0x00, 0x60, 0x7F, 0xFB, 0xB9, 0xC0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x18, 0x0F, 0x80, 0x00, 0x3F, 0xFF, 0xFB, 0xA8, 0xE0, 0x70, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x07, 0xC0, 0x00, 0x00, 0x7F, 0xFB,
		0xA8, 0x70, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x03, 0xC0,
		0x00, 0x06, 0x60, 0x06, 0x68, 0x71, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x0F, 0xF3, 0xE0, 0x00, 0x07, 0xFF, 0xFC, 0xDC, 0x27, 0x80, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF3, 0xF0, 0x00, 0x00, 0x1F, 0xE1,
		0x94, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0xF8,
		0x00, 0x01, 0xFF, 0x0F, 0x34, 0x1C, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x07, 0x70, 0xFF, 0xFE, 0x07, 0xFC, 0x7E, 0x6C, 0x79, 0xC0, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x78, 0x7F, 0xFF, 0xDF, 0x81, 0xF8,
		0xCC, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x7C, 0x7F,
		0xFF, 0x9F, 0x3F, 0xC3, 0x99, 0xC0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x0F, 0x7C, 0x3F, 0xFF, 0x38, 0x7C, 0x1E, 0x33, 0x80, 0x38, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x7C, 0x03, 0xFF, 0x73, 0xF1, 0xF8,
		0xE7, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x7C, 0x00,
		0x7F, 0x77, 0xC7, 0xE3, 0xC6, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x1E, 0x00, 0x00, 0x78, 0x77, 0x9F, 0x8F, 0x06, 0x00, 0x18, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x1F, 0x80, 0x03, 0x77, 0x3E, 0x3E,
		0x06, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x01, 0x80,
		0x07, 0x77, 0x78, 0xF8, 0x06, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x3C, 0x1F, 0x80, 0x1F, 0x37, 0x73, 0xF0, 0x07, 0x00, 0x38, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x01, 0xC0, 0x7F, 0xB7, 0x67, 0x04,
		0x03, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x1D, 0xC0,
		0xFF, 0x9B, 0x6E, 0x7E, 0x01, 0xC0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x7C, 0x07, 0xFF, 0xFF, 0xCD, 0x6C, 0xFF, 0x00, 0xFF, 0xC0, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x03, 0xFF, 0xF8, 0x65, 0x6D, 0xFF,
		0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x09, 0xFF,
		0xE0, 0x70, 0x01, 0xFF, 0xC1, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xF8, 0x0C, 0xFF, 0x00, 0x63, 0xF9, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x0E, 0x0E, 0x00, 0x0F, 0xFC, 0x7F,
		0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x07, 0x82,
		0x00, 0x7F, 0xFF, 0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0xC0, 0x03, 0x80, 0x00, 0xFF, 0xFF, 0xBF, 0xF0, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x01, 0xC0, 0x00, 0xFF, 0xFF, 0x9F,
		0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x01, 0xC0,
		0x00, 0xFF, 0xFF, 0x8F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x80, 0x01, 0xC0, 0x00, 0xFF, 0xBF, 0x8F, 0xF0, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0xC0, 0x00, 0xFF, 0x0F, 0x9F,
		0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0xE0,
		0x00, 0x7F, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x00, 0x00, 0xE0, 0x00, 0x7F, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xE0, 0x00, 0x3F, 0xE0, 0x01,
		0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x60,
		0x00, 0x3F, 0xC0, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x06, 0x00, 0x00, 0x70, 0x00, 0x1F, 0x80, 0x00, 0x7F, 0xFE, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x77, 0xF0, 0x1F, 0x80, 0x00,
		0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x70,
		0x70, 0x0F, 0x80, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x0C, 0x00, 0x00, 0x33, 0xF8, 0x0F, 0x80, 0x00, 0x00, 0x1F, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x38, 0x7C, 0x0F, 0x80, 0x1F,
		0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x3B,
		0x7E, 0x0F, 0x80, 0x01, 0xE0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x1C, 0x00, 0x00, 0x39, 0xFF, 0x1F, 0x80, 0x0F, 0xF8, 0x3F, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x1C, 0x3F, 0xFF, 0x80, 0x00,
		0xFC, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1C,
		0x1F, 0xFF, 0x80, 0x0E, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x38, 0x00, 0x00, 0x1C, 0x0F, 0xF3, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x07, 0xE0, 0x00, 0x00,
		0x3F, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1C,
		0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//method that init LCD
void initLCD() {
	//Backlight ON (just for CTU logo)
	changeStateOfGPIO(&LCD_BL, 1);

	//reset LCD
	changeStateOfGPIO(&LCD_RST, 1);
	HAL_Delay(10);
	changeStateOfGPIO(&LCD_RST, 0);
	HAL_Delay(10);
	changeStateOfGPIO(&LCD_RST, 1);
	HAL_Delay(10);

	//init uc1701
	u8g_InitComFn(&lcd, &u8g_dev_uc1701_dogs102_hw_spi, u8g_com_hw_spi_fn);
	HAL_Delay(10);

	//print CTU logo for 2 seconds
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x13r;

		u8g_DrawBitmap(&lcd, 0, 0, 16, 64, logoCVUT);

	} while (u8g_NextPage(&lcd));

	HAL_Delay(1000);
	changeStateOfGPIO(&LCD_BL, 0);

	//everything set to 0
	lcdIndex = 0;
	menuLevel = 0;
	menuIndex = 0;
	subMenuIndex = 0;
	backlightTime = 0;
	backlightStatus = 0;

}

//method that print float value (made for ADC)
void writeFloatADC(char adcName[5], float adcValue, char adcQuantiti,
		uint16_t x, uint16_t y) {
	sprintf(tmpForSprintf, "%s=%2.1f%c", adcName, adcValue, adcQuantiti);
	u8g_DrawStr(&lcd, x, y, tmpForSprintf);
}

void writeFloat2ADC(char adcName[5], float adcValue, char adcQuantiti,
		uint16_t x, uint16_t y) {
	sprintf(tmpForSprintf, "%s=%2.3f%c", adcName, adcValue, adcQuantiti);
	u8g_DrawStr(&lcd, x, y, tmpForSprintf);
}

//method that print float value of ADC
void writeIntADC(char adcName[5], float adcValue, char adcQuantiti, uint16_t x,
		uint16_t y) {
	sprintf(tmpForSprintf, "%s=%2d%c", adcName, (int) adcValue, adcQuantiti);
	u8g_DrawStr(&lcd, x, y, tmpForSprintf);
}

//method that print voltage of Cell
void writeFloatCellVoltage(struct cell cell, uint16_t x, uint16_t y) {
	sprintf(tmpForSprintf, "%s=%2.3f %c", cell.name, cell.voltage, "V");
	u8g_DrawStr(&lcd, x, y, tmpForSprintf);
}

//method that print all lates ADC values
void writeAllCurrentADCValues() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		writeFloatADC(voltageCell1P.name, voltageCell1P.currValue,
				voltageCell1P.quantiti, 0, 10);

		writeFloatADC(voltageCell2P.name, voltageCell2P.currValue,
				voltageCell2P.quantiti, 0, 20);
		writeFloatADC(voltageCell3P.name, voltageCell3P.currValue,
				voltageCell3P.quantiti, 0, 30);
		writeFloatADC(voltageCell4P.name, voltageCell4P.currValue,
				voltageCell4P.quantiti, 0, 40);
		writeFloatADC("IB", currentDischarge.currValue,
				currentDischarge.quantiti, 0, 50);
		writeFloatADC("Vo", getOutputVoltage(),
				'V', 0, 60);

		writeFloatADC("IA", getCurrentCharge(),
				currentCharge.quantiti, 55, 20);
		writeFloatADC(voltageAdapter.name, voltageAdapter.currValue,
				voltageAdapter.quantiti, 55, 10);
		writeIntADC(tempCell.name,  getTemperature(tempCell.currValue), tempCell.quantiti, 55,
				30);
		writeIntADC(tempBalancer.name,  getTemperature(tempBalancer.currValue), tempBalancer.quantiti, 55, 40);
		lcd.font = u8g_font_10x20;
u8g_DrawStr(&lcd, 57, 58, "NOW");

	} while (u8g_NextPage(&lcd));
}

//method that print all average ADC values
void writeAllAverageADCValues() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		writeFloatADC(voltageCell1P.name, voltageCell1P.avgValue,
				voltageCell1P.quantiti, 0, 10);

		writeFloatADC(voltageCell2P.name, voltageCell2P.avgValue,
				voltageCell2P.quantiti, 0, 20);
		writeFloatADC(voltageCell3P.name, voltageCell3P.avgValue,
				voltageCell3P.quantiti, 0, 30);
		writeFloatADC(voltageCell4P.name, voltageCell4P.avgValue,
				voltageCell4P.quantiti, 0, 40);
		writeFloatADC("IB", currentDischarge.avgValue,
				currentDischarge.quantiti, 0, 50);
		writeFloatADC("Vo", getOutputVoltage(),
				'V', 0, 60);

		writeFloatADC("IA", getCurrentCharge(),
				currentCharge.quantiti, 55, 20);
		writeFloatADC(voltageAdapter.name, voltageAdapter.avgValue,
				voltageAdapter.quantiti, 55, 10);
		writeIntADC(tempCell.name,  getTemperature(tempCell.avgValue), tempCell.quantiti, 55,
				30);
		writeIntADC(tempBalancer.name,  getTemperature(tempBalancer.avgValue), tempBalancer.quantiti, 55, 40);
		lcd.font = u8g_font_10x20;
u8g_DrawStr(&lcd, 57, 58, "AVG");
	} while (u8g_NextPage(&lcd));
}

//method that print all maximal ADC values
void writeAllMaxADCValues() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10r;
		writeFloatADC(voltageCell1P.name, voltageCell1P.maxValue,
				voltageCell1P.quantiti, 0, 10);

		writeFloatADC(voltageCell2P.name, voltageCell2P.maxValue,
				voltageCell2P.quantiti, 0, 20);
		writeFloatADC(voltageCell3P.name, voltageCell3P.maxValue,
				voltageCell3P.quantiti, 0, 30);
		writeFloatADC(voltageCell4P.name, voltageCell4P.maxValue,
				voltageCell4P.quantiti, 0, 40);
		writeFloatADC("IB", currentDischarge.maxValue,
				currentDischarge.quantiti, 0, 50);
		writeFloatADC("Vo", getOutputVoltage(),
				'V', 0, 60);

		writeFloatADC("IA", getCurrentCharge(),
				currentCharge.quantiti, 55, 20);
		writeFloatADC(voltageAdapter.name, voltageAdapter.maxValue,
				voltageAdapter.quantiti, 55, 10);
		writeIntADC(tempCell.name,  getTemperature(tempCell.maxValue), tempCell.quantiti, 55,
				30);
		writeIntADC(tempBalancer.name,  getTemperature(tempBalancer.maxValue), tempBalancer.quantiti, 55, 40);
		lcd.font = u8g_font_10x20;
u8g_DrawStr(&lcd, 57, 58, "MAX");
	} while (u8g_NextPage(&lcd));
}

//method that print all minimal ADC values
void writeAllMinADCValues() {
	u8g_FirstPage(&lcd);
	do {		lcd.font = u8g_font_6x10r;
	lcd.font = u8g_font_6x10r;
	writeFloatADC(voltageCell1P.name, voltageCell1P.minValue,
			voltageCell1P.quantiti, 0, 10);

	writeFloatADC(voltageCell2P.name, voltageCell2P.minValue,
			voltageCell2P.quantiti, 0, 20);
	writeFloatADC(voltageCell3P.name, voltageCell3P.minValue,
			voltageCell3P.quantiti, 0, 30);
	writeFloatADC(voltageCell4P.name, voltageCell4P.minValue,
			voltageCell4P.quantiti, 0, 40);
	writeFloatADC("IB", currentDischarge.minValue,
			currentDischarge.quantiti, 0, 50);
	writeFloatADC("Vo", getOutputVoltage(),
			'V', 0, 60);

	writeFloatADC("IA", getCurrentCharge(),
			currentCharge.quantiti, 55, 20);
	writeFloatADC(voltageAdapter.name, voltageAdapter.minValue,
			voltageAdapter.quantiti, 55, 10);
	writeIntADC(tempCell.name,  getTemperature(tempCell.minValue), tempCell.quantiti, 55,
			30);
	writeIntADC(tempBalancer.name,  getTemperature(tempBalancer.minValue), tempBalancer.quantiti, 55, 40);
	lcd.font = u8g_font_10x20;
u8g_DrawStr(&lcd, 57, 58, "MIN");
	} while (u8g_NextPage(&lcd));
}

//method that prints cells voltage, sorted by name and charging and discharging current
void writeCellsOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x12r;
		writeFloat2ADC("1P", cell1.voltage, 'V', 20, 12);
		writeFloat2ADC("2P", cell2.voltage, 'V', 20, 24);
		writeFloat2ADC("3P", cell3.voltage, 'V', 20, 36);
		writeFloat2ADC("4P", cell4.voltage, 'V', 20, 48);

		writeFloat2ADC("IB", currentDischarge.currValue,
				currentDischarge.quantiti, 20, 60);

	} while (u8g_NextPage(&lcd));
}

//method that prints cells capacity.
void writeCellsCapacityOnLCD() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_6x10;
		u8g_DrawStr(&lcd, 5, 11, "used mAh");
		u8g_DrawStr(&lcd, 5, 26 - 2, "used Wh ");

		lcd.font = u8g_font_6x12;
		sprintf(tmpForSprintf, "%4.2f",
				(cell1.used_mAh));
		u8g_DrawStr(&lcd, 50+5, 13, tmpForSprintf);
		sprintf(tmpForSprintf, "%4.2f",
				(cell1.used_Wh + cell2.used_Wh + cell3.used_Wh + cell4.used_Wh));
		u8g_DrawStr(&lcd, 50+5, 26, tmpForSprintf);

		writeFloat2ADC("VB", voltageCell4P.currValue,
						voltageCell4P.quantiti, 20, 39);

		writeFloat2ADC("IB", currentDischarge.currValue,
						voltageCell4P.quantiti, 20, 52);
	} while (u8g_NextPage(&lcd));
}

//proint on lcd depending on moenu level
//probably that is the function what are you looking for
writeOnLCDByMenuIndex() {
	switch (menuLevel) {
	case NONE:
		//nothing pressed
		printByLcdIndex();
		break;
	case MENU:
		//you are in menu
		printMenu();
		break;
	case SUBMENU:
		//you are in submenu
		switch (menuIndex) {
		case LCD_STAT:
			print_LCD_STAT_Submenu();
			break;
		case OUTPUT_REG:
			print_OUTPUT_REG_Submenu();
			break;
		case SEND:
			print_SEND_Submenu();
			break;
		case BACKLIGHT:
			print_BACKLIGHT_Submenu();
			break;
		case TURN_OFF:
			print_TURN_OFF_Submenu();
			break;
		}
		break;
	}
}

//method that prints screen depending on lcdIndex
void printByLcdIndex() {
	switch (lcdIndex) {
	case 0:
		printMainScreen();
		break;
	case 1:
		writeAllCurrentADCValues();
		break;
	case 2:
		writeAllAverageADCValues();
		break;
	case 3:
		writeAllMaxADCValues();
		break;
	case 4:
		writeAllMinADCValues();
		break;
	case 5:
		writeCellsCapacityOnLCD();
		break;
	case 6:
		writeCellsOnLCD();
		break;
	}
}

//method that print main screen (that shows most demanding values)
void printMainScreen() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_7x13;

		//output voltage
		sprintf(tmpForSprintf, "%2.1fV", getOutputVoltage());
		u8g_DrawStr(&lcd, 2, 13, tmpForSprintf);

		//remaining use time
		float tmp = getEstimatedRemainingTime(cell1, cell2, cell3, cell4);
		if (tmp > 100)
			u8g_DrawStr(&lcd, 40, 13, "99h");
		else if (tmp < 100 && tmp >= 0) {

			sprintf(tmpForSprintf, "%2.0fh", tmp);
			u8g_DrawStr(&lcd, 40, 13, tmpForSprintf);
		}

		// capacity percent
		tmp = (100
				* minValue((cell1.estimatedCapacityPercent),
						(cell2.estimatedCapacityPercent),
						(cell3.estimatedCapacityPercent),
						(cell4.estimatedCapacityPercent)))
				- (((100
						* minValue((cell1.estimatedCapacityPercent),
								(cell2.estimatedCapacityPercent),
								(cell3.estimatedCapacityPercent),
								(cell4.estimatedCapacityPercent)))
						* minValue((cell1.estimatedCapacityPercent),
								(cell2.estimatedCapacityPercent),
								(cell3.estimatedCapacityPercent),
								(cell4.estimatedCapacityPercent)))* (cell1.used_mAh)/(cell1.estimatedStart_mAh));
		if (tmp < 100 && tmp >= 0) {
		} else if (tmp >= 100) {
			tmp = 99.9;
		}

		sprintf(tmpForSprintf, "%2.1f%%", tmp);
		u8g_DrawStr(&lcd, 5 * 7 + 4 * 7 + 2, 13, tmpForSprintf);

		//battery voltage
		//text
		lcd.font = u8g_font_6x13;
		u8g_DrawStr(&lcd, 2, 30, "U");
		lcd.font = u8g_font_5x8;
		//index
		u8g_DrawStr(&lcd, 9, 30 + 2, "B");
		//value
		lcd.font = u8g_font_6x13;
		sprintf(tmpForSprintf, "=%2.1fV", voltageCell4P.currValue);
		u8g_DrawStr(&lcd, 15, 30, tmpForSprintf);

		//text
		lcd.font = u8g_font_6x13;
		u8g_DrawStr(&lcd, 2 + 50, 30, "I");
		//index
		lcd.font = u8g_font_5x8;
		u8g_DrawStr(&lcd, 9 + 50, 30 + 2, "B");
		//value
		lcd.font = u8g_font_6x13;

		sprintf(tmpForSprintf, "=%1.2fA", currentDischarge.currValue);
		u8g_DrawStr(&lcd, 15 + 50, 30, tmpForSprintf);

		//text
		lcd.font = u8g_font_6x13;
		u8g_DrawStr(&lcd, 2, 45, "T");
		//index
		lcd.font = u8g_font_5x8;
		u8g_DrawStr(&lcd, 9, 45 + 2, "B");
		//value
		lcd.font = u8g_font_6x13;
		sprintf(tmpForSprintf, "=%2.0fC", getTemperature(tempCell.currValue));
		u8g_DrawStr(&lcd, 15, 45, tmpForSprintf);

		//text
		lcd.font = u8g_font_6x13;
		u8g_DrawStr(&lcd, 2 + 50, 45, "T");
		//index
		lcd.font = u8g_font_5x8;
		u8g_DrawStr(&lcd, 9 + 50, 45 + 2, "C");
		//value
		lcd.font = u8g_font_6x13;
		sprintf(tmpForSprintf, "=%2.0fC",
				getTemperature(tempBalancer.currValue));
		u8g_DrawStr(&lcd, 15 + 50, 45, tmpForSprintf);

		//text
		lcd.font = u8g_font_6x13;
		u8g_DrawStr(&lcd, 2, 60, "V");
		//index
		lcd.font = u8g_font_5x8;
		u8g_DrawStr(&lcd, 9, 60 + 2, "A");
		//value
		lcd.font = u8g_font_6x13;
		sprintf(tmpForSprintf, "=%2.1fV", voltageAdapter.currValue);
		u8g_DrawStr(&lcd, 15, 60, tmpForSprintf);

		//text
		lcd.font = u8g_font_6x13;
		u8g_DrawStr(&lcd, 2 + 50, 60, "I");
		//index
		lcd.font = u8g_font_5x8;
		u8g_DrawStr(&lcd, 9 + 50, 60 + 2, "A");
		//value
		lcd.font = u8g_font_6x13;
		sprintf(tmpForSprintf, "=%2.1fA", getCurrentCharge());
		u8g_DrawStr(&lcd, 15 + 50, 60, tmpForSprintf);

		// draw lines for better appearance
		u8g_DrawLine(&lcd, 5 * 7 + 2, 15, 5 * 7 + 2, 0);
		u8g_DrawLine(&lcd, 0, 0, 0, 64);
		u8g_DrawLine(&lcd, 101, 0, 101, 64);
		u8g_DrawLine(&lcd, 5 * 7 + 4 * 7 - 1, 15, 5 * 7 + 4 * 7 - 1, 0);
		u8g_DrawLine(&lcd, 102, 0, 102, 64);
		u8g_DrawLine(&lcd, 0, 15, 101, 15);
		u8g_DrawLine(&lcd, 0, 0, 102, 0);
		u8g_DrawLine(&lcd, 51, 64, 51, 16);
		u8g_DrawLine(&lcd, 0, 33, 102, 33);
		u8g_DrawLine(&lcd, 0, 48, 102, 48);
		u8g_DrawLine(&lcd, 0, 63, 102, 63);

	} while (u8g_NextPage(&lcd));
}

//method that sets lcdIndex on desired value
setLCDindex(uint8_t index) {
	lcdIndex = index;
}

// method that prints menu
void printMenu() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_7x13;
		u8g_DrawStr(&lcd, 10, 13, " MENU");
		lcd.font = u8g_font_6x12;
		u8g_DrawLine(&lcd, 0, 14, 102, 14);
		if (menuIndex < 4) {
			u8g_DrawStr(&lcd, 10, 26, "LCD STAT");
			u8g_DrawStr(&lcd, 10, 38, "OUTPUT REG");
			u8g_DrawStr(&lcd, 10, 50, "SEND");
			u8g_DrawStr(&lcd, 10, 62, "BACKLIGHT");
			u8g_DrawStr(&lcd, 0, (menuIndex * 12) + 26, ">");
			//u8g_DrawStr(&lcd, 90, (subMenuIndex * 12) + 26, "-");
		} else {
			lcd.font = u8g_font_6x12;

			u8g_DrawStr(&lcd, 10, 26, "TURN OFF");

			u8g_DrawStr(&lcd, 0, ((menuIndex - 4) * 12) + 26, ">");
			//u8g_DrawStr(&lcd, 90, ((subMenuIndex-4) * 12) + 26, "-");
		}
	} while (u8g_NextPage(&lcd));
}

//method that prints output regulator
void print_OUTPUT_REG_Submenu() {
	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_7x13;
		u8g_DrawStr(&lcd, 10, 10, " OUTPUT REG");
		lcd.font = u8g_font_6x12;
		u8g_DrawLine(&lcd, 0, 14, 102, 14);
		if (subMenuIndex < 4) {
			u8g_DrawStr(&lcd, 10, 26, "Out = 0V");
			u8g_DrawStr(&lcd, 10, 38, "Out = 3V");
			u8g_DrawStr(&lcd, 10, 50, "Out = 5V");
			u8g_DrawStr(&lcd, 10, 62, "Out = 9V");

			u8g_DrawStr(&lcd, 0, (subMenuIndex * 12) + 26, ">");
		} else {
			lcd.font = u8g_font_6x12;

			u8g_DrawStr(&lcd, 10, 26, "Out = 11.5V");

			u8g_DrawStr(&lcd, 0, ((subMenuIndex - 4) * 12) + 26, ">");
		}
	} while (u8g_NextPage(&lcd));

}

// method that prints submenu of lcd stat
void print_LCD_STAT_Submenu() {

	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_7x13;
		u8g_DrawStr(&lcd, 10, 10, " OUTPUT REG");
		lcd.font = u8g_font_6x12;
		u8g_DrawLine(&lcd, 0, 14, 102, 14);
		if (subMenuIndex < 4) {
			u8g_DrawStr(&lcd, 10, 26, "Main Screen");
			u8g_DrawStr(&lcd, 10, 38, "All cur vales");
			u8g_DrawStr(&lcd, 10, 50, "All avg vales");
			u8g_DrawStr(&lcd, 10, 62, "All max vales");

			u8g_DrawStr(&lcd, 0, (subMenuIndex * 12) + 26, ">");
		} else {
			lcd.font = u8g_font_6x12;

			u8g_DrawStr(&lcd, 10, 26, "All min vales");
			u8g_DrawStr(&lcd, 10, 38, "Used capacity");
			u8g_DrawStr(&lcd, 10, 50, "Cell Voltage");
			u8g_DrawStr(&lcd, 10, 62, "");

			u8g_DrawStr(&lcd, 0, ((subMenuIndex - 4) * 12) + 26, ">");
		}
	} while (u8g_NextPage(&lcd));

}

// method that prints submenu of send
void print_SEND_Submenu() {

	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_7x13;
		u8g_DrawStr(&lcd, 10, 10, "SEND");
		lcd.font = u8g_font_6x12;
		u8g_DrawLine(&lcd, 0, 14, 102, 14);
		if (subMenuIndex < 4) {
			u8g_DrawStr(&lcd, 10, 26, "Send 1");
			u8g_DrawStr(&lcd, 10, 38, "Send 2");
			u8g_DrawStr(&lcd, 10, 50, "Send 3");
			u8g_DrawStr(&lcd, 10, 62, "Send 4");

			u8g_DrawStr(&lcd, 0, (subMenuIndex * 12) + 26, ">");
			//u8g_DrawStr(&lcd, 90, (subMenuIndex * 12) + 26, "-");
		} else {
			lcd.font = u8g_font_6x12;

			u8g_DrawStr(&lcd, 10, 26, "Send 5");
			u8g_DrawStr(&lcd, 10, 38, "Send 6");
			u8g_DrawStr(&lcd, 10, 50, "Send 7");
			u8g_DrawStr(&lcd, 10, 62, "Send 8");

			u8g_DrawStr(&lcd, 0, ((subMenuIndex - 4) * 12) + 26, ">");
			//u8g_DrawStr(&lcd, 90, ((subMenuIndex-4) * 12) + 26, "-");
		}
	} while (u8g_NextPage(&lcd));

}

//method that prints submenu of baclight
void print_BACKLIGHT_Submenu() {

	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_7x13;
		u8g_DrawStr(&lcd, 10, 10, "BACKLIGHT");
		lcd.font = u8g_font_6x12;
		u8g_DrawLine(&lcd, 0, 14, 102, 14);
		if (subMenuIndex < 4) {
			u8g_DrawStr(&lcd, 10, 26, "Turn ON");
			u8g_DrawStr(&lcd, 10, 38, "Turn OFF");

			u8g_DrawStr(&lcd, 0, (subMenuIndex * 12) + 26, ">");
			//u8g_DrawStr(&lcd, 90, (subMenuIndex * 12) + 26, "-");
		} else {
		}
	} while (u8g_NextPage(&lcd));

}

//metho that prints submenu of turn off
void print_TURN_OFF_Submenu() {

	u8g_FirstPage(&lcd);
	do {
		lcd.font = u8g_font_7x13;
		u8g_DrawStr(&lcd, 10, 10, "TURN OFF ?");
		lcd.font = u8g_font_6x12;
		u8g_DrawLine(&lcd, 0, 14, 102, 14);
		if (subMenuIndex < 4) {
			u8g_DrawStr(&lcd, 10, 26, "Yes");
			u8g_DrawStr(&lcd, 10, 38, "Cancle");

			u8g_DrawStr(&lcd, 0, (subMenuIndex * 12) + 26, ">");
			//u8g_DrawStr(&lcd, 90, (subMenuIndex * 12) + 26, "-");
		} else {
		}
	} while (u8g_NextPage(&lcd));

}

//method that increase value of menuIndex
void increaseMenuIndex() {
	if (menuIndex < MAX_MENU_INDEX)
		menuIndex++;
}

// method that reduces menuIndex
void reduceMenuIndex() {
	if (menuIndex > 0)
		menuIndex--;
}
// method that go round with menuIndex
void goRoundMenuIndex() {
	if (menuIndex < MAX_MENU_INDEX)
		menuIndex++;
	else
		menuIndex = 0;
}

//method that sets value of menu level
void setMenuIndex(uint8_t level) {

	if (level <= MAX_MENU_INDEX && level >= 0)
		menuIndex = level;
}

//method that sets value of menu level
void set_MENU_LEVEL(uint8_t level) {
	if (level <= MAX_MENU_LEVEL && level >= 0)
		menuLevel = level;
}

//method that increase value of menu level
void increase_MENU_LEVEL() {
	if (menuLevel < MAX_MENU_LEVEL)
		menuLevel++;
}

//method that reduces value of menu level
void reduce_MENU_LEVEL() {
	if (menuLevel > 0)
		menuLevel--;

}

//method that go round with menu level
void goRound_MENU_LEVEL() {
	if (menuLevel < MAX_MENU_LEVEL)
		menuLevel++;
	else
		menuLevel = 0;
}

//method that sets submenu index
void setSubMenuIndex(uint8_t level) {
	switch (menuIndex) {
	case LCD_STAT:
		if (level <= MAX_LCD_STAT_SUBMENU_INDEX && level >= 0)
			subMenuIndex = level;
		break;
	case OUTPUT_REG:
		if (level <= MAX_OUTPUT_REG_SUBMENU_INDEX && level >= 0)
			subMenuIndex = level;
		break;
	case SEND:
		if (level <= MAX_SEND_SUBMENU_INDEX && level >= 0)
			subMenuIndex = level;
		break;
	case BACKLIGHT:
		if (level <= MAX_BACKLIGHT_SUBMENU_INDEX && level >= 0)
			subMenuIndex = level;
		break;
	case TURN_OFF:
		if (level <= MAX_TURN_OFF_SUBMENU_INDEX && level >= 0)
			subMenuIndex = level;
		break;
	}
}

//method that increase Submenu Index
void increaseSubMenuIndex() {
	switch (menuIndex) {
	case LCD_STAT:
		if (subMenuIndex < MAX_LCD_STAT_SUBMENU_INDEX)
			subMenuIndex++;
		break;
	case OUTPUT_REG:
		if (subMenuIndex < MAX_OUTPUT_REG_SUBMENU_INDEX)
			subMenuIndex++;
		break;
	case SEND:
		if (subMenuIndex < MAX_SEND_SUBMENU_INDEX)
			subMenuIndex++;
		break;
	case BACKLIGHT:
		if (subMenuIndex < MAX_BACKLIGHT_SUBMENU_INDEX)
			subMenuIndex++;
		break;
	case TURN_OFF:
		if (subMenuIndex < MAX_TURN_OFF_SUBMENU_INDEX)
			subMenuIndex++;
		break;
	}
}

//method that reduces value of submenuIndex
void reduceSubMenuIndex() {
	if (subMenuIndex > 0)
		subMenuIndex--;
}

//method that go round with value of submenuIndex
void goRoundSubMenuIndex() {

	switch (menuIndex) {
	case LCD_STAT:
		if (subMenuIndex < MAX_LCD_STAT_SUBMENU_INDEX)
			subMenuIndex++;
		else
			subMenuIndex = 0;
		break;
	case OUTPUT_REG:
		if (subMenuIndex < MAX_OUTPUT_REG_SUBMENU_INDEX)
			subMenuIndex++;
		else
			subMenuIndex = 0;
		break;
	case SEND:
		if (subMenuIndex < MAX_SEND_SUBMENU_INDEX)
			subMenuIndex++;
		else
			subMenuIndex = 0;
		break;
	case BACKLIGHT:
		if (subMenuIndex < MAX_BACKLIGHT_SUBMENU_INDEX)
			subMenuIndex++;
		else
			subMenuIndex = 0;
		break;
	case TURN_OFF:
		if (subMenuIndex < MAX_TURN_OFF_SUBMENU_INDEX)
			subMenuIndex++;
		else
			subMenuIndex = 0;
		break;
	}

}

//method that returs menuLevel
int getMenuLevel() {
	return menuLevel;
}

//method that returns menuIndex
int getMenuIndex() {
	return menuIndex;
}

//method that returns subMenuIndex
int getSubMenuIndex() {
	return subMenuIndex;
}

//method that checks what to do with lcd
void backlightCheck() {
	if (backlightStatus != BACKLIGH_ON_FOREVER) {
		if (backlightStatus == BACKLIGH_ON_FOR_TIME)
			backlightTime += 50;

		if (backlightTime <= BACKLIGHT_TIME_OFF
				&& backlightStatus == BACKLIGH_ON_FOR_TIME)
			changeStateOfGPIO(&LCD_BL, 1);
		else if (backlightStatus
				== BACKLIGH_ON_FOR_TIME&& backlightTime > BACKLIGHT_TIME_OFF) {
			changeStateOfGPIO(&LCD_BL, 0);
			backlightStatus = BACKLIGH_OFF;
		} else
			changeStateOfGPIO(&LCD_BL, 0);

	} else if (backlightStatus == BACKLIGH_ON_FOREVER)
		changeStateOfGPIO(&LCD_BL, 1);

}

//method that turns on lcd baclight, if it isn't alreadyy turned on forever
void backlightON() {
	if (backlightStatus != BACKLIGH_ON_FOREVER) {
		backlightStatus = BACKLIGH_ON_FOR_TIME;
		backlightTime = 0;
	}
}

//method that turns off baclight of lcd
void backlightOFF() {
	backlightStatus = BACKLIGH_OFF;
	backlightTime = 0;
}

//method that turns on baclight of lcd forever
void backlightOnForever() {
	backlightStatus = BACKLIGH_ON_FOREVER;
	backlightTime = 0;
}
