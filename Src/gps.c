/*
 * gps.c
 *
 *  Created on: 11 de mar de 2020
 *      Author: oscar
 */

#include "gps.h"

UART_HandleTypeDef hlpuart1;

//extern unsigned int hora,lat_value,lon_value;

void fn_init_gps() {
	/*	st_flags.gps = false;
	 st_data_sensor_e.lat_value = 0;
	 st_data_sensor_e.log_value = 0;
	 st_data_sensor_previwes_e.log_value = 0;
	 st_data_sensor_previwes_e.lat_value = 0;*/
	//fn_get_gps();
	GPS_ON
	st_gps_data_current.altitude = 0;
	st_gps_data_current.hour = 0;
	st_gps_data_current.latitude = 0;
	st_gps_data_current.longitude = 0;
	st_gps_data_current.minute = 0;
	st_gps_data_current.numSV = 0;
	st_gps_data_current.quality = 0;
	st_gps_data_current.second = 0;
	st_gps_data_current.speed = 0;

}

void fn_get_gps() {

	st_gps_data_previous.altitude = st_gps_data_current.altitude;
	st_gps_data_previous.hour = st_gps_data_current.hour;
	st_gps_data_previous.latitude = st_gps_data_current.latitude;
	st_gps_data_previous.longitude = st_gps_data_current.longitude;
	st_gps_data_previous.minute = st_gps_data_current.minute;
	st_gps_data_previous.numSV = st_gps_data_current.numSV;
	st_gps_data_previous.quality = st_gps_data_current.quality;
	st_gps_data_previous.second = st_gps_data_current.second;
	st_gps_data_previous.speed = st_gps_data_current.speed;

	//***************GPS VARIABLES**********************************
	float data_latitude, data_longitude, data_altitude;
	int data_qualidade, data_numSV;
	char buffer_gps[1024] = "";
	char aux_buff_gps[74] = "";
	uint32_t hora;
	struct {
		char lat[12], lon[12], hra[10], NS[1], EW[1], numSV[2], speed[6],
				quality[2], alt[8];
	} aux;

	//st_data_sensor_previwes_e.lat_value = st_data_sensor_e.lat_value;
	//st_data_sensor_previwes_e.log_value = st_data_sensor_e.log_value;

	HAL_UART_Init(&hlpuart1);
	HAL_UART_Receive(&hlpuart1, (uint8_t*) buffer_gps, 1024, 2000);
	//HAL_UART_Transmit(&hlpuart1, (uint8_t*) buffer_gps, 1024, 2000);
	//fn_fprint(buffer_gps);

	/*	 Message Structure:
	 *
	 $xxVTG,cogt,cogtUnit,cogm,cogmUnit,sogn,sognUnit,sogk,sogkUnit,posMode*cs<CR><LF>
	 Example:
	 $GPVTG,77.52,T,,M,0.004,N,0.008,K,A*06
	 ****************************************************************************************
	 *FieldNo. 	* Name 		*	Unit	*	Format		*	Example	*		Description		*
	 *   4  	* cogmUnit  *  -    	* 	character  	*  	  M   	*   Course over ground 	*
	 *   5  	* sogn      * 	knots 	* 	numeric    	* 	0.004 	*   Speed over ground	*
	 *   7  	* sogk      * 	km/h  	* 	numeric    	* 	0.008 	*   Speed over ground	*
	 ****************************************************************************************
	 $xxGGA,time,lat,NS,lon,EW,quality,numSV,HDOP,alt,altUnit,sep,sepUnit,diffAge,diffStation*cs<CR><LF>
	 Example:
	 $GPGGA,092725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B*/
	find_between("GGA,", "\n", buffer_gps, aux_buff_gps);
	fn_fprint(aux_buff_gps);
	fn_fprint(".\r\n");
	if (strlen(aux_buff_gps) > 30) {
		uint8_t c = 0;
		char* token;
		token = strtok(aux_buff_gps, ",");
		while (token != NULL) {
			if (c == 0) {
				strcpy(aux.hra, token);
			}
			if (c == 1) {
				strcpy(aux.lat, token);
			}
			if (c == 2) {
				strcpy(aux.NS, token);
			}
			if (c == 3) {
				strcpy(aux.lon, token);
			}
			if (c == 4)
				strcpy(aux.EW, token);
			if (c == 5) {
				strcpy(aux.quality, token);
			}
			if (c == 6) {
				strcpy(aux.numSV, token);
			}
			if (c == 7) {
			}
			if (c == 8) {
				strcpy(aux.alt, token);
			}
			if (c == 9)
				token = NULL;
			c++;
			token = strtok(NULL, ",");
		}

		hora = atoi(aux.hra);              // hora (hh.mm.ss)
		data_latitude = atof(aux.lat);      // latitude
		data_longitude = atof(aux.lon);     // longitude
		data_altitude = atof(aux.alt);
		data_numSV = atoi(aux.numSV);
		data_qualidade = atoi(aux.quality);
		st_gps_data_current.hour = hora / 10000;
		st_gps_data_current.minute = (hora - (st_gps_data_current.hour * 10000))
				/ 100;
		st_gps_data_current.second = (hora
				- ((st_gps_data_current.hour * 10000)
						+ (st_gps_data_current.minute * 100)));
		if (hora != 0) {
			switch (st_gps_data_current.hour) {
			case 2:
				st_gps_data_current.hour = 23;
				break;
			case 1:
				st_gps_data_current.hour = 22;
				break;
			case 0:
				st_gps_data_current.hour = 21;
				break;
			default:
				st_gps_data_current.hour -= 3;
				break;
			}
		}

		if ((data_latitude != 0) && (data_longitude != 0)) {
			//st_flags.gps = true;
			data_latitude /= 100;
			data_longitude /= 100;
			uint32_t lat_graus = (uint32_t) data_latitude;
			uint32_t lon_graus = (uint32_t) data_longitude;
			uint32_t lat_min = (data_latitude - lat_graus) * 100;
			uint32_t lon_min = (data_longitude - lon_graus) * 100;
			data_latitude = lat_graus + (lat_min / 60);
			data_longitude = lon_graus + (lon_min / 60);
			data_latitude = 100000 * data_latitude;
			data_longitude = 100000 * data_longitude;
			st_gps_data_current.longitude = data_latitude;
			st_gps_data_current.longitude = data_longitude;
			st_gps_data_current.altitude = (uint32_t) data_altitude * 10;
			st_gps_data_current.quality = (uint32_t) data_qualidade;
			st_gps_data_current.numSV = (uint32_t) data_numSV;
			GPS_OFF
		} else {
			st_gps_data_current.longitude = 0;
			st_gps_data_current.longitude = 0;
			st_gps_data_current.altitude = 0;
			st_gps_data_current.quality = 0;
			st_gps_data_current.numSV = 0;
			GPS_OFF
		}

	}
}

void fn_print_gps() {
	char numbuff[] = "\0";
	fn_fprint("\r\n");
	fn_fprint("********* GPS ***********");
	fn_fprint("\r\n");
	fn_fprint("LATITUDE: ");
	itoa(st_gps_data_current.longitude, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("\r\n");
	fn_fprint("LONGITUDE: ");
	itoa(st_gps_data_current.longitude, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("\r\n");
	fn_fprint("GPS HOUR: ");
	itoa(st_gps_data_current.hour, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("\r\n");
	fn_fprint("GPS MINUTE: ");
	itoa(st_gps_data_current.minute, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("\r\n");
	fn_fprint("GPS SECOND: ");
	itoa(st_gps_data_current.second, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("\r\n");
	fn_fprint("SIGNAL QUALITY: ");
	itoa(st_gps_data_current.second, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("\r\n");
	fn_fprint("ALTITUDE: ");
	itoa(st_gps_data_current.second, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("\r\n");
	fn_fprint("NUMBER SATELLITES: ");
	itoa(st_gps_data_current.second, numbuff, 10);
	fn_fprint(numbuff);
	HAL_Delay(100);
	fn_fprint("*********************\r\n");

}
