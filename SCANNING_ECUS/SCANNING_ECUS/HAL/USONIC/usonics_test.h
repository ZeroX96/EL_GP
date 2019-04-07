/*
 * usonics_test.h
 *
 * Created: 4/7/2019 10:37:31 AM
 *  Author: MSA
 */ 


#ifndef 0
#include "INCLUDES.h"
void usonics_init(void);
int main(void)
{
	usonics_init();
	static msa_u32 usonic0;
	static msa_u32 usonic1;
	while (1)
	{
		usonic0=read_ultra_sonic0();
		send_usonic0(usonic0);	//NOTE U R SENDING THE ASCII CODE,VALUES
		usonic1=read_ultra_sonic1();
		send_usonic1(usonic1);
		//test neglictting the values lower than 380 and higher than 1000 4ex so i'm more precised and in safe region
		if ( (usonic1 <= 450))// && (usonic1 > 0) )
		{
			usonic1=read_ultra_sonic1();
			send_usonic1(usonic1);
			PORTA=0xff;
		}
		else
		{
			PORTA=0x00;
		}
		if ( (usonic0 <= 450))// && (usonic0 > 0) )
		{
		 	usonic0=read_ultra_sonic0();
		 	send_usonic0(usonic0);
		 	PORTA=0xff;
		}
		else
		{
		 	PORTA=0x00;
		}
		usart_send('\n');
		_delay_ms(1000);
		// 		 //(void)usart_recve();
	}
	return 0;
}
void usonics_init(void)
{
	DDRA=0xff;
	DDRC=0x03;
	usart_init();
	//ultrasonic
	DDRD &=~(3<<2);      //setting the interrupt pin as an input
	_delay_ms(50);
	GICR|=(1<<INT0)|(1<<INT1);//	//enabling interrupt0 & interrupt1
	MCUCR|=(1<<ISC00)|(1<<ISC10);   //setting interrupt triggering at any logic change for both interrupts
	TIMSK|=(1<<TOIE2)|(1<<TOIE0);	//enable the over flow interrupts for timer 2 & time 0
	sei();               //enabling global interrupts
}

#endif /* USONICS_TEST_H_ */