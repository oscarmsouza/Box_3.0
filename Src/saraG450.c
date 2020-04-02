/*
 * saraG450.c
 *
 *  Created on: 30 de mar de 2020
 *      Author: oscar
 */

#include "saraG450.h"

void fn_power_on_sara(void) { //to power on call this
	fn_fprint("\r\nPOWER ON SARA MODULE\r\n");
	GPRS_ON
	HAL_Delay(1000);
	GPRS_RESET_OFF
	HAL_Delay(3000);
	GPRS_PWR_ON
	HAL_Delay(10000);
	fn_fprint("SARA MUDULE RUN\r\n");
}

/*
 * first at commands you send and verify cell chip
 * if one this events does not work ok the module torn off
 */
void fn_start_at_commands_sara(void) {
	//fn_power_on_sara();
	int timeToScape = 10;

	while (!fn_at_command_sara("AT&K0", 100) && timeToScape != 0) {
		HAL_Delay(100);
		timeToScape--;
	}
	if (!fn_at_command_sara("AT", 100)) {
		fn_fprint("AT COMMAND DONT START");
		fn_power_off_sara();

	}
	if (!fn_at_command_sara("AT+CPIN?", 100)) {
		fn_fprint("CHIP DONT START");
		fn_power_off_sara();
	}
}

void fn_get_module_info_sara(void) { //call this one time if you need
	//  Manufacturer identification +CGMI
	fn_at_command_sara("AT+CGMI", 100);
	// Model identification +CGMM
	fn_at_command_sara("AT+CGMM", 100);
	//  Firmware version identification +CGMR
	fn_at_command_sara("AT+CGMR", 100);
	// IMEI identification +CGSN
	fn_at_command_sara("AT+CGSN", 100);

}

void fn_network_configuration_sara(void) {	//call this one time

	//  Packet switched data configuration +UPSD
	//DEFINE PROFILE 1 - VIVO
	//defines  the  APN  operator
	fn_at_command_sara("AT+UPSD=1,1,\"zap.vivo.com.br\"", 200);
	//defines  the  APN username
	fn_at_command_sara("AT+UPSD=1,2,\"vivo\"", 200);
	//defines  the  APN  password
	fn_at_command_sara("AT+UPSD=1,3,\"vivo\"", 200);
	//DEFINE PROFILE 2 - TIM
	//defines  the  APN  operator
	fn_at_command_sara("AT+UPSD=2,1,\"timbrasil.br\"", 200);
	//defines  the  APN username
	fn_at_command_sara("AT+UPSD=2,2,\"tim\"", 200);
	//defines  the  APN  password
	fn_at_command_sara("AT+UPSD=2,3,\"tim\"", 200);
	//DEFINE PROFILE 3 - CLARO
	//defines  the  APN  operator
	fn_at_command_sara("AT+UPSD=3,1,\"claro.com.br\"", 200);
	//defines  the  APN username
	fn_at_command_sara("AT+UPSD=3,2,\"claro\"", 200);
	//defines  the  APN  password
	fn_at_command_sara("AT+UPSD=3,3,\"claro\"", 2000);
	/*	//DEFINE PROFILE 4 - OI
	 //defines  the  APN  operator
	 fn_at_command_sara("AT+UPSD=4,1,\"gprs.oi.com.br\"", 200);
	 //defines  the  APN username
	 fn_at_command_sara("AT+UPSD=4,2,\"oi\"", 200);
	 //defines  the  APN  password
	 fn_at_command_sara("AT+UPSD=4,3,\"oi\"", 200);*/
}

void fn_network_activation_sara(void) {	//call ever time you reset the module

	int TimeToScape = 3;
	//    GPRS attach or detach +CGATT
	fn_at_command_sara("AT+CGATT?", 300);
	if (!find_word(responce_sara, "+CGATT:1")) {
		fn_at_command_sara("AT+CGATT=1", 20000);
		while (!find_word(responce_sara, "+CGATT:1") && TimeToScape != 0) {
			TimeToScape--;
			fn_at_command_sara("AT+CGATT=1", 5000);
		}
	}
	/*//  Network registration status +CREG
	 fn_at_command_sara("AT+CREG?", 300);
	 if (!find_word(responce_sara, "+CREG:1")) {
	 while (!find_word(responce_sara, "+CREG: 1")&& try != 0) {
	 fn_at_command_sara("AT+CREG=1", 10000);
	 fn_at_command_sara("AT+CREG?", 300);
	 try--;
	 }
	 try=5;
	 }*/

	//  Operator selection +COPS
	fn_at_command_sara("AT+COPS?", 300);

	//Activate the GPRS connection ()
	if (find_word(responce_sara, "VIVO")) {
		e_operador_select = VIVO;
		//  Packet switched data action +UPSDA
		fn_at_command_sara("AT+UPSDA=1,3", 2000);
		// Packet switched network-assigned data +UPSND
		fn_at_command_sara("AT+UPSND=1,0", 2000);
		if (find_word(responce_sara, "+UPSND: 1,0,\"\"")) {
			fn_at_command_sara("AT+UPSND=1,0", 2000);
		}

	} else if (find_word(responce_sara, "TIM")) {
		e_operador_select = TIM;
		//  Packet switched data action +UPSDA
		fn_at_command_sara("AT+UPSDA=2,3", 2000);
		// Packet switched network-assigned data +UPSND
		fn_at_command_sara("AT+UPSND=2,0", 2000);

	} else if (find_word(responce_sara, "CLARO")) {
		e_operador_select = CLARO;
		//  Packet switched data action +UPSDA
		fn_at_command_sara("AT+UPSDA=3,3", 2000);
		// Packet switched network-assigned data +UPSND
		fn_at_command_sara("AT+UPSND=3,0", 2000);

	} else if (find_word(responce_sara, "OI")) {
		e_operador_select = OI;
		//  Packet switched data action +UPSDA
		fn_at_command_sara("AT+UPSDA=4,3", 2000);
		// Packet switched network-assigned data +UPSND
		fn_at_command_sara("AT+UPSND=4,0", 2000);

	}

}

void fn_http_mensage_sara(int type_mensage) {
	switch (type_mensage) {
	case DAILY_UPDATE_FRAME:
		//Reset the HTTP profile #0 OF 3
		fn_at_command_sara("AT+UHTTP=0", 100);
		//Set the server domain name and port.
		fn_at_command_sara("AT+UHTTP=0,1,\"wizebox-api-dev.herokuapp.com\"",
				300);
		//Function mount the payload command
		fn_mount_frame_sara(DAILY_UPDATE_FRAME);
		//GET request of the default page
		fn_at_command_sara(uhttpc_comand_frame, 5000);
		// Check the server's reply data
		//fn_at_command_sara("AT+URDFILE=\"uplink.fss\"", 100);
		break;
	case CONFIG_FRAME:
		//Delete fss file
		fn_at_command_sara("AT+UDELFILE=\"downlink.fss\"", 200);
		//Reset the HTTP profile #0 OF 3
		fn_at_command_sara("AT+UHTTP=1", 500);
		//Set the server domain name and port.
		fn_at_command_sara("AT+UHTTP=1,1,\"wizebox-api-dev.herokuapp.com\"",
				500);
		//Function mount the payload command
		fn_mount_frame_sara(CONFIG_FRAME);
		//GET request of the default page
		fn_at_command_sara(uhttpc_comand_frame, 10000);

		// Check the server's reply data
		fn_at_command_sara("AT+URDFILE=\"downlink.fss\"", 5000);
		HAL_Delay(200);
		break;
	default:
		break;

	}
}

void fn_power_off_sara(void) {	//to power off call this
	fn_fprint("\r\nSARA MODULE SWITCH OFF\r\n");
	fn_at_command_sara("AT+CPWROFF", 200);
	GPRS_OFF
	HAL_Delay(100);
	GPRS_PWR_OFF
	HAL_Delay(100);
	fn_fprint("SARA MUDULE OFF\r\n");
}

/*
 *
 *
 * COMMAND FUNCIONS
 *
 *
 *
 */

/*
 * int fn_get_imei_sara()
 * if you need to check the imei number call this
 * the string number allocate in char sara_imei
 * return the number of imei in decimal int
 *
 */
int fn_get_imei_sara() {
	fn_at_command_sara("AT+CGSN", 100);
	int counter_mei = 0;
	int imei = 0;
	//char responce_sara[BYTES_TO_RECEIVER];
	for (int var = 0; var < BYTES_TO_RECEIVER; var++) {
		if (responce_sara[var] > 47 && responce_sara[var] < 58
				&& responce_sara[var] != 0) {
			sara_imei[counter_mei] = responce_sara[var];
			if (counter_mei == 15)
				break;
			counter_mei++;
			imei = 1;
		}
	}
	return imei;
}

/*
 * int fn_at_command_sara(char* at_command, int msDelay)
 * function send at command and counter millisecond delay (enter values)
 * Return 0 if the at command don't return OK and 1 if return OK
 */
int fn_at_command_sara(char* at_command, unsigned int msDelay) {
	int return_flag = 0;
	int size_at_command = strlen(at_command);
	size_at_command += 3;
	char new_command[size_at_command];
	char GSMreceiver[BYTES_TO_RECEIVER] = { 0 };
	memset(responce_sara, 0, BYTES_TO_RECEIVER);

	strcpy(new_command, at_command);
	strcat(new_command, "\r\n\0");
	//uint8_t* new_com = (uint8_t*) new_command;
	HAL_UART_Transmit_DMA(&huart5, (uint8_t*) &new_command, size_at_command);
	while (UartReady != SET) {
	}
	UartReady = RESET;

	HAL_UART_Receive_DMA(&huart5, (uint8_t*) &GSMreceiver,
	BYTES_TO_RECEIVER);
	LED_ON
	HAL_Delay(msDelay);
	LED_OFF
	huart5.pRxBuffPtr = (uint8_t*) &GSMreceiver;
	huart5.RxXferCount = 0;

	int size_response_uart = 0;

	for (int var = 0; var < BYTES_TO_RECEIVER; var++) {
		if (GSMreceiver[var] != 0 && GSMreceiver[var] < 128) {
			++size_response_uart;
		}
	}
	char sendResponse[size_response_uart];
	int counter_size = 0;

	for (int var = 0; var < BYTES_TO_RECEIVER; var++) {
		if (GSMreceiver[var] != 0 && GSMreceiver[var] < 128) {
			sendResponse[counter_size] = GSMreceiver[var];
			responce_sara[counter_size] = GSMreceiver[var];
			++counter_size;
			if (GSMreceiver[var - 1] == 79 && GSMreceiver[var] == 75) {
				return_flag = 1;
			}
		}
	}
	//HAL_UART_Transmit_IT(&hlpuart1, (uint8_t*) sendResponse,size_response_uart);
	fn_fprint(sendResponse);

	return return_flag;
}

/*
 * AUXILIAR FUNCIONS - PAYLOAD
 */

void fn_mount_frame_sara(int type_frame) {
	memset(st_frame_type.frame_report_values, 0, 22);
	memset(uhttpc_comand_frame, 0, 80);
	fn_get_imei_sara();
	fn_encoder_report_frame(st_frame_type.frame_report_values);

	switch (type_frame) {
	case DAILY_UPDATE_FRAME:
		strcpy(uhttpc_comand_frame, "AT+UHTTPC=0,1,\"/sigfox/uplink?device=");
		strcat(uhttpc_comand_frame, sara_imei);
		strcat(uhttpc_comand_frame, "&data=");
		strcat(uhttpc_comand_frame, st_frame_type.frame_report_values);
		strcat(uhttpc_comand_frame, "\",\"uplink.fss\"");
		break;
	case CONFIG_FRAME:
		strcpy(uhttpc_comand_frame,
				"AT+UHTTPC=1,1,\"/gprs/bidir?ack=true&device=");
		strcat(uhttpc_comand_frame, sara_imei);
		strcat(uhttpc_comand_frame, "&data=");
		strcat(uhttpc_comand_frame, st_frame_type.frame_report_values);
		strcat(uhttpc_comand_frame, "\",\"downlink.fss\"");
		break;
	default:
		break;
	}
}
