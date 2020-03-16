/*
 * gps.h
 *
 *  Created on: 11 de mar de 2020
 *      Author: oscar
 */

#ifndef GPS_H_
#define GPS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sigfox.h>
#include "encoder.h"

typedef struct {
	uint32_t
	quality,
	hour,
	minute,
	second,
	latitude,
	longitude,
	altitude,
	numSV,
	speed;
} st_gps_data;

st_gps_data st_gps_data_current;
st_gps_data st_gps_data_previous;

void find_between(const char *first, const char *last, char *buff,
		char *buff_return);

void fn_init_gps();

void fn_get_gps();

void fn_print_gps();

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* GPS_H_ */

