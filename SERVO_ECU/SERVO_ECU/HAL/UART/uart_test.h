/*
 * test_1.h
 *
 * Created: 3/26/2019 2:15:17 PM
 *  Author: MSA
 */ 

#if 0
/*
 * HAL_USART.c
 *
 * Created: 11/09/2018 20:51:15
 * Author : Mahmoud_saad
 */ 

//#include <avr/io.h>
#include "hal_USART.h"
	usart_t usart_1;

void usart_read(void);
	msa_u8 temp_val2='9';
int main(void)
{
    /* Replace with your application code */

	usart_init(&usart_1,B_SENDER_N_RECEIVER,ONE_STP_BIT,NO_PARITY,EIGHT,INTERRUPT_DRIVEN,FALLING_EDGE); 
    msa_u8 got_val;
	DDRA=0xff;
	msa_u8 temp_val='5';//new line in protues
	msa_u8 *arr_add=(msa_u8 *)"you gave me this =>";
	msa_u8 *arr_add2=(msa_u8 *)"put your val ";
	//msa_u8 *got_arr;
	usart_set_isr_RXC_callback(&usart_1,usart_read);
	//msa_u8 arr[10];
	//usart_set_isr_TXC_callback(&usart_1,usart_send);
	sei();
	while (1) 
    {
// 		usart_send_byte(&usart_1,&temp_val);
// 		PORTA=0xff;
// 		_delay_ms(500);//test foring
// 		PORTA=0x55;
// 		_delay_ms(500);
		
		//usart_receive_arr(&usart_1,arr,5);
 		//usart_send_arr(&usart_1,arr);
 		//usart_send_byte(&usart_1,(msa_u8 *)&val);
		//usart_send_arr(&usart_1,arr_add2);	
		//_delay_ms(500);
		usart_receive_byte(&usart_1,&got_val);
		//_delay_ms(500);
		//usart_send_byte(&usart_1,&temp_val);
		//usart_send_arr(&usart_1,arr_add);
		//_delay_ms(500);
		//usart_send_byte(&usart_1,&got_val);
		//usart_send_byte(&usart_1,&temp_val);
		if (got_val == '5')
		{
			PORTA++;
		}
		_delay_ms(100);
		
		
		//usart_send_byte(&usart_1,&temp_val);
		//usart_receive_arr(&usart_1,got_arr);
		//usart_send_arr(&usart_1,arr_add);
		//usart_send_arr(&usart_1,got_arr);
    }
}
msa_u8 temp_got;
void usart_read(void)
{
	PORTB++;
	//usart_send_byte(&usart_1,&temp_val2);
	//cli();
	temp_got=UDR;
	//UCSRA|=(1<<RXC);
}

ISR(USART_RXC_vect)
{
	usart_read();
}




#endif /* TEST_1_H_ */