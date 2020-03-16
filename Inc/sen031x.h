/*
 * sen031x.h
 *
 *  Created on: 16 de mar de 2020
 *      Author: oscar
 */

#ifndef SEN031X_H_
#define SEN031X_H_

#include "main.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

UART_HandleTypeDef huart2;


#define DIST_MIN			   30 //30m
#define Distance_Base         140 //140cm
#define radian_cos          0.866025


int fn_get_sen031x();
void insertionSort(float vetor[], int tamanhoVetor);

#endif /* SEN031X_H_ */
