/*
 * USONICs.h
 *
 * Created: 30/11/2018 04:38:54
 *  Author: Mahmoud
 */ 


#ifndef USONICS_H_
#define USONICS_H_
#ifndef F_CPU
#define  F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "../common.h"
#include "HAL/UART/hal_USART.h"


#define OVF_VAL 1500 //the val. of every overflow occurrence

//static uint8_t overFlow_cntr=0;//enable the ov isr and just inc this global every ov isr and reset it whenever the counter val is read
msa_u32 read_ultra_sonic0(void);

void send_usonic0(msa_u32 COUNTA);

msa_u32 read_ultra_sonic1(void);

void send_usonic1(msa_u32 COUNTB);





#endif /* USONICS_H_ */