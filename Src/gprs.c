/*
 * gprs.c
 *
 *  Created on: 9 de mar de 2020
 *      Author: oscar
 */


#include "gprs.h"

void fn_init_gprs(){
	char command[7] = "AT&K0\r\n";
	char ok[10]={0};
		HAL_UART_Transmit(&huart5, (uint8_t*) command, 7,200);
		HAL_Delay(25);
		HAL_UART_Receive(&huart5, (uint8_t*) ok, 10,500);
		HAL_Delay(200);

}

