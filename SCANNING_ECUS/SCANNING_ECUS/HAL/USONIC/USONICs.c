/*
 * USONICs.c
 *
 * Created: 30/11/2018 04:38:27
 *  Author: Mahmoud
 */ 
#include "USONICs.h"

//  the ultrasonic0 using counter 1
static volatile unsigned int pulse0 = 0;			// integer  to cal the time of the signal transmission and reception
static volatile bool_t state0 = 0;			// integer  to access all though the program
static volatile unsigned int OVF_CNTR_0 = 0;     // integer  to take care of the over-flows of u_sonic_1
static volatile unsigned char SHOWA [16];		// displaying digital output as it's sent as ascii
static volatile bool_t ready_0=E_FALSE;		//used to synchronize & ensure that the sensor reading process is completed

//  the ultrasonic1 using counter 2
static volatile unsigned int pulse1 = 0;			// integer  to cal the time of the signal transmission and reception
static volatile bool_t state1 = 0;			// integer  to access all though the program
static volatile unsigned int OVF_CNTR_1 = 0;     // integer  to take care of the over-flows of u_sonic_1
static volatile unsigned char SHOWB [16];		// displaying digital output as it's sent as ascii
static volatile bool_t ready_1=E_FALSE;		//used to synchronize & ensure that the sensor reading process is completed

//extending the visibility of the uart object that holds the uart configs
extern usart_t uart_obj;					//used to hold the uart configurations
//  the ultrasonic0 using counter 1
msa_u32 read_ultra_sonic0(void) //0000 0011
{
	ready_0=E_FALSE;
	CLEAR_BIT(PORTC,0);	
	_delay_us(2);
	SET_BIT(PORTC,0);	
	_delay_us(15);		//triggering the sensor for 15usec
	CLEAR_BIT(PORTC,0);
	
	while (!ready_0)//wait the sensor reading completion
	;
	ready_0=E_FALSE;	//false it so the next time wait for the next reading process
	_delay_us(50);
	return ( ( pulse0 + ((msa_u32)OVF_VAL*OVF_CNTR_0))/(58) );	//getting the distance based on formula on introduction
	
}
void send_usonic0(msa_u32 COUNTA)
{
	msa_u8 *arr_add1=(msa_u8 *)"usonic0 data = ";
	msa_u8 *arr_add2=(msa_u8 *)"  mm  ";
	itoa(COUNTA,SHOWA,10);
	usart_send_arr(&uart_obj,arr_add1);
	usart_send_arr(&uart_obj,SHOWA);
	usart_send_arr(&uart_obj,arr_add2);
	
}

//  the ultrasonic1 using counter 2
msa_u32 read_ultra_sonic1(void) //0000 0011
{
	ready_1=E_FALSE;
	
	CLEAR_BIT(PORTC,1);
	_delay_us(2);
	SET_BIT(PORTC,1);
	_delay_us(15);		//triggering the sensor for 15usec
	CLEAR_BIT(PORTC,1);
	
	while (!ready_1)//wait the sensor reading completion
	;
	ready_1=E_FALSE;	//false it so th next time wait for the next reading process
	_delay_us(50);
	return ( ( pulse1 + ((msa_u32)OVF_VAL*OVF_CNTR_1))/(58) );	//getting the distance based on formula on introduction   * ((msa_u32)F_CPU/1000000)
}
void send_usonic1(msa_u32 COUNTB)
{
	msa_u8 *arr_add1=(msa_u8 *)"usonic1 data = ";
	msa_u8 *arr_add2=(msa_u8 *)"  mm  ";
	itoa(COUNTB,SHOWA,10);
	usart_send_arr(&uart_obj,arr_add1);
	usart_send_arr(&uart_obj,SHOWA);
	usart_send_arr(&uart_obj,arr_add2);
	
}

ISR(TIMER0_OVF_vect)
{
	OVF_CNTR_0++;
}

ISR(TIMER2_OVF_vect)
{
	OVF_CNTR_1++;
}


 //will test to work as is and later will test using semaphores and the cond will be  if not available return specific val to tell the func that couldn't read the distancve this ime
 //later on if used this algo, notice if the val couldn't be read, dont move the servo this turn :D <3 


//interrupt service routine when there is a change in logic level for the USONIC_0
ISR(INT0_vect)
{

	if (state0==1)//when logic from HIGH to LOW
	{

		TCCR0=0;//disabling counter

		pulse0=TCNT0;//count memory is updated to integer

		TCNT0=0;//resetting the counter memory

		state0=0;
		ready_0=E_TRUE;
		

	}
	else//when logic change from LOW to HIGH
	{

		TCCR0|=(1<<CS00);//enabling counter

		state0=1;
		OVF_CNTR_0=0;

	}

}

//interrupt service routine when there is a change in logic level for the USONIC_0
ISR(INT1_vect)
{

	if (state1==1)//when logic from HIGH to LOW
	{

		TCCR2=0;//disabling counter

		pulse1=TCNT2;//count memory is updated to integer

		TCNT1=0;//resetting the counter memory

		state1=0;
		ready_1=E_TRUE;

	}
	else//when logic change from LOW to HIGH
	{

		TCCR2|=(1<<CS20);//enabling counter

		state1=1;
		OVF_CNTR_1=0;

	}

}