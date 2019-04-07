/*
 * includes.h
 *
 * Created: 3/22/2019 4:31:44 AM
 *  Author: MSA
 */ 


#ifndef INCLUDES_H_
#define INCLUDES_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

//General includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

//RTOS includes
#include "RTOS/FreeRTOS.h"
#include "RTOS/FreeRTOSConfig.h"
#include "RTOS/task.h"
#include "RTOS/semphr.h"

//self-made Drivers includes
#include "HAL/common.h"
#include "HAL/hal_standarized_data.h"
//uart
#include "HAL/UART/hal_USART.h"
#include "HAL/UART/hal_USART_CFG.h"
//spi
#include "HAL/SPI/hal_SPI.h"
#include "HAL/SPI/hal_SPI_CFG.h"
//
void system_init(void);
void sys_test(msa_u8 counter,msa_u8 direction);
void usart_listen(void);
void uart_check(void);

#endif /* INCLUDES_H_ */