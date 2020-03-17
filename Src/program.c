/*
 * program.c
 *
 *  Created on: 16 de mar de 2020
 *      Author: oscar
 */

#include "program.h"

//**************GLOBAL VARIABLES*********************************
Machine_States_t e_Current_Machine_State = INITIALIZING,
		e_Previous_Machine_State = NONE;

//*********************** CONTROL FUNCTIONS ***************************
void fn_Change_Machine_State(Machine_States_t state) {
	e_Previous_Machine_State = e_Current_Machine_State;
	e_Current_Machine_State = state;
}

void fn_start_program() {
	blink(20);
	LED_ON
	HAL_Delay(3000);
	fn_fprint("START PROGRAM\r\n");
	LED_OFF
	fn_init_sensors();
	fn_get_sensors_values();
	fn_send_daily_frame_sigfox();
}

void fn_run_program() {

		HAL_Delay(30000);
		fn_get_sensors_values();
		fn_send_report_frame_sigfox();
}

void serial_values() {
	fn_fprint("\r\n");
	fn_fprint("********* SENSORS VALUES ***********");
	fn_fprint("\r\n");
	fn_fprint("ANGLE: ");
	fn_fprintnumber((int)st_data_sensor_e.angle);
	HAL_Delay(1000);
	fn_fprint("°\r\n");
	fn_fprint("BATTERY: ");
	fn_fprintnumber((int)st_data_sensor_e.battery);
	HAL_Delay(1000);
	fn_fprint(" volts\r\n");
	fn_fprint("DISTANCE: ");
	fn_fprintnumber((int)st_data_sensor_e.distance);
	HAL_Delay(1000);
	fn_fprint(" cm\r\n");
	fn_fprint("TEMPERATURE: ");
	fn_fprintnumber((int)st_data_sensor_e.temperature);
	HAL_Delay(1000);
	fn_fprint(" c\r\n");
	fn_fprint("LATITUDE: ");
	fn_fprintnumber((int)st_data_sensor_e.latitude);
	HAL_Delay(1000);
	fn_fprint("\r\n");
	fn_fprint("LONGITUDE: ");
	fn_fprintnumber((int)st_data_sensor_e.longitude);
	HAL_Delay(1000);
	fn_fprint("\r\n");
	fn_fprint("VOLUME REFERENCE: ");
	fn_fprintnumber((int)st_data_sensor_e.referenceVol);
	HAL_Delay(1000);
	fn_fprint("\r\n");
	fn_fprint("VOLUME: ");
	fn_fprintnumber((int)st_data_sensor_e.volume);
	HAL_Delay(1000);
	fn_fprint("\r\n########################################\r\n");

}
