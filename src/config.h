#ifndef config
#define config

#include "stm32l4xx_hal.h"
#include "ADC.h"
#include "GPIO.h"
#include "BTN.h"
#include "TMR.h"

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


struct TMR button1Timer;
struct TMR button2Timer;
struct TMR button3Timer;
struct TMR integralTimer;
struct TMR idleTimer;

#define MAX_OUT_VOLTAGE_STATUS 3
#define MAX_CHARGER_CURRENT_STATUS 2

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


void initGPIOs();
void initADCs();

#endif
