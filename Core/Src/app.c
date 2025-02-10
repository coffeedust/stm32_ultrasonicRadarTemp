/*
 * app.c
 *
 *  Created on: Feb 4, 2025
 *      Author: npedu-204-04
 */

#include "app.h"

extern UART_HandleTypeDef	huart2;
extern TIM_HandleTypeDef	htim1;
extern TIM_HandleTypeDef	htim3;
extern TIM_HandleTypeDef	htim11;

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setServo(uint8_t angle) {
	htim1.Instance->CCR1 = map(angle, 0, 180, 500-1, 2300-1);
}

void app() {
	initTimer(&htim11);
	initUart(&huart2);
	initUltrasonic(&htim3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	while(1) {
		// 각도를 수신받음 : A000\n ~ A180\n
		char *msg = getMessage();
		if(strlen(msg) >= 4) {
			if(msg[0] == 'A') {
				uint16_t angle = atoi(&msg[1]);
				// 서보를 해당 각도로 이동
				setServo(angle);
				HAL_Delay(100);
				// 거리측정
				uint16_t distance = getDistance();
				// 거리 정보 송신 : D000\n ~ D999\n
				printf("D%03d\n", distance);
			}
		}
	}
}
