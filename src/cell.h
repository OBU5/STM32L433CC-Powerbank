/*
 * cell.h
 *
 *  Created on: Apr 22, 2018
 *      Author: obu
 */

#ifndef CELL_H_
#define CELL_H_

struct cell {
	char name[6];
	float voltage;
	float estimatedStart_mAh;
	float estimatedCapacityPercent;
	float used_mAh;
	float used_Wh;
	float maxCapacity;
};

#endif /* CELL_H_ */
