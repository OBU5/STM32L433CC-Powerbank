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

void initLCD()
{
	  changeStateOfGPIO(&FET_HoldOn,1);
	  HAL_Delay(1);
	  changeStateOfGPIO(&LCD_BL,1);
	  HAL_Delay(1);
	  changeStateOfGPIO(&LCD_RST,1);
	  HAL_Delay(1);
	  changeStateOfGPIO(&LCD_RST,0);
	  HAL_Delay(1);
	  changeStateOfGPIO(&LCD_RST,1);
	  HAL_Delay(1);

    u8g_InitComFn(&lcd, &u8g_dev_uc1701_dogs102_hw_spi, u8g_com_hw_spi_fn);

}

void printAccuratelyADC(struct ADC* adc, uint16_t x, uint16_t y){
    sprintf(tmpForSprintf,"%s=%2.3f%c",adc->name,adc->currValue,adc->quantiti);
    u8g_DrawStr(&lcd, x,y, tmpForSprintf);
}

void printApproximatelyADC(struct ADC* adc, uint16_t x, uint16_t y){
    sprintf(tmpForSprintf,"%s=%2d%c",adc->name,(uint8_t)adc->currValue,adc->quantiti);
    u8g_DrawStr(&lcd, x,y, tmpForSprintf);
}



void writeAllOnLCD(){
    u8g_FirstPage(&lcd);
     do
     {
         lcd.font = u8g_font_6x10r;
         printAccuratelyADC(&voltageCell1P,0,10);
         printAccuratelyADC(&voltageCell2P,0,20);
         printAccuratelyADC(&voltageCell3P,0,30);
         printAccuratelyADC(&voltageCell4P,0,40);
         printAccuratelyADC(&currentCharge,0, 50);
         printAccuratelyADC(&currentDischarge,0,60);


         printApproximatelyADC(&voltageAdapter,65,10);
         printApproximatelyADC(&tempCell,65,40);
         printApproximatelyADC(&tempBalancer,65,50);
         printApproximatelyADC(&tempMCU,65,60);
     	//printADC(voltageBat,70
     	//printADC(Vrefint

     } while ( u8g_NextPage(&lcd) );
}
