/*
 * power.h
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#ifndef POWER_H_
#define POWER_H_

#include "config.h"

typedef enum {
	_0V, _5V, _3_3V,_9V, _11_5V
} OutVoltageStatus;


typedef enum {
	_0mA, _200mA, _2A
} ChargerCurrentStatus;


void checkCharger();
void initOutVoltage();
void chargerCurrentOFF();

void increaseChargerCurrent();

void reduceChargerCurrent();

void goRoundChargerCurrent();
void setChargerCurrent(ChargerCurrentStatus status);
void changeChargerCurrent();
void outVoltageOFF();

void changeOutVoltage(uint16_t status);
float getOutputVoltage();
float getCurrentCharge();


#endif /* POWER_H_ */
