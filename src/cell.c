/*
 * cell.c
 *
 *  Created on: Apr 22, 2018
 *      Author: obu
 */

#include "cell.h"
#include "config.h"
#include "lcd.h"

uint16_t getEstimatedPercent_BP(struct cell cell1, struct cell cell2,
		struct cell cell3, struct cell cell4) {

	float min = cell1.estimatedCapacityPercent;
	if (cell2.estimatedCapacityPercent < min)
		min = cell2.estimatedCapacityPercent;
	if (cell3.estimatedCapacityPercent < min)
		min = cell3.estimatedCapacityPercent;
	if (cell4.estimatedCapacityPercent < min)
		min = cell4.estimatedCapacityPercent;

	return (uint16_t) cell1.estimatedCapacityPercent * 100;
}

float minValue(float val1, float val2, float val3, float val4) {

	float min = val1;

	if (val2 < min)
		min = val2;

	if (val3 < min)
		min = val3;

	if (val4 < min)
		min = val4;

	return min;
}

float getEstimatedRemainingTime(struct cell cell1, struct cell cell2,
		struct cell cell3, struct cell cell4) {
	return minValue(estimateRemaining_mAh_ByDeliveredEnergy(cell1),
			estimateRemaining_mAh_ByDeliveredEnergy(cell2),
			estimateRemaining_mAh_ByDeliveredEnergy(cell3),
			estimateRemaining_mAh_ByDeliveredEnergy(cell4))
			/ (currentDischarge.currValue * 1000);
}

void dischargingCell(struct cell* cell, float current, uint16_t time) {
	//milliseconds to hours -> miliseconds/ tosec / 60 / 60
	float hourTime = (((float) time) / 20 / 60 / 60);
	cell->used_mAh = cell->used_mAh + (current * (hourTime));
	cell->used_Wh = cell->used_Wh
			+ (current / 1000/*to A*/* cell->voltage * (hourTime));
}

void refreshCellVoltage(struct cell* cell, float voltage) {
	cell->voltage = voltage;

}

void refreshCellCapacityPercent(struct cell* cell, float voltage) {
	cell->estimatedCapacityPercent = estimateRemainingCapacityPercentByVoltage(
			voltage);
}

float estimateRemaining_mAh_ByDeliveredEnergy(struct cell cell) {
	return cell.estimatedStart_mAh - cell.used_mAh;
}

float estimateRemaining_Wh_ByDeliveredEnergy(struct cell cell) {
	return cell.estimatedStart_Wh - cell.used_Wh;
}

float estimateRemainingCapacityPercentByVoltage(float voltage) {
	float ret = 1
			- ((voltage - (float) MAX_CELL_VOLTAGE)
					/ -(((float) VOLTAGE_AT_HIGH_PERCENT_OF_CAPACITY
							- (float) VOLTAGE_AT_LOW_PERCENT_OF_CAPACITY)
							/ ((float) HIGH_PERCENT_OF_CAPACITY
									- (float) LOW_PERCENT_OF_CAPACITY)));
	return ret;
}

void initCell(struct cell* cell, char name[6], float maxCapacity, float voltage) {
	int i;
	for (i = 0; i < 6; i++) {
		cell->name[i] = name[i];
	}
	cell->maxCapacity = maxCapacity;
	cell->voltage = voltage;
	cell->estimatedStart_mAh = maxCapacity
			* estimateRemainingCapacityPercentByVoltage(voltage);
	cell->estimatedStart_Wh = maxCapacity * voltage
			* estimateRemainingCapacityPercentByVoltage(voltage);
	cell->estimatedCapacityPercent = estimateRemainingCapacityPercentByVoltage(
			voltage);
	cell->used_Wh = 0;
	cell->used_mAh = 0;
}
