/*
 * includes.h
 *
 * Created: 3/22/2019 4:31:44 AM
 *  Author: MSA
 */ 


#ifndef INCLUDES_H_
#define INCLUDES_H_
//CPU-SPEED
#define F_CPU 8000000UL
//GENREAL INCLUDES
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//RTOS
#include "RTOS/FREERTOS.h"
#include "RTOS/task.h"
#include "RTOS/semphr.h"
//EXTERNAL-INTERRUPTS
#include "HAL/EXTERNAL_INTERRUPTS/external_interrupts.h"
//UART
#include "HAL/uart"


#endif /* INCLUDES_H_ */