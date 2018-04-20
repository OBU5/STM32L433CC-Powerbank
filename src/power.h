/*
 * power.h
 *
 *  Created on: Apr 17, 2018
 *      Author: obu
 */

#ifndef POWER_H_
#define POWER_H_

#include "config.h"


void powerInit();
void chargerCurrentOFF();
void increaseChargerCurrent();
void reduceChargerCurrent();
void goRoundChargerCurrent();
void changeChargerCurrent() ;

void outVoltageOFF();
void increaseOutVoltage();
void reduceOutVoltage();
void goRoundOutVoltage();
void changeOutVoltage();


#endif /* POWER_H_ */
