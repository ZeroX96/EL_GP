/*
 * SCANNING_ECUS.c
 *
 * Created: 3/22/2019 4:27:30 AM
 * Author : MSA
 */ 

 //revise the OVF_VAL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "includes.h"

//global variables
volatile msa_u8			uart_data_got=0;			//used to listen to the tiva calls

volatile str_spi_objectInfo_t	spi_obj;					//used to hold the spi configurations
volatile usart_t				uart_obj;					//used to hold the uart configurations

volatile static msa_u32 usonic0=0;
volatile static msa_u32 usonic1=0;
volatile msa_u8 spi_temp_out=0;
volatile msa_u8 spi_temp_inn=0;
volatile msa_u8 uart_temp='\n';
//volatile msa_u8 scaneduler=E_TRUE;			//used to synchronize the scanning with the servo spi calls




int main(void)
{
	system_init();
    while (1) 
    {
		usonic0=read_ultra_sonic0();
		usonic1=read_ultra_sonic1();
		//scaneduler=E_FALSE;
		//test ignoring the values lower than 380 and higher than 1000 4ex so I'm more precise and in safe region
		send_usonic0(usonic0);
		send_usonic1(usonic1);
		if (( (usonic0 <= 750U) && (usonic0 >= 1U) ) || ( (usonic1 <= 750U) && (usonic1 >=1U) ) )
		{
			if (( (usonic0 <= 750U) && (usonic0 >= 1U) ))
			{
				spi_temp_out=OBSTACLE_A1;
			} 
			else //usonic1
			{
				spi_temp_out=OBSTACLE_A2;
			}
			hal_spiExchangeDATA_edited(&spi_obj,&spi_temp_out,&spi_temp_inn);
		}
 		_delay_ms(2);
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
	DDRC=DDRA=0xff;
	SET_BIT(PORTA,0);
	//spi init...try polling i.e wait 10 m s or the time the longest scanning task will take plus some
	//time then ask for the status if reading is done or not
	//try to make the delay decreases by time :D
	hal_spiInit(&spi_obj,SPI_1_base,FREQ_BY_4,SLAVE_EN,SPI_INTERRUPTING,MODE_1,MSB_FIRST);
	hal_setSpiIsrCallback(&spi_obj,spi_listen);
	//uart init //but will disable the completion isr
	usart_init(&uart_obj,B_SENDER_N_RECEIVER,ONE_STP_BIT,NO_PARITY,EIGHT,POLLING_DRIVEN,FALLING_EDGE);	//notice that in this specific project
																											//according to sys demands, i ignored
																											//prevented the uart_send_complete isr 
	usart_set_isr_RXC_callback(&uart_obj,usart_listen);
	//usonics_init
	//output the control/triggering pins
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	//ultrasonic
	//setting the interrupt pins as inputs
	CLEAR_BIT(DDRD,2);
	CLEAR_BIT(DDRD,3);
 	//enabling interrupt0 & interrupt1
	SET_BIT(GICR,INT0);
	SET_BIT(GICR,INT1);
	//setting interrupt triggering at any logic change for both interrupts
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC10);
	//enable the over flow interrupts for timer 2 & time
	SET_BIT(TIMSK,TOIE2);
	SET_BIT(TIMSK,TOIE0);
	_delay_ms(50);
	sei();
}

//this will occur only if there is an emergency call from the tiva controller
void usart_listen(void)
{
	uart_data_got=UDR;
	//mutexGiveFromISR
}
//this will occur only if there is an emergency call from the tiva controller
void spi_listen(void)
{
	//wait for safety
	//scan 1
	//wait 
	//scan 2
	//wait
	//scan 3
	
	//scaneduler=E_TRUE;
	//PORTA=SPDR;
	spi_temp_inn=SPDR;
	//SPDR=spi_temp_out;
	
	//mutexGiveFromISR
}