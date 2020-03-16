/*
 * sigfox.c
 *
 *  Created on: 9 de mar de 2020
 *      Author: oscar
 */
#include <sigfox.h>



/*
 fn_init_sigfox
 funcao de configuracoes para a rede sigfox na regiao 2 e 4 alem da possibilidade de utilizar na dongle com downlink
 parta tal deve-se definir a DONGLE_KEY
 */
void fn_init_sigfox() {
	char ok[4];
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT$P=0\r\n", 8, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) ok, 4, 100);
	HAL_Delay(10);
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT$DR=905200000\r\n", 17, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) ok, 4, 100);
	HAL_Delay(10);
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT$IF=902200000\r\n", 17, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) ok, 4, 100);
	HAL_Delay(10);
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT$WR\r\n", 7, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) ok, 4, 100);
	HAL_Delay(10);
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT$RC\r\n", 7, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) ok, 4, 100);
	HAL_Delay(10);

#ifdef DONGLE_KEY
	//public key or private key
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)"ATS410=1\r\n",11);//ATS410=1 private key ; ATS410=0 public key
	//HAL_UART_Receive_IT(&huart1,(uint8_t*)ok,4,10);
	HAL_Delay(500);
#endif

}

//pegar id
void fn_get_id_sigfox() {

	char command[9] = "AT$I=10\r\n";
	HAL_UART_Transmit_IT(&huart1, (uint8_t*) command, 9);
	while (UartReady != SET) {
	}
	//Reset transmission flag
	UartReady = RESET;
	HAL_UART_Receive_IT(&huart1, (uint8_t*) st_sigfox_parameters.id, 10);
	while (UartReady != SET) {
		blink(2);
	}
	//Reset transmission flag
	UartReady = RESET;

}

//pegar pac
void fn_get_pac_sigfox() {

	char command[9] = "AT$I=11\r\n";
	HAL_UART_Transmit_IT(&huart1, (uint8_t*) command, 9);
	while (UartReady != SET) {
	}
	//Reset transmission flag
	UartReady = RESET;
	HAL_UART_Receive_IT(&huart1, (uint8_t*) st_sigfox_parameters.pac, 18);
	while (UartReady != SET) {
		blink(2);
	}
	//Reset transmission flag8
	UartReady = RESET;
}

//dumy command
void fn_at_sigfox() {

	char command[4] = "AT\r\n";
	//int at = 0;
	HAL_UART_Transmit(&huart1, (uint8_t*) command, 4, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) st_sigfox_parameters.at, 4, 100);

	/*		if (st_sigfox_parameters.at[0] == 79
	 && st_sigfox_parameters.at[1] == 85) {
	 at = 1;
	 }
	 return at;*/

}

//pegar a tensao no modulo sigfox
void fn_get_volt_sigfox() {

	char command[7] = "AT$V?\r\n";
	HAL_UART_Transmit_IT(&huart1, (uint8_t*) command, 7);
	HAL_UART_Receive_IT(&huart1, (uint8_t*) st_sigfox_parameters.volts, 6);
	while (UartReady != SET) {
		blink(2);
	}
	//Reset transmission flag
	UartReady = RESET;

	int_volt_sigfox = atoi(st_sigfox_parameters.volts);
	int_volt_sigfox/=1000;
}

//pegar a temperatura no mudulo sigfox
void fn_get_temperature_sigfox() {

	char command[8] = "AT$T?\r\n";
	HAL_UART_Transmit_IT(&huart1, (uint8_t*) command, 8);
	HAL_UART_Receive_IT(&huart1, (uint8_t*) st_sigfox_parameters.temperature,
			7);
	while (UartReady != SET) {
		blink(2);
	}
	//Reset transmission flag
	UartReady = RESET;

	int_temp_sigfox = atoi(st_sigfox_parameters.temperature);

}

// daqui para baixo estao as funcoes de envio e recepcao de frames pela rede
void fn_send_frame_test_sigfox(char* frame) {
	char ok[4] = { };
	int tam = (strlen(frame) + 8);
	char complete_frame[tam];
	char init_frame[6] = "AT$SF=";
	strcpy(complete_frame, init_frame);
	strcat(complete_frame, frame);
	strcat(complete_frame, "\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*) complete_frame, tam, 200);
	HAL_UART_Receive(&huart1, (uint8_t*) ok, 4, 100);

	strcpy(st_sigfox_frame.test, frame);
}

void fn_send_start_frame_sigfox() {
	SIGFOX_ON
	fn_status_sigfox();
	HAL_Delay(100);
	fn_init_sigfox();
	fn_get_temperature_sigfox();
	fn_get_volt_sigfox();

	char start_machine_frame[15] = { 0 };
	char ok[4] = { 0 };
	char buffer_start[7] = { 0 };
	int temp_buff = (int_temp_sigfox/10);
	int volt_buff = (int_volt_sigfox/100);

	start_machine_frame[0] = 65;
	start_machine_frame[1] = 84;
	start_machine_frame[2] = 36;
	start_machine_frame[3] = 83;
	start_machine_frame[4] = 70;
	start_machine_frame[5] = 61;
	start_machine_frame[6] = 48;
	start_machine_frame[7] = 50;

	decHex(volt_buff, buffer_start);
	check_size_info(2, buffer_start);
	strcat(start_machine_frame, buffer_start);


	decHex(temp_buff, buffer_start);
	check_size_info(2, buffer_start);
	strcat(start_machine_frame, buffer_start);


	start_machine_frame[12] = 13;
	start_machine_frame[13] = 10;
	start_machine_frame[14] = 0;
	HAL_UART_Transmit(&huart1, (uint8_t*) start_machine_frame, 15, 200);
	HAL_Delay(500);
	HAL_UART_Receive(&huart1, (uint8_t*) ok, 4, 200);

	HAL_Delay(1000);
	SIGFOX_OFF
	fn_status_sigfox();
}

void fn_info_sigfox() {
	SIGFOX_ON
	SIGFOX_RESET_ON
	HAL_Delay(10);
	SIGFOX_RESET_OFF
	HAL_Delay(1000);
	fn_at_sigfox();
	HAL_Delay(100);
	fn_init_sigfox();
	HAL_Delay(100);
	fn_get_id_sigfox();
	fn_fprint("SIGFOX ID: ");
	fn_fprint(st_sigfox_parameters.id);
	fn_fprint("\r\n");
	HAL_Delay(100);
	fn_get_pac_sigfox();
	fn_fprint("SIGFOX PAC: ");
	fn_fprint(st_sigfox_parameters.pac);
	fn_fprint("\r\n");
	HAL_Delay(100);
	fn_get_temperature_sigfox();
	fn_fprint("SIGFOX TEMPERATURE: ");
	fn_fprint(st_sigfox_parameters.temperature);
	fn_fprint("\r\n");
	SIGFOX_RESET_ON
	HAL_Delay(10);
	SIGFOX_RESET_OFF
	HAL_Delay(100);
	fn_get_volt_sigfox();
	fn_fprint("SIGFOX VOLTS: ");
	fn_fprint(st_sigfox_parameters.volts);
	fn_fprint("\r\n");
	HAL_Delay(100);
	SIGFOX_OFF
}


void fn_status_sigfox()
{
	if (HAL_GPIO_ReadPin(WISOL_LED_CPU_GPIO_Port,WISOL_LED_CPU_Pin)) {
		LED_ON
	}
	else
		LED_OFF
}
