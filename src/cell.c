/*
 * cell.c
 *
 *  Created on: Apr 22, 2018
 *      Author: obu
 */

#include "cell.h"
#include "config.h"

void dischargingCell(struct cell* cell, uint8_t current, uint16_t time) {
	float timeInHours = time / 1000 / 60 / 60;
	cell->used_mAh += current * timeInHours;
	cell->used_Wh += current *cell->voltage* timeInHours;
}

int refreshCellVoltage(struct cell* cell, float voltage) {
	cell->voltage = voltage;
	if (voltage < MAX_CELL_VOLTAGE && voltage > MIN_CELL_VOLTAGE)
		return 0;
	else
		return -1;
}

float estimateRemaining_mAh_ByDeliveredEnergy(struct cell cell) {
	return cell.estimatedStart_mAh - cell.used_mAh;
}

float estimateRemaining_Wh_ByDeliveredEnergy(struct cell cell) {
	return cell.estimatedStart_mAh - cell.used_mAh;
}

float estimateRemainingCapacityPercentByVoltage(struct cell cell) {
	float ret = 1
			- ((cell.voltage - (float) MAX_CELL_VOLTAGE)
					/ -(((float) VOLTAGE_AT_HIGH_PERCENT_OF_CAPACITY
							- (float) VOLTAGE_AT_LOW_PERCENT_OF_CAPACITY)
							/ ((float) HIGH_PERCENT_OF_CAPACITY
									- (float) LOW_PERCENT_OF_CAPACITY)));
	if (ret * 100 >= LOW_PERCENT_OF_CAPACITY) {
		return ret;
	} else
		return -1.0;
}

void initCell(struct cell* cell, char name[6], float maxCapacity, float voltage) {
	int i;
	for (i = 0; i < 6; i++)
		cell->name[i] = name[i];
	cell->maxCapacity = maxCapacity;
	cell->voltage = voltage;
	cell->estimatedStart_mAh = maxCapacity*estimateRemainingCapacityPercentByVoltage(*cell);
	cell->estimatedCapacityPercent=estimateRemainingCapacityPercentByVoltage(*cell);
}
