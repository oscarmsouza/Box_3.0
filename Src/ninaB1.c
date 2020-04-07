/*
 * ninaB1.c
 *
 *  Created on: 6 de abr de 2020
 *      Author: oscar
 */

#include "ninaB1.h"

void fn_ninaB1() {

	BLE_OFF
	LED_OFF
	HAL_Delay(10000);
	BLE_ON
	LED_ON
	HAL_Delay(1000);

	fn_at_command_nina("AT", 1000);
	fn_at_command_nina("AT+UBTLE=1", 1000);
	fn_at_command_nina("AT&W", 1000);
	fn_at_command_nina("AT+UBTLN=\"WIZE TEST CENTRAL BLE\"", 1000);
	fn_at_command_nina("AT+UBTD", 5000);
	fn_at_command_nina("AT+UDCP=sps://CCF9578580A3p", 2000);
	HAL_Delay(1000);
	fn_at_command_nina("ATO1", 1000);
	HAL_Delay(1000);
	fn_at_command_nina("teste", 1000);

	BLE_OFF
	LED_OFF
}

void fn_find_device_rssi(int devices_strength_seguence) {
	uint8_t c = 0;
	char* token;
	token = strtok(responce_nina, ",");
	while (token != NULL) {
		if (c == 0) {

		}
		if (c == 1) {

		}
		if (c == 2) {

		}
		if (c == 3) {

		}
		if (c == 4)

			if (c == 5) {

			}
		if (c == 6) {

		}
		if (c == 7) {
		}
		if (c == 8) {

		}
		if (c == 9)
			token = NULL;
		c++;
		token = strtok(NULL, ",");
	}

}

int fn_at_command_nina(char* at_command, unsigned int msDelay) {
	int return_flag = 0;
	int size_at_command = strlen(at_command);
	size_at_command += 2;
	char new_command[size_at_command];
	char BLEreceiver[BYTES_NINA_TO_RECEIVER] = { 0 };
	memset(responce_nina, 0, BYTES_NINA_TO_RECEIVER);

	strcpy(new_command, at_command);
	strcat(new_command, "\r\n");
	//uint8_t* new_com = (uint8_t*) new_command;
	HAL_UART_Transmit_DMA(&huart4, (uint8_t*) &new_command, size_at_command);
	while (UartReady != SET) {
	}
	UartReady = RESET;
	HAL_Delay(msDelay);
	HAL_UART_Receive_DMA(&huart4, (uint8_t*) &BLEreceiver,
			BYTES_NINA_TO_RECEIVER);
	LED_ON
	HAL_Delay(10);
	LED_OFF
	huart4.pRxBuffPtr = (uint8_t*) &BLEreceiver;
	huart4.RxXferCount = 0;

	int size_response_uart = 0;

	for (int var = 0; var < BYTES_NINA_TO_RECEIVER; var++) {
		if (BLEreceiver[var] != 0 && BLEreceiver[var] < 128) {
			++size_response_uart;
		}
	}
	char sendResponse[size_response_uart];
	int counter_size = 0;

	for (int var = 0; var < BYTES_NINA_TO_RECEIVER; var++) {
		if (BLEreceiver[var] != 0 && BLEreceiver[var] < 128) {
			sendResponse[counter_size] = BLEreceiver[var];
			responce_nina[counter_size] = BLEreceiver[var];
			++counter_size;
			if (BLEreceiver[var - 1] == 79 && BLEreceiver[var] == 75) {
				return_flag = 1;
			}
		}
	}
	//HAL_UART_Transmit_IT(&hlpuart1, (uint8_t*) sendResponse,size_response_uart);
	fn_fprint(sendResponse);


	return return_flag;
}

int fn_set_perimetral_nina() {
	BLE_OFF
	LED_OFF
	HAL_Delay(1000);
	BLE_ON
	LED_ON
	HAL_Delay(1000);
	fn_at_command_nina("AT", 1000);
	//fn_at_command_nina("AT+UMRS=115200,2,8,1,1,1",1000);
	//fn_change_baundrate();
	fn_at_command_nina("AT", 1000);
	fn_at_command_nina("AT+UBTLE=2", 1000);
	HAL_Delay(500);
	fn_at_command_nina("AT+UDSC=0,6", 1000);
	HAL_Delay(500);
	fn_at_command_nina("AT&W", 1000);
	fn_at_command_nina("AT+CPWROFF", 1000);
	HAL_Delay(500);
	fn_at_command_nina("AT+UBTLN=\"WIZE TEST PERIMETRAL BLE\"", 1000);
	HAL_Delay(500);
	fn_at_command_nina("ATO1", 1000);
	//fn_recever_nina(50);
	while(1){
	fn_at_command_nina("SEND TO ME", 10000);
	fn_fprint("\n");
	}
	return 1;
}

int fn_recever_nina(unsigned int sec_timeout){
	volatile int NUM=0;
	char receiver_buff[100];
	uint8_t receiver_byte;
	sec_timeout*=1000;
	while(sec_timeout!=0){
		HAL_UART_Receive_DMA(&huart4,&receiver_byte,1);
		if(receiver_byte!=0)
		{
			receiver_buff[NUM++] = receiver_byte;
			LED_CHANGE
		}
		HAL_Delay(1);
		sec_timeout--;
		if(receiver_byte == 13)
		{
			break;
		}
	}
	if(NUM>0)
	{
		fn_fprint(receiver_buff);
		return 1;
	}
	else
		return 0;

}


