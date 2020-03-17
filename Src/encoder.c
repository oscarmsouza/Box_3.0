/*
 * encoder.c
 *
 *  Created on: 9 de mar de 2020
 *      Author: oscar
 */

#include "encoder.h"

//########################## ENCODER  PAYLOAD ###############################

void fn_encoder_report_frame(char * frame){

		//char report_frame_complete[31] = { 0 };
		char buffer_frame[7] = { 0 };
		char header_char[2] = "2";
		//itoa(header, header_char, 10);
		fn_fprint("SEND REPORT FRAME:  ");

		/*	report_frame_complete[6] = 48;
		 report_frame_complete[7] = 50;*/

		check_size_info(2, header_char);
		strcat(frame, header_char);

		decHex(st_data_sensor_e.battery, buffer_frame);
		check_size_info(2, buffer_frame);
		strcat(frame, buffer_frame);

		decHex(st_data_sensor_e.temperature, buffer_frame);
		check_size_info(2, buffer_frame);
		strcat(frame, buffer_frame);

		decHex(st_data_sensor_e.latitude, buffer_frame);
		check_size_info(6, buffer_frame);
		strcat(frame, buffer_frame);

		decHex(st_data_sensor_e.longitude, buffer_frame);
		check_size_info(6, buffer_frame);
		strcat(frame, buffer_frame);

		strcat(frame, "0");

		decHex(st_data_sensor_e.volume, buffer_frame);
		strcat(frame, buffer_frame);

		decHex(st_data_sensor_e.angle, buffer_frame);
		strcat(frame, buffer_frame);

		strcat(frame, "0");
}

//########################## ENCODER HEXA/DEC/BIN ###############################
int OnehextoOneDec(char hex[]) {
	int i = 0;
	int decimal = 0;
	/* Find the decimal representation of hex[i] */
	if (hex[i] >= '0' && hex[i] <= '9') {
		decimal = hex[i] - 48;
	} else if (hex[i] >= 'a' && hex[i] <= 'f') {
		decimal = hex[i] - 97 + 10;
	} else if (hex[i] >= 'A' && hex[i] <= 'F') {
		decimal = hex[i] - 65 + 10;
	}

	return decimal;
}

int hexDec(char *hex) {
	int i = 0;
	int val = 0;
	int len;

	int decimal = 0;

	/* Find the length of total number of hex digit */
	len = strlen(hex);
	len--;

	/*
	 * Iterate over each hex digit
	 */
	for (i = 0; i < strlen(hex); i++) {

		/* Find the decimal representation of hex[i] */
		if (hex[i] >= '0' && hex[i] <= '9') {
			val = hex[i] - 48;
		} else if (hex[i] >= 'a' && hex[i] <= 'f') {
			val = hex[i] - 97 + 10;
		} else if (hex[i] >= 'A' && hex[i] <= 'F') {
			val = hex[i] - 65 + 10;
		}

		decimal += val * pow(16, len);
		len--;
	}
	return decimal;
}

void decHex(uint32_t number, char buff[7]) {

	char hex[7]; /*bcoz it contains characters A to F*/
	memset(buff, 0x00, 7);//sizeof(buff));
	memset(hex, 0x00, 7);//sizeof(buff));
	int cnt, i;
	cnt = 0; /*initialize index to zero*/
	if (number == 0) {
		strcpy(buff, "0");
	}
	while (number > 0) {
		switch (number % 16) {
		case 10:
			hex[cnt] = 'A';
			break;
		case 11:
			hex[cnt] = 'B';
			break;
		case 12:
			hex[cnt] = 'C';
			break;
		case 13:
			hex[cnt] = 'D';
			break;
		case 14:
			hex[cnt] = 'E';
			break;
		case 15:
			hex[cnt] = 'F';
			break;
		default:
			hex[cnt] = (number % 16) + 0x30; /*converted into char value*/
		}
		number = number / 16;
		cnt++;
	}
	for (i = (cnt - 1); i >= 0; i--) {
		int j = cnt - 1 - i;
		buff[j] = hex[i];
	}
}

void decToBinary(int number, char binary[32]) {
	int cnt, i;
	int bin[32];
	cnt = 0; /*initialize index to zero*/
	while (number > 0) {
		bin[cnt] = number % 2;
		number = number / 2;
		cnt++;
	}
	for (i = (cnt - 1); i >= 0; i--)
		binary[i] = bin[i];
}

int num_hex_digits(unsigned n) {
	if (!n)
		return 1;

	int ret = 0;
	for (; n; n >>= 4) {
		++ret;
	}
	return ret;
}

void hexBin(char *hex, char *dec) {

	int i = 0;
	memset(dec, '\0', strlen(dec));

	/* Extract first digit and find binary of each hex digit */
	for (i = 0; i < strlen(hex); i++) {
		switch (hex[i]) {
		case '0':
			strcat(dec, "0000");
			break;
		case '1':
			strcat(dec, "0001");
			break;
		case '2':
			strcat(dec, "0010");
			break;
		case '3':
			strcat(dec, "0011");
			break;
		case '4':
			strcat(dec, "0100");
			break;
		case '5':
			strcat(dec, "0101");
			break;
		case '6':
			strcat(dec, "0110");
			break;
		case '7':
			strcat(dec, "0111");
			break;
		case '8':
			strcat(dec, "1000");
			break;
		case '9':
			strcat(dec, "1001");
			break;
		case 'a':
		case 'A':
			strcat(dec, "1010");
			break;
		case 'b':
		case 'B':
			strcat(dec, "1011");
			break;
		case 'c':
		case 'C':
			strcat(dec, "1100");
			break;
		case 'd':
		case 'D':
			strcat(dec, "1101");
			break;
		case 'e':
		case 'E':
			strcat(dec, "1110");
			break;
		case 'f':
		case 'F':
			strcat(dec, "1111");
			break;
		default:
			break;
		}
	}
}

int binaryToDec(int num) {
	int decimal_val = 0, base = 1, rem = 0;

	//printf("Enter a binary number(1s and 0s) \n");
	//scanf("%d", &num); /* maximum five digits */
	//int binary_val = num;
	while (num > 0) {
		rem = num % 10;
		decimal_val = decimal_val + rem * base;
		num = num / 10;
		base = base * 2;
	}
	return decimal_val;
}

int bin_to_dec(char *bin) {

	int i, tam, novoValor = 0;
	tam = strlen(bin); //verifica quantos dígitos tem no número

	//pega os dígitos da direita para a esquerda
	for (i = tam - 1; i >= 0; i--) {
		//printf("%c|", numero[i]);
		if (bin[i] == '1') {
			novoValor += pow(2, tam - 1 - i);
		}
	}

	return novoValor;
}
//########################## ENCODER AUXILIAR PAYLOAD ###############################
void RemoveSpaces(char source[]) {
	//int tam = strlen(source);
	char* i = source;
	char* j = source;

	while (*j != 0) {
		*i = *j++;
		if (*i != ' ')
			i++;
	}
	*i = 0;

}

void check_size_info(int size, char*buff) {
	if(size == 2){
		char dado[4] = "";
		switch (strlen(buff)) {
		case (1):
			dado[0] = 48;
			//dado[1] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (2):
/*			dado[0] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);*/
			break;
/*		case (3):
			break;*/
		default:
			buff[0] = 48;
			buff[1] = 48;
			break;
		}
	}
		else if (size==4){
		char dado[5] = "";
		switch (strlen(buff)) {
		case (1):
			dado[0] = 48;
			dado[1] = 48;
			dado[2] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (2):
			dado[0] = 48;
			dado[1] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (3):
			dado[0] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (4):
			break;
		default:
			buff[0] = 48;
			buff[1] = 48;
			buff[2] = 48;
			buff[3] = 48;
			buff[4] = 0;
			break;
		}
		}
		else if (size==6){
		char dado[7] = "";
		switch (strlen(buff)) {
		case (1):
			dado[0] = 48;
			dado[1] = 48;
			dado[2] = 48;
			dado[3] = 48;
			dado[4] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (2):
			dado[0] = 48;
			dado[1] = 48;
			dado[2] = 48;
			dado[3] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (3):
			dado[0] = 48;
			dado[1] = 48;
			dado[2] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (4):
			dado[0] = 48;
			dado[1] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (5):
			dado[0] = 48;
			strcat(dado, buff);
			strcpy(buff, dado);
			break;
		case (6):
			break;
		default:
			buff[0] = 48;
			buff[1] = 48;
			buff[2] = 48;
			buff[3] = 48;
			buff[4] = 48;
			buff[5] = 48;
			buff[6] = 0;
			break;
		}

		}
}

int fn_get_seconsForTimeStemp(int TS_Total) {
	//TS_Total = 355195;
	int TS_hour, TS_day, TS_minute, TS_secons;
	float TS_hour_aux, TS_day_aux, TS_minute_aux;

	TS_day_aux = TS_Total / 1440.000;
	TS_day = TS_day_aux;

	TS_hour_aux = (TS_day_aux - TS_day) * 24.000;
	TS_hour = TS_hour_aux;

	TS_minute_aux = (TS_hour_aux - TS_hour) * 60.00;
	TS_minute = round(TS_minute_aux);

	TS_secons = 60 * (TS_minute + (TS_hour * 60));

	return TS_secons;
}
//########################## ENCODER AUXILIAR GPS ###############################


void find_between(const char *first, const char *last, char *buff,
		char *buff_return) {
	//const char *last = "*";
	//const char *buff = _gps;
	char *target = NULL;
	char *start, *end;
	start = strstr(buff, first);
	end = strstr(start, last);

	if (start) {
		start += strlen(first);
		if (end) {
			target = (char *) malloc(end - start + 1);
			memcpy(target, start, end - start);
			target[end - start] = '\0';
		}
	}
	strcpy(buff_return, target);
	free(target);
}


