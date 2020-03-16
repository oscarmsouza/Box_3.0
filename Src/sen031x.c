/*
 * sen031x.c
 *
 *  Created on: 16 de mar de 2020
 *      Author: oscar
 */

#include "sen031x.h"
#include "main.h"



int fn_get_sen031x() {
	US_ON
	HAL_Delay(1000);
	float array_us[100], us_buffer = 0;
	int distance = 0;
	uint8_t Rx_data[5] = { };
	uint8_t header, data_h, data_l, sum, soma;

	for (int i = 0; i < 100; i++) {
		HAL_UART_Receive_IT(&huart2,Rx_data, 5);
		HAL_Delay(50);
		for (int var = 0; var < 5; var++) {
			if (Rx_data[var] == 0xff) {
				header = Rx_data[var];
				data_h = Rx_data[var + 1];
				data_l = Rx_data[var + 2];
				sum = Rx_data[var + 3];
				soma = (header + data_h + data_l) & 0xFF;
				if (soma == sum) {
					distance = (data_h << 8) + data_l;
				}
			}
		}
		array_us[i] = distance / 10;
	}

	insertionSort(array_us, 100);
	for (int i = 10; i < 90; i++) {
		us_buffer += array_us[i];
	}
	distance = us_buffer / 80;
	US_OFF
	return (distance);

}

void insertionSort(float vetor[], int tamanhoVetor) {
	int escolhido, j;

	for (int i = 1; i < tamanhoVetor; i++) {
		escolhido = vetor[i];
		j = i - 1;

		while ((j >= 0) && (vetor[j] > escolhido)) {
			vetor[j + 1] = vetor[j];
			j--;
		}

		vetor[j + 1] = escolhido;
	}
}


/*static void MX_USART2_UART_Init(void) {

	 USER CODE BEGIN USART2_Init 0

	 USER CODE END USART2_Init 0

	 USER CODE BEGIN USART2_Init 1

	 USER CODE END USART2_Init 1
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT
			| UART_ADVFEATURE_DMADISABLEONERROR_INIT;
	huart2.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
	huart2.AdvancedInit.DMADisableonRxError =
			UART_ADVFEATURE_DMA_DISABLEONRXERROR;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	 USER CODE BEGIN USART2_Init 2

	 USER CODE END USART2_Init 2

}*/
