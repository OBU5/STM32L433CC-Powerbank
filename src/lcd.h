/*
 * lcd.h
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#ifndef LCD_H_
#define LCD_H_


void initLCD();

void printADC(struct ADC* adc, uint16_t x, uint16_t y);

void writeAllOnLCD();


#endif /* LCD_H_ */
