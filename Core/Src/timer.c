/*
 * timer.c
 *
 *  Created on: Feb 7, 2025
 *      Author: npedu-204-04
 */

#include "timer.h"

TIM_HandleTypeDef	*timerHtim;

void initTimer(TIM_HandleTypeDef *inHtim) {
	timerHtim = inHtim;
	HAL_TIM_Base_Start(timerHtim);
}

void DelayUs(uint16_t time) {
	timerHtim->Instance->CNT = 0;
	while(timerHtim->Instance->CNT < time);
}
