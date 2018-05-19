/*
 * cell.h
 *
 *  Created on: Apr 22, 2018
 *      Author: obu
 */

#ifndef CELL_H_
#define CELL_H_

#include "config.h"

typedef enum {
	ABOVE_15_PERCENT, BELOV_15_PERCENT
} CapacityLevel;

volatile struct cell {
	volatile char name[6];
	volatile float voltage;
	volatile float estimatedStart_mAh;
	volatile float estimatedStart_Wh;
	volatile float estimatedCapacityPercent;
	volatile float used_mAh;
	volatile float used_Wh;
	volatile float maxCapacity;
	CapacityLevel capacityLevel;
};

uint16_t getEstimatedPercent_BP(struct cell cell1, struct cell cell2,
		struct cell cell3, struct cell cell4);

float minValue(float val1, float val2, float val3, float val4);

float getEstimatedRemainingTime(struct cell cell1, struct cell cell2,
		struct cell cell3, struct cell cell4);

void dischargingCell(struct cell* cell, float current, uint16_t time);

void refreshCellVoltage(struct cell* cell, float voltage);
void refreshCellCapacityPercent(struct cell* cell, float voltage);

float estimateRemaining_mAh_ByDeliveredEnergy(struct cell cell);

float estimateRemaining_Wh_ByDeliveredEnergy(struct cell cell);
float estimateRemainingCapacityPercentByVoltage(float voltage);
void initCell(struct cell* cell, char name[6], float maxCapacity,
		float voltage);

#endif /* CELL_H_ */
