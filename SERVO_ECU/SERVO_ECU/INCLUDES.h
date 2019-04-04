/*
 * INCLUDES.h
 *
 * Created: 30/11/2018 04:41:53
 *  Author: Mahmoud
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
//uart
#include "hal/UART/hal_USART.h"
#include "hal/UART/hal_USART_CFG.h"
#include "HAL/hal_standarized_data.h"
//pwm
#include "hal/PWM/hal_PWM.h"
#include "hal/PWM/hal_PWM_CFG.h"
//spi
#include "HAL/SPI/hal_SPI.h"
#include "HAL/SPI/hal_SPI_CFG.h"




#endif /* INCLUDES_H_ */