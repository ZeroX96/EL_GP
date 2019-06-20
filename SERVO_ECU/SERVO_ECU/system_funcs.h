/*
 * system_funcs.h
 *
 * Created: 6/1/2019 12:14:18 AM
 *  Author: msams
 */ 


#ifndef SYSTEM_FUNCS_H_
#define SYSTEM_FUNCS_H_
#include "INCLUDES.h"

extern volatile st_pwm_object		 pwm_obj;					//used as a container of the pwm configurations
extern volatile str_spi_objectInfo_t spi_obj;					//used to hold the spi configurations
extern volatile usart_t				 uart_obj;					//used to hold the uart configurations
extern volatile msa_u8				 uart_data_got;			//used to listen to the tiva calls
extern volatile msa_u8				 spi_temp_out;
extern volatile msa_u8				 spi_temp_inn;
//
void system_init(void);
void sys_test(msa_u8 counter,msa_u8 direction);
void usart_listen(void);
void spi_listen(void);

void move_forward(unsigned char beriod);
void move_bckward(unsigned char beriod);
void move_right(unsigned char beriod);
void move_left(unsigned char beriod);
void move_stop(unsigned char beriod);
void hal_spiExchangeDATA_A(str_spi_objectInfo_t * strg_obj,msa_u8 *ByteOUT,msa_u8 *ByteIN);
void hal_spiExchangeDATA_B(str_spi_objectInfo_t * strg_obj,msa_u8 *ByteOUT,msa_u8 *ByteIN);


#endif /* SYSTEM_FUNCS_H_ */