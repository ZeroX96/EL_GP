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
//interrupts
#include "HAL/INTERRUPTS/external_interrupts.h"


//defines
//pwm_defines
#define SERVO_CTRL_FREQ 50 //20mHZ according to the specs of the servo type we have
#define SERVO_DELAY_VAL 300
#define PWM_PIN 3
#define LED_PIN 0
#define BUZ_PIN 1
#define RED_LED_ON() (PORTA|=(1<<LED_PIN))
#define RED_LED_OF() (PORTA&=~(1<<LED_PIN))
#define BUZ_ON() (PORTA|=(1<<BUZ_PIN))
#define BUZ_OF() (PORTA&=~(1<<BUZ_PIN))


#endif /* INCLUDES_H_ */