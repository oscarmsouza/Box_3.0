/*
 * encoder.h
 *
 *  Created on: 9 de mar de 2020
 *      Author: oscar
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "main.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sigfox.h"
#include "gprs.h"

int OnehextoOneDec(char hex[]);
int hexDec(char *hex);
void decHex(int number, char buff[7]);
void decToBinary(int number, char binary[32]);
int num_hex_digits(unsigned n);
void hexBin(char *hex, char *dec) ;
int binaryToDec(int num);
int bin_to_dec(char *bin);
void RemoveSpaces(char source[]);
void check_size_info(int size, char*buff);


#endif /* ENCODER_H_ */
