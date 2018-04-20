/*
 * config.c
 *
 *  Created on: Apr 11, 2018
 *      Author: obu
 */

#include "config.h"
#include "stm32l4xx_it.h"

void initGPIOs() {
	initGPIO(&FET_HoldOn,OUT,GPIOA,GPIO_PIN_12);

	initGPIO(&LCD_RST,OUT,GPIOA,GPIO_PIN_9);
	initGPIO(&LCD_CS,OUT,GPIOA,GPIO_PIN_8);
	initGPIO(&LCD_CD,OUT,GPIOA,GPIO_PIN_10);
	initGPIO(&LCD_BL,OUT,GPIOB,GPIO_PIN_14);

	initGPIO(&FET_BuckConv_5V,OUT,GPIOB,GPIO_PIN_3);
	initGPIO(&FET_BuckConv_9V,OUT,GPIOB,GPIO_PIN_4);
	initGPIO(&FET_BuckConv_12V,OUT,GPIOB,GPIO_PIN_5);
	initGPIO(&FET_BuckConv_EN,OUT,GPIOA,GPIO_PIN_11);

	initGPIO(&FET_Charger_CurrentMode,OUT,GPIOB,GPIO_PIN_7);
	initGPIO(&CHRG_nSHDN,OUT,GPIOB,GPIO_PIN_9);
	initGPIO(&CHRG_nICL,IN,GPIOB,GPIO_PIN_8);


	initGPIO(&BTN_1,IN,GPIOA,GPIO_PIN_15);
	initGPIO(&BTN_2,IN,GPIOA,GPIO_PIN_1);
	initGPIO(&BTN_3,IN,GPIOA,GPIO_PIN_2);
}

void initADCs() {


	initADC("1P",&voltageCell1P,((10+9.09)/9.09),'V');
	initADC("2P",&voltageCell2P, ((10+3.09)/3.09),'V');
	initADC("3P",&voltageCell3P, ((10+1.87)/1.87),'V');
	initADC("4P",&voltageCell4P, ((10+1.37)/1.37),'V');
	initADC("Tc",&tempCell, 1,'C');
	initADC("Tb",&tempBalancer, 1,'C');
	initADC("VA",&voltageAdapter, (16+1.3)/1.3,'V');
	initADC("CC",&currentCharge, 2/1.2085,'A');
	initADC("CD",&currentDischarge,1/(0.033*20) ,'A');
	initADC("Tu",&tempMCU, 1,'C');
	initADC("Vb",&voltageBat, 1,'V');
}

void initTimers(){
	initTimer(&button1Timer,50);
	initTimer(&button2Timer,50);
	initTimer(&button3Timer,50);
	initTimer(&integralTimer,50);
	initTimer(&idleTimer,50);
}

