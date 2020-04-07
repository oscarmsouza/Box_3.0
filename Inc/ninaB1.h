/*
 * ninaB1.h
 *
 *  Created on: 6 de abr de 2020
 *      Author: oscar
 */

#ifndef NINAB1_H_
#define NINAB1_H_
#include "main.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sigfox.h"
#include "encoder.h"
#include "program.h"


UART_HandleTypeDef huart4;

#define BYTES_NINA_TO_RECEIVER	500

char responce_nina[BYTES_NINA_TO_RECEIVER];
char cofetest[8];
uint8_t byte_nina;
uint32_t NINAbytesToReceive;
char recever_nina_uart[100];

int fn_at_command_nina(char* at_command, unsigned int msDelay);
void fn_find_device_rssi(int devices_strength_seguence);
void fn_ninaB1();
int fn_set_perimetral_nina();

int fn_recever_nina(unsigned int sec_timeout);

#endif /* NINAB1_H_ */
