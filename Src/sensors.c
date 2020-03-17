/*
 * sensors.c
 *
 *  Created on: 16 de mar de 2020
 *      Author: oscar
 */

#include "sensors.h"

void fn_init_sensors() {
	fn_init_lsm303ah();
	fn_info_sigfox();
	fn_init_gps();
	st_data_sensor_e.angle = 0;
	st_data_sensor_e.battery = 0;
	st_data_sensor_e.distance = 0;
	st_data_sensor_e.latitude = 0;
	st_data_sensor_e.longitude = 0;
	st_data_sensor_e.referenceVol = 200;
	st_data_sensor_e.temperature = 0;
}

void fn_get_sensors_values() {
	st_data_sensor_previwes_e.angle = st_data_sensor_e.angle;
	st_data_sensor_previwes_e.battery = st_data_sensor_e.battery;
	st_data_sensor_previwes_e.distance = st_data_sensor_e.distance;
	st_data_sensor_previwes_e.latitude = st_data_sensor_e.latitude;
	st_data_sensor_previwes_e.longitude = st_data_sensor_e.longitude;
	st_data_sensor_previwes_e.referenceVol = st_data_sensor_e.referenceVol;
	st_data_sensor_previwes_e.temperature = st_data_sensor_e.temperature;
	 fn_get_angle_value();
	 fn_get_volume_value();
	 fn_get_lat_lon_values();
	 fn_get_temperature_value();
	 fn_get_battery_value();
	 serial_values();
}

void fn_get_angle_value() {
	fn_get_lsm303ah();
	if (st_accelerometer.pitch < 0)
		st_accelerometer.pitch *= (-1);
	st_data_sensor_e.angle = round (st_accelerometer.pitch/10);
}

void fn_get_volume_value() {
	st_data_sensor_e.distance = fn_get_sen031x();
	if (st_data_sensor_e.distance < VOL_MIN) {
		st_data_sensor_e.volume = 10;
	} else if (st_data_sensor_e.distance >= st_data_sensor_e.referenceVol) {
		st_data_sensor_e.volume = 0;
	} else {
		float vol_perc = st_data_sensor_e.distance * 100;
		vol_perc /= st_data_sensor_e.referenceVol;
		vol_perc = 100 - vol_perc;
		vol_perc /= 10;
		vol_perc = round(vol_perc);
		int test = (uint32_t) (vol_perc);
		st_data_sensor_e.volume = test;
	}
}

void fn_get_lat_lon_values()
{
	fn_get_gps();
	fn_get_longitude_value();
	fn_get_latitude_value();
}

void fn_get_latitude_value() {
	st_data_sensor_e.latitude = st_gps_data_current.latitude;
}

void fn_get_longitude_value() {
	st_data_sensor_e.longitude = st_gps_data_previous.longitude;
}

void fn_get_temperature_value() {
	SIGFOX_ON
	fn_init_sigfox();
	fn_get_stm32_temperature();
	fn_get_temperature_sigfox();
	SIGFOX_OFF
	if (st_stm_adc_variables.temperature != 0 && int_temp_sigfox != 0) {
		st_data_sensor_e.temperature = (st_stm_adc_variables.temperature
				+ int_temp_sigfox)/2;
	}else 	if (st_stm_adc_variables.temperature == 0 && int_temp_sigfox != 0) {
		st_data_sensor_e.temperature =  int_temp_sigfox;
	}else 	if (st_stm_adc_variables.temperature != 0 && int_temp_sigfox == 0) {
		st_data_sensor_e.temperature =  st_stm_adc_variables.temperature;
	}
}

void fn_get_battery_value() {
	SIGFOX_ON
	HAL_Delay(500);
	fn_get_id_sigfox();
	fn_get_stm32_volts();
	fn_get_volt_sigfox();
	SIGFOX_OFF

	if(st_stm_adc_variables.battery==0)
	{
		st_data_sensor_e.battery = int_volt_sigfox;
	}else{
		st_data_sensor_e.battery = (st_stm_adc_variables.battery*10);
	}

}
