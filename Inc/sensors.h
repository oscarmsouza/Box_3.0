/*
 * sensors.h
 *
 *  Created on: 16 de mar de 2020
 *      Author: oscar
 */

#ifndef SENSORS_H_
#define SENSORS_H_

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

#define VOL_MIN		20

typedef struct {
	//e_uplink_frames_type_t header;
	uint32_t angle, battery, distance, temperature, latitude, longitude,
			referenceVol, volume;

} st_sensors_data_t;

st_sensors_data_t st_data_sensor_e;
st_sensors_data_t st_data_sensor_previwes_e;


void fn_init_sensors();
void fn_get_sensors_values();
void fn_get_angle_value();
void fn_get_volume_value();
void fn_get_latitude_value();
void fn_get_longitude_value();
void fn_get_temperature_value();
void fn_get_battery_value();
void fn_get_lat_lon_values();

#endif /* SENSORS_H_ */
