/*
 * SERVO_ECU.c
 *
 * Created: 3/25/2019 12:17:44 PM
 * Author : MSA
 * Main test_1,without RTOS..note The value specifies the number of words the stack can hold, not the number of bytes.  
 */ 
#include "INCLUDES.h"
#include "system_funcs.h"

#define PRESS_VAL	150

#define AUTO_SYS	'z'
#define MANU_SYS	'x'
#define OFF_SYS		 0

#define RESET_SYS	'c'

#define MV_FORWARD	'v'
#define MV_BACKWARD 'b'
#define MV_LEFT		'n'
#define MV_RIGHT	'm'

#define FL_LIGHT	'p'
#define FR_LIGHT	'u'
#define BL_LIGHT	'o'
#define BR_LIGHT	'y'

#define BEEEEEEEEB	'i'

//global variables
volatile msa_u8			SHOWA [16];					// displaying digital output as it's sent as ascii
volatile msa_u8			uart_data_got=0;			//used to listen to the tiva calls 
volatile msa_u8			iteration_counter;
volatile msa_u8			servo_direction[10]={2,3,4,5,6,7,6,5,4,3};	//re-edit=delete this useless array
volatile st_pwm_object			pwm_obj;					//used as a container of the pwm configurations
volatile str_spi_objectInfo_t	spi_obj;					//used to hold the spi configurations
volatile usart_t				uart_obj;					//used to hold the uart configurations
volatile msa_u8					sys_mode=OFF_SYS;

volatile msa_u8 spi_temp_out=0;
volatile msa_u8 spi_temp_inn=0;
volatile msa_u8 uart_temp=0;
volatile msa_u8 *uart_welcome =			"=>Welcome to the system\n=>two modes possible:-\n=>AUTO(press Auto)\tManual(press Manual)\n<=";
volatile msa_u8 *uart_wrong_command =	"sorry, this command isn't applicable";
volatile msa_u8 *uart_manual_active =	"now the manual mode is active. you may control by the keypad on the screen";
volatile msa_u8 *uart_automatic_active= "now the automatic mode is active. you may stop me with the RESET button";
volatile msa_u8 *obstacle_array =		"Caution, there is an obstacle ahead!!";
int main(void)
{
	system_init();
	//sei();
	while (1)
	{
		//send uart which mode??
		usart_send_arr(&uart_obj,uart_welcome);
		//possible>> auto-avoidance and remote-controlled
		//read the uart with a while not interrupt
		usart_receive_byte(&uart_obj,&uart_temp);
		//auto>>
		if (uart_temp == AUTO_SYS)
		{
			usart_send_arr(&uart_obj,uart_automatic_active);
			sys_mode=AUTO_SYS;
			//while not quit
			while (uart_temp != RESET_SYS )
			{
				// 0:1:2 Servo direction
				for (iteration_counter=0; iteration_counter < 10; iteration_counter++)
				{
					//pwm
					move_forward(350);
					pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,servo_direction[iteration_counter]);
					//_delay_ms(SERVO_DELAY_VAL);
				}
				if (UDR == RESET_SYS)
				{
					break;
				}
			}
		} 
		else if(uart_temp == MANU_SYS)   //r-controlled>>
		{
			usart_send_arr(&uart_obj,uart_manual_active);
			sys_mode=MANU_SYS;
			//while not quit
			while (uart_temp != RESET_SYS )
			{
				usart_receive_byte(&uart_obj,&uart_temp);
				//if 4ard/bkward/lift/right>>set the servo to the front/bkward/lift/right
				if		(uart_temp == MV_FORWARD)
				{
					//scan the distance if there is an obstacle stop
					//send >>an obstacle,please turn right or lift or move 4ard or bkward
					//if not>>move for 200ms
					//pwm
					pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,3);
					move_forward(PRESS_VAL);
				} 
				else if (uart_temp == MV_BACKWARD)
				{
					//scan the distance if there is an obstacle stop
					//send >>an obstacle,please turn right or lift or move 4ard or bkward
					//if not>>move for 200ms
					//pwm
					pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,3);
					move_bckward(PRESS_VAL);
				} 
				else if (uart_temp == MV_RIGHT)
				{
					//scan the distance if there is an obstacle stop
					//send >>an obstacle,please turn right or lift or move 4ard or bkward
					//if not>>move for 200ms
					//pwm
					pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,7);
					move_right(PRESS_VAL);
				} 
				else if (uart_temp == MV_LEFT)
				{
					//scan the distance if there is an obstacle stop
					//send >>an obstacle,please turn right or lift or move 4ard or bkward
					//if not>>move for 200ms
					//pwm
					pwm_edit(&pwm_obj,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,7);
					move_left(PRESS_VAL);
				}
				else if (uart_temp == BEEEEEEEEB)
				{
					TOGGLE_BIT(PORTD,4);
				}
				else if (uart_temp == FL_LIGHT)
				{
					TOGGLE_BIT(PORTA,4);
				}
				else if (uart_temp == FR_LIGHT)
				{
					TOGGLE_BIT(PORTA,5);
				}
				else if (uart_temp == BL_LIGHT)
				{
					TOGGLE_BIT(PORTA,6);
				}
				else if (uart_temp == BR_LIGHT)
				{
					TOGGLE_BIT(PORTA,7);
				}
			}
		sys_mode=OFF_SYS;
		}
		else if(uart_temp == '\n')
		{
			//donothing this is just to neglict the end flag from the mobile app
		}
		else//neither manual nor auto
		{
			usart_send_arr(&uart_obj,uart_wrong_command);
		}
	}	//while_system
	//if any error happened and missed the previous loop this will cover that error and try to catch 
	//and i'll know by the change in the system behavior 
	while(1)
	{
		//system fail alarm
		//BUZ on
		BUZ_ON();
		//delay 250
		_delay_ms(200);
		//BUZ off
		BUZ_OF();
		//delay 250
		_delay_ms(200);
	}
	return 0;
}

ISR(INT0_vect)
{
	// 		movement_stop();
	move_stop(10);
	// 		read spi
	usart_send_arr(&uart_obj,obstacle_array);
	hal_spiExchangeDATA_A(&spi_obj,&spi_temp_out,&spi_temp_inn);

		if (spi_temp_inn == OBSTACLE_A1)
		{
			move_right(350);
		} 
		else
		{
			move_left(350);
		}
		spi_temp_inn=0;

}
ISR(INT1_vect)
{
	// 		movement_stop();
	move_stop(10);
	// 		read spi
	usart_send_arr(&uart_obj,obstacle_array);
	hal_spiExchangeDATA_A(&spi_obj,&spi_temp_out,&spi_temp_inn);

	if (spi_temp_inn == OBSTACLE_A1)
	{
		move_left(350);
	}
	else
	{
		move_right(350);
	}
	spi_temp_inn=0;
		
}