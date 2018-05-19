/*
 * lcd.h
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */
#ifndef LCD_H_
#define LCD_H_

typedef enum {
	NONE, MENU, SUBMENU, SUBSUBMENU
} MenuLevel;

typedef enum {
	LCD_STAT, OUTPUT_REG, SEND, BACKLIGHT, TURN_OFF
} MenuIndex;

typedef enum {
	BACKLIGH_OFF, BACKLIGH_ON_FOR_TIME, BACKLIGH_ON_FOREVER
} BacklightStatus;

//method thathat init LCD
void initLCD();
	//Backligh;

//method that print float value (made for ADC)
void writeFloatADC(char adcName[5], float adcValue, char adcQuantiti,
		uint16_t x, uint16_t y);


void writeFloat2ADC(char adcName[5], float adcValue, char adcQuantiti,
		uint16_t x, uint16_t y);
//method that print float value of ADC
void writeIntADC(char adcName[5], float adcValue, char adcQuantiti, uint16_t x,
		uint16_t y);
//method that print voltage of Cell
void writeFloatCellVoltage(struct cell cell, uint16_t x, uint16_t y);

//method that print all lates ADC values
void writeAllCurrentADCValues();

//method that print all average ADC values
void writeAllAverageADCValues() ;

//method that print all maximal ADC values
void writeAllMaxADCValues();

//method that print all minimal ADC values
void writeAllMinADCValues();

//method that prints cells voltage, sorted by name and charging and discharging current
void writeCellsOnLCD();

//method that prints cells capacity.
void writeCellsCapacityOnLCD();
//proint on lcd depending on moenu level
//probably that is the function what are you looking for
writeOnLCDByMenuIndex();

//method that prints screen depending on lcdIndex
void printByLcdIndex();

//method that print main screen (that shows most demanding values)
void printMainScreen();

//method that sets lcdIndex on desired value
setLCDindex(uint8_t index);

// method that prints menu
void printMenu();
//method that prints output regulator
void print_OUTPUT_REG_Submenu() ;

// method that prints submenu of lcd stat
void print_LCD_STAT_Submenu();
// method that prints submenu of send
void print_SEND_Submenu();
//method that prints submenu of baclight
void print_BACKLIGHT_Submenu() ;

//metho that prints submenu of turn off
void print_TURN_OFF_Submenu();

//method that increase value of menuIndex
void increaseMenuIndex();

// method that reduces menuIndex
void reduceMenuIndex() ;
// method that go round with menuIndex
void goRoundMenuIndex();

//method that sets value of menu level
void setMenuIndex(uint8_t level);
//method that sets value of menu level
void set_MENU_LEVEL(uint8_t level);
//method that increase value of menu level
void increase_MENU_LEVEL();
//method that reduces value of menu level
void reduce_MENU_LEVEL();

//method that go round with menu level
void goRound_MENU_LEVEL();
//method that sets submenu index
void setSubMenuIndex(uint8_t level);
//method that increase Submenu Index
void increaseSubMenuIndex();
//method that reduces value of submenuIndex
void reduceSubMenuIndex();
//method that go round with value of submenuIndex
void goRoundSubMenuIndex();

//method that returs menuLevel
int getMenuLevel();
//method that returns menuIndex
int getMenuIndex();
//method that returns subMenuIndex
int getSubMenuIndex();

//method that checks what to do with lcd
void backlightCheck();

//method that turns on lcd baclight, if it isn't alreadyy turned on forever
void backlightON();

//method that turns off baclight of lcd
void backlightOFF();

//method that turns on baclight of lcd forever
void backlightOnForever();


void reduceSubMenuIndex();
//method that go round with value of submenuIndex
void goRoundSubMenuIndex();

//method that returs menuLevel
int getMenuLevel();
//method that returns menuIndex
int getMenuIndex();
//method that returns subMenuIndex
int getSubMenuIndex();

//method that checks what to do with lcd
void backlightCheck();

//method that turns on lcd baclight, if it isn't alreadyy turned on forever
void backlightON();

//method that turns off baclight of lcd
void backlightOFF();

//method that turns on baclight of lcd forever
void backlightOnForever();

#endif /* LCD_H_ */
