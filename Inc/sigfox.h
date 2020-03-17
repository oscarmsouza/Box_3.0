/*
 * sigfox.h
 *
 *  Created on: 9 de mar de 2020
 *      Author: oscar
 */

#ifndef SIGFOX_H_
#define SIGFOX_H_

#include <main.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "encoder.h"
#include "gprs.h"
#include "lsm303ah_reg.h"
#include "gps.h"
#include "sen031x.h"
#include "sensors.h"
#include "program.h"

#define DONGLE_KEY
UART_HandleTypeDef huart1;

int int_temp_sigfox, int_volt_sigfox;

struct {
	char
	id[10],
	pac[18],
	temperature[7],
	volts[6],
	at[4];
} st_sigfox_parameters;

struct{
	char
	test[24],
	frame_report_values[22];
}st_sigfox_frame;

void fn_init_sigfox();
void fn_get_id_sigfox();
void fn_get_pac_sigfox();
void fn_at_sigfox();
void fn_get_volt_sigfox();
void fn_get_temperature_sigfox();
void fn_send_frame_sigfox(char* frame);
void fn_send_start_frame_sigfox();
void fn_info_sigfox();
void fn_status_sigfox();
void fn_send_report_frame_sigfox();
void fn_reset_sigfox();
void fn_send_daily_frame_sigfox();


#endif /* SIGFOX_H_ */
