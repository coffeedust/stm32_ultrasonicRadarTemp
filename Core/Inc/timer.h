/*
 * timer.h
 *
 *  Created on: Feb 7, 2025
 *      Author: npedu-204-04
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

void initTimer(TIM_HandleTypeDef *inHtim);
void DelayUs(uint16_t time);

#endif /* INC_TIMER_H_ */
