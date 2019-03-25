/*
 * SERVO_ECU.c
 *
 * Created: 3/25/2019 12:17:44 PM
 * Author : MSA
 */ 
#include "hal_PWM.h"
#include "UART.h"

#define SERVO_CTRL_FREQ 50 //20mHZ
#define DELAY_VAL 1000

int main(void)
{
	st_pwm_object pwm_obj1;
	DDRB=0xff;
	usart_init();
	//static msa_u32 usonic1;
	//usonics_init();
	
	pwm_init(&pwm_obj1,TIMER_0,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,1);
	static volatile unsigned char SHOWA [16];		// displaying digital output as it's sent as ascii
	msa_u8 direction_angles[3]={3,6,8};
	//pwm_deinit(&pwm_obj1);
	
	//usonics_init();
	while (1)
	{
		for (msa_s8 i=0;i<2;i++)
		{
			
			usart_send_arr("i = ");
			itoa(i,SHOWA,10);
			usart_send_arr(SHOWA);
			usart_send_arr("  gives an angle of ");
			itoa(direction_angles[i],SHOWA,10);
			usart_send_arr(SHOWA);
			usart_send('\n');
			pwm_edit(&pwm_obj1,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,direction_angles[i]);
			_delay_ms(DELAY_VAL);
		}
		for (msa_s8 i=2;i>0;i--)
		{
			
			usart_send_arr("i = ");
			itoa(i,SHOWA,10);
			usart_send_arr(SHOWA);
			usart_send_arr("  gives an angle of ");
			itoa(direction_angles[i],SHOWA,10);
			usart_send_arr(SHOWA);
			usart_send('\n');
			pwm_edit(&pwm_obj1,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,direction_angles[i]);
			_delay_ms(DELAY_VAL);
		}
	}
}
