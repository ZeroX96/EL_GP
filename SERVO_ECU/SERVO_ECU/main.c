/*
 * SERVO_ECU.c
 *
 * Created: 3/25/2019 12:17:44 PM
 * Author : MSA
 * Main test_1,without RTOS
 */ 
#include "INCLUDES.h"

//defines
//pwm_defines
#define SERVO_CTRL_FREQ 50 //20mHZ
#define SERVO_DELAY_VAL 1000

//
void system_init(void);
void usart_read(void);

//global variables
volatile msa_u8			SHOWA [16];		// displaying digital output as it's sent as ascii
volatile msa_u8			uart_data_got;	//used to listen to the tiva calls 
volatile msa_u8			servo_direction[3]={3,6,8};
st_pwm_object			pwm_obj;		//used as a container of the pwm configurations
str_spi_objectInfo_t	spi_obj;
usart_t					uart_obj;

volatile msa_u8 spi_temp_out=0;
volatile msa_u8 spi_temp_inn=0;
volatile msa_u8 uart_temp=0;

int main(void)
{
	system_init();
	
	while (1)
	{
		// 0:1:2 Servo direction
		for (msa_u8 iteration_counter=0; iteration_counter < 2; iteration_counter++)
		{
			//check if uart_stop
			//pwm_0
			pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,servo_direction[iteration_counter]);
			//check if uart_stop
			//spi_scan ya atmega
			spi_temp_out = SCAN_YA_MEGA;
			hal_spiExchangeDATA(&spi_obj,&spi_temp_out,&spi_temp_inn);
			//check if uart_stop
			//wait el confirmation counter to be two
			_delay_ms(300);
			
		}
		//2:1:0 servo direction
		for (msa_u8 iteration_counter=2; iteration_counter > 0; iteration_counter++)
		{
			//check if uart_stop
			//pwm_0
			
			//check if uart_stop
			//spi_scan ya atmega
			
			//check if uart_stop
			//wait el confirmation counter to be two
		}
		
	}
	return 0;
}


void system_init(void)
{
	//pwm init
	pwm_init(&pwm_obj,TIMER_0,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,1);
	//uart init
	usart_init(&uart_obj,B_SENDER_N_RECEIVER,ONE_STP_BIT,NO_PARITY,EIGHT,INTERRUPT_DRIVEN,FALLING_EDGE);
	usart_set_isr_RXC_callback(&uart_obj,usart_read);
	//spi init...try polling i.e wait 10 m s or the time the longest scanning task will take plus some time then ask for the status if reading is done or not
				//try to make the delay decreases by time :D 
	hal_spiInit(&spi_obj,SPI_1_base,FREQ_BY_4,MASTER_EN,SPI_POLLING,MODE_1,MSB_FIRST);
	
}


//these will occure only if there is an emergency call from the tiva controller
void usart_read(void)
{
	uart_data_got=UDR;
}

ISR(USART_RXC_vect)
{
	usart_read();
}
