#ifndef config
#define config

#include "stm32l4xx_hal.h"
#include "ADC.h"
#include "GPIO.h"
#include "TMR.h"
#include "cell.h"

//-----------------------------------------------------------------
//OUT
//-----------------------------------------------------------------


struct GPIO FET_HoldOn;
struct GPIO LCD_RST;
struct GPIO LCD_CS;
struct GPIO LCD_CD;
struct GPIO LCD_BL;

struct GPIO FET_BuckConv_12V;
struct GPIO FET_BuckConv_9V;
struct GPIO FET_BuckConv_5V;
struct GPIO CHRG_nSHDN;
struct GPIO FET_Charger_CurrentMode;
struct GPIO FET_BuckConv_EN;
struct GPIO CHRG_nICL;

struct GPIO BTN_1;
struct GPIO BTN_2;
struct GPIO BTN_3;



struct ADC voltageCell1P;
struct ADC voltageCell2P;
struct ADC voltageCell3P;
struct ADC voltageCell4P;
struct ADC tempCell;
struct ADC tempBalancer;
struct ADC voltageAdapter;
struct ADC currentCharge;
struct ADC currentDischarge;
struct ADC tempMCU;
struct ADC voltageBat;
struct ADC Vrefint;


struct TMR btn1Timer;
struct TMR btn2Timer;
struct TMR btn3Timer;
struct TMR integralTimer;
struct TMR idleTimer;



struct cell cell1;
struct cell cell2;
struct cell cell3;
struct cell cell4;



#define MAX_OUT_VOLTAGE_STATUS 3
#define MAX_CHARGER_CURRENT_STATUS 2
#define MAX_LCD_STATUS 6

//-----------------------------------------------------------------
//IN
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//ADC
//-----------------------------------------------------------------



#define SPI_HANDLER hspi2 // use your SPI hadler
extern SPI_HandleTypeDef SPI_HANDLER;

#define VREFINT ((uint16_t*)((uint32_t) 0x1FFF75AA))
#define TS_CAL1 ((uint16_t*)((uint32_t) 0x1FFF75A8))
#define TS_CAL2 ((uint16_t*)((uint32_t) 0x1FFF75CA))
#define V_REF 3.3
#define ADC_DISTORTION 4096
#define SHORT_TIME_LIMIT 50 //in milliseconds
#define LONG_TIME_LIMIT 1000 //in milliseconds
#define MAX_CELL_VOLTAGE 4.2 //in milliseconds
#define MIN_CELL_VOLTAGE 3 //in milliseconds

#define VOLTAGE_AT_LOW_PERCENT_OF_CAPACITY  3.25//in milliseconds
#define VOLTAGE_AT_HIGH_PERCENT_OF_CAPACITY 4.2//in milliseconds
#define CELL_CAPACITY 2400
#define HIGH_PERCENT_OF_CAPACITY 100
#define LOW_PERCENT_OF_CAPACITY 15


void initGPIOs();
void initADCs();

#endif
