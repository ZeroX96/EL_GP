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
#define SERVO_CTRL_FREQ 50 //20mHZ according to the specs of the servo type we have
#define SERVO_DELAY_VAL 1000
#define LED_PIN 0
#define BUZ_PIN 1
#define RED_LED_ON() (PORTA|=(1<<LED_PIN))
#define RED_LED_OF() (PORTA&=~(1<<LED_PIN))
#define BUZ_ON() (PORTA|=(1<<BUZ_PIN))
#define BUZ_OF() (PORTA&=~(1<<BUZ_PIN))
//
void system_init(void);
void sys_test(msa_u8 counter,msa_u8 direction);
void usart_listen(void);
void uart_check(void);

//global variables
volatile msa_u8			SHOWA [16];					// displaying digital output as it's sent as ascii
volatile msa_u8			uart_data_got=0;			//used to listen to the tiva calls 
volatile msa_u8			servo_direction[3]={3,6,8};	//
volatile st_pwm_object			pwm_obj;					//used as a container of the pwm configurations
volatile str_spi_objectInfo_t	spi_obj;					//used to hold the spi configurations
volatile usart_t				uart_obj;					//used to hold the uart configurations

volatile msa_u8 spi_temp_out=0;
volatile msa_u8 spi_temp_inn=0;
volatile msa_u8 uart_temp=0;

int main(void)
{
	system_init();
	
	while (1)
	{
		// 0:1 Servo direction
		for (msa_u8 iteration_counter=0; iteration_counter < 2; iteration_counter++)
		{
			//check if uart_stop
			uart_check();
			//pwm
			pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,servo_direction[iteration_counter]);
			//check if uart_stop
			uart_check();
			//spi_scan ya atmega
			spi_temp_out = SCAN_YA_MEGA;
			hal_spiExchangeDATA(&spi_obj,&spi_temp_out,&spi_temp_inn);
			//check if uart_stop
			uart_check();
			//system test
			sys_test(iteration_counter,servo_direction[iteration_counter]); 
			//wait el confirmation counter to be two 
			_delay_ms(SERVO_DELAY_VAL);//use the rtos delay instead or wait the confirm cntr to be 2
			
		}
		//2:1 servo direction
		for (msa_u8 iteration_counter=2; iteration_counter > 0; iteration_counter--)
		{
			//check if uart_stop
			uart_check();
			//pwm
			pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,servo_direction[iteration_counter]);
			//check if uart_stop
			uart_check();
			//spi_scan ya atmega
			spi_temp_out = SCAN_YA_MEGA;
			hal_spiExchangeDATA(&spi_obj,&spi_temp_out,&spi_temp_inn);
			//check if uart_stop
			uart_check();
			//system test
			sys_test(iteration_counter,servo_direction[iteration_counter]);
			//wait el confirmation counter to be two
			_delay_ms(SERVO_DELAY_VAL);//use the rtos delay instead or wait the confirm cntr to be 2
			
		}
		
	}
	//if any error happened and missed the previous loop this will cover that error and try to catch 
	//and i'll know by the change in the system behavior 
	while(1)
	{
		//system fail alarm
		//BUZ on
		BUZ_ON();
		//delay 250
		_delay_ms(500);
		//BUZ off
		BUZ_OF();
		//delay 250
		_delay_ms(500);
	}
	return 0;
}


void system_init(void)
{
	DDRA=DDRC=0XFF;
	//pwm init
	pwm_init(&pwm_obj,TIMER_0,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,1);
	//uart init
	usart_init(&uart_obj,B_SENDER_N_RECEIVER,ONE_STP_BIT,NO_PARITY,EIGHT,INTERRUPT_DRIVEN,FALLING_EDGE);
	//usart_set_isr_RXC_callback(&uart_obj,usart_listen);
	//spi init...try polling i.e wait 10 m s or the time the longest scanning task will take plus some 
	//time then ask for the status if reading is done or not
				//try to make the delay decreases by time :D 
	hal_spiInit(&spi_obj,SPI_1_base,FREQ_BY_4,MASTER_EN,SPI_POLLING,MODE_1,MSB_FIRST);
}

void uart_check(void)	//will be a task with a semaphore depends on the isr
{
	PORTC++;
	if(uart_data_got == STOP_SERVO)
	{
		while (uart_data_got != RESUME_SERVO)	//will be changed by the isr
		{
			//red led on
			RED_LED_ON();
			//delay 250
			_delay_ms(250);
			//red led off
			RED_LED_OF();
			//delay 250
			_delay_ms(250);
		}
	
	}
}

void sys_test(msa_u8 counter,msa_u8 direction)
{
	msa_u8 *arr_add1=(msa_u8 *)"i = ";
	msa_u8 *arr_add2=(msa_u8 *)"  gives an angle of ";
	msa_u8 data_byte='\n';
	//testing
	usart_send_arr(&uart_obj,arr_add1);
	itoa(counter,SHOWA,10);
	usart_send_arr(&uart_obj,SHOWA);
	usart_send_arr(&uart_obj,arr_add2);
	itoa(direction,SHOWA,10);
	usart_send_arr(&uart_obj,SHOWA);
	usart_send_byte(&uart_obj,&data_byte);
	//testing_end
}

//these will occur only if there is an emergency call from the tiva controller
void usart_listen(void)
{
	PORTA^=0XFF;
	uart_data_got=UDR;
}
/* fck u ,u already set this using the uart_set_isr :[ 
*/
ISR(USART_RXC_vect)
{
	PORTC^=0XFF;
	usart_listen();
}