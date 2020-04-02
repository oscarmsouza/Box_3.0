/*
 * saraG450.h
 *
 *  Created on: 30 de mar de 2020
 *      Author: oscar
 */

#ifndef SARAG450_H_
#define SARAG450_H_
#include "main.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sigfox.h"
#include "encoder.h"
#include "program.h"


#define BYTES_TO_RECEIVER	500
#define MAX_TRY_TO_CONECT 	5

UART_HandleTypeDef huart5;

int fn_get_imei_sara();
int fn_at_command_sara(char* at_command, unsigned int msDelay);
void fn_power_on_sara(void);
void fn_power_off_sara(void);
void fn_get_module_info_sara(void);
void fn_network_configuration_sara(void);
void fn_start_at_commands_sara(void);
void fn_network_activation_sara(void);
void fn_mount_frame_sara(int type_frame);
void fn_http_mensage_sara(int type_mensage);

uint8_t byte, gsmbyte;



char responce_sara[BYTES_TO_RECEIVER];
char sara_imei[15];
char uhttpc_comand_frame[200];

enum{
	NON,
	VIVO,
	TIM,
	CLARO,
	OI
}e_operador_select;

#endif /* SARAG450_H_ */
