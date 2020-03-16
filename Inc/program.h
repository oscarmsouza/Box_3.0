/*
 * program.h
 *
 *  Created on: 16 de mar de 2020
 *      Author: oscar
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_
#include "main.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sigfox.h"
#include "encoder.h"
#include "gprs.h"
#include "lsm303ah_reg.h"
#include "gps.h"
#include "sen031x.h"
#include "sensors.h"


/*************************************************************************************************/
/*    ENUMS                                                                                      */
/*************************************************************************************************/
typedef enum {
	NONE,
	INITIALIZING,
	ERRO,
	TEST,
	COUNTER,
	SEND_UPLINK,
	SEND_DOWNLINK,
	SEND_ALERT,
} Machine_States_t;


void fn_Change_Machine_State(Machine_States_t state);
void fn_start_program();
void fn_run_program();
void serial_values();

#endif /* PROGRAM_H_ */
