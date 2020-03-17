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
	HAL_UART_Transmit_IT(&huart1, (uint8_t*) "ATS410=1\r\n", 11); //ATS410=1 private key ; ATS410=0 public key
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
	int_volt_sigfox /= 1000;
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
	int_temp_sigfox /= 10;
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

void fn_status_sigfox() {
	if (HAL_GPIO_ReadPin(WISOL_LED_CPU_GPIO_Port, WISOL_LED_CPU_Pin)) {
		LED_ON
	} else
		LED_OFF
}

void fn_reset_sigfox() {
	SIGFOX_RESET_ON
	HAL_Delay(50);
	SIGFOX_RESET_OFF
	//HAL_GPIO_DeInit(EN_SFOX_GPIO_Port, EN_SFOX_Pin);
	fn_fprint("\r\nsigfox reset\r\n");
}

//#################### PAYLOAD FUNCTIONS #####################################
// daqui para baixo estao as funcoes de envio e recepcao de frames pela rede
void fn_send_report_frame_sigfox() {
	SIGFOX_ON
	memset(st_sigfox_frame.frame_report_values, 0, 22);
	fn_encoder_report_frame(st_sigfox_frame.frame_report_values);
	fn_status_sigfox();
	HAL_Delay(500);
	fn_reset_sigfox();
	fn_init_sigfox();
	//fn_init_sigfox();
	char ok[4] = { 0 };
	//int tam = (strlen(frame) + 8);
	uint8_t tam = 32;
	char complete_frame[tam];
	//char init_frame[6] = {0};
	complete_frame[0] = 65;
	complete_frame[1] = 84;
	complete_frame[2] = 36;
	complete_frame[3] = 83;
	complete_frame[4] = 70;
	complete_frame[5] = 61;

	strcat(complete_frame, st_sigfox_frame.frame_report_values);
	strcat(complete_frame, "\r\n");
	HAL_UART_Transmit_IT(&huart1, (uint8_t*) complete_frame, tam);
	while (UartReady != SET) {
	}
	//Reset transmission flag
	UartReady = RESET;
	HAL_UART_Receive_IT(&huart1, (uint8_t*) ok, 4);
	HAL_Delay(2000);
	fn_status_sigfox();
	fn_fprint("reportframe:  ");
	fn_fprint(complete_frame);
	SIGFOX_OFF
	fn_status_sigfox();
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
	int temp_buff = (int_temp_sigfox);
	int volt_buff = (int_volt_sigfox);

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
	fn_fprint("frame start:  ");
	fn_fprint(start_machine_frame);
	fn_fprint("\r\n");
}

void fn_send_daily_frame_sigfox() {
	SIGFOX_ON
	fn_fprint("SIGFOX DAILY FRAME\r\n");
	memset(st_sigfox_frame.frame_report_values, 0, 22);
	fn_encoder_report_frame(st_sigfox_frame.frame_report_values);
	fn_status_sigfox();
	HAL_Delay(500);
	fn_reset_sigfox();
	fn_init_sigfox();

	uint8_t d_time = 0, tam = 33;
	int timebyte_int, undTimeByte_int, time_byte_value = 0;

	char complete_payload[tam];
	char config[32] = { 0 };
	char buff_downlink[16] = { 0 };
	char buff_dec[64] = { 0 };
	char undTimeByte[2] = { 0 };
	char volume_ref[3] = { 0 };
	char time_stamp[7] = { 0 };
	char timebyte[6] = { 0 };

	complete_payload[0] = 65;
	complete_payload[1] = 84;
	complete_payload[2] = 36;
	complete_payload[3] = 83;
	complete_payload[4] = 70;
	complete_payload[5] = 61;
	strcat(complete_payload, st_sigfox_frame.frame_report_values);
	complete_payload[28] = 44;
	complete_payload[29] = 49;
	complete_payload[30] = 13;
	complete_payload[31] = 10;
	complete_payload[32] = 0;
	for (int var = 0; var < 3; ++var) {

		HAL_UART_Transmit_IT(&huart1, (uint8_t*) complete_payload, tam);
		d_time = 0;
		while (UartReady != SET && d_time != 60) {
			HAL_Delay(1000);
			d_time++;
		}
		//Reset transmission flag
		UartReady = RESET;
		HAL_UART_Receive_IT(&huart1, (uint8_t*) config, 32);
		d_time = 0;
		while (UartReady != SET && d_time != 60) {
			HAL_Delay(1000);
			d_time++;
		}
		/* Reset transmission flag */
		UartReady = RESET;
		find_between("RX=", "\r", config, buff_downlink);
		if (strlen(buff_downlink) >= 15) {
			var = 3;
			fn_fprint("SIGFOX DOWNLINK VALUES:");
			fn_fprint(buff_downlink);
			RemoveSpaces(buff_downlink);
			hexBin(buff_downlink, buff_dec);

			undTimeByte[0] = buff_dec[32]; //0
			undTimeByte[1] = buff_dec[33]; //1
			time_stamp[0] = buff_downlink[6];
			time_stamp[1] = buff_downlink[7];
			time_stamp[2] = buff_downlink[4];
			time_stamp[3] = buff_downlink[5];
			time_stamp[4] = buff_downlink[2];
			time_stamp[5] = buff_downlink[3];

			fn_fprint("SIGFOX DOWNLINK BINARY:");
			fn_fprint(buff_dec);

			undTimeByte[0] = buff_dec[32]; //0
			undTimeByte[1] = buff_dec[33]; //1

			volume_ref[0] = buff_downlink[10];
			volume_ref[1] = buff_downlink[11];

			timebyte[0] = buff_dec[34]; //0
			timebyte[1] = buff_dec[35]; //1
			timebyte[2] = buff_dec[36]; //1
			timebyte[3] = buff_dec[37]; //1
			timebyte[4] = buff_dec[38]; //1
			timebyte[5] = buff_dec[39]; //0

			timebyte_int = atoi(timebyte);
			undTimeByte_int = atoi(undTimeByte);

			time_byte_value = binaryToDec(timebyte_int); //transmission period in hours
			st_data_sensor_e.referenceVol = hexDec(volume_ref);

			time_byte_value = binaryToDec(timebyte_int); //transmission period in hours

			st_timers.TimeStamp = hexDec(time_stamp); //timestamp minutes-sigmais protocol

			if (undTimeByte_int == 00 && time_byte_value != 0) //if 00 = time unid its seconds
					{
				st_timers.seconds_to_send = time_byte_value;
			}
			if (undTimeByte_int == 01 && time_byte_value != 0) // if 01 = time unid its minutes
					{
				st_timers.seconds_to_send = (time_byte_value * 60);
			}
			if (undTimeByte_int == 10 && time_byte_value != 0) // if 10 = time unid its hours
					{
				st_timers.seconds_to_send = (time_byte_value * 3600);
			}
			if (undTimeByte_int == 11 && time_byte_value != 0) // if 11 = time unid its days
					{
				st_timers.seconds_to_send = (time_byte_value * 86400);
			}

			st_timers.seconds_today = fn_get_seconsForTimeStemp(
					st_timers.TimeStamp); //seconds elapsed in the day
		}
	}
	fn_status_sigfox();

	SIGFOX_OFF
	fn_status_sigfox();
}
