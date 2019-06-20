/*
 * system_funcs.c
 *
 * Created: 6/1/2019 12:14:41 AM
 *  Author: msams
 */
 #include "system_funcs.h"


void system_init(void)
{
	DDRC  = 0x03;	//spi ss_select pins for the two other ecuS
	PORTC = 0x03;	//spi ss_select pins for the two other ecuS
	DDRA  = 0xff;	//leds and motors
	CLEAR_BIT(DDRD,2);	//int-0
	//SET_BIT(PORTD,2);	//pullUp
	CLEAR_BIT(DDRD,3);	//int-1
	//SET_BIT(PORTD,3);	//pullUp
	SET_BIT(DDRD,4);	//beeb
	//LED PINS
	SET_BIT(DDRA,LED_PIN);
	SET_BIT(DDRA,BUZ_PIN);
	//spi init...try polling i.e wait 10 m s or the time the longest scanning task will take plus some
	//time then ask for the status if reading is done or not
	//try to make the delay decreases by time :D
	hal_spiInit(&spi_obj,SPI_1_base,FREQ_BY_4,MASTER_EN,SPI_POLLING,MODE_1,MSB_FIRST);
	//hal_setSpiIsrCallback(&spi_obj,spi_listen);
	//uart init
	usart_init(&uart_obj,B_SENDER_N_RECEIVER,ONE_STP_BIT,NO_PARITY,EIGHT,POLLING_DRIVEN,UART_FALLING_EDGE);
	usart_set_isr_RXC_callback(&uart_obj,usart_listen);
	//pwm init
	SET_BIT(DDRB,PWM_PIN);
	SET_BIT(PORTB,PWM_PIN);
	pwm_init(&pwm_obj,TIMER_0,INVERTED,FAST_PWM,SERVO_CTRL_FREQ,1);
	sei();
	init_interrrupts();
	set_interrupt(INTERRUPT0,RISING_EDGE);
	set_interrupt(INTERRUPT1,RISING_EDGE);
	
}

void hal_spiExchangeDATA_A(str_spi_objectInfo_t * strg_obj,msa_u8 *ByteOUT,msa_u8 *ByteIN)
{
	CLEAR_BIT(PORTC,0);
	hal_spiExchangeDATA(strg_obj,ByteOUT,ByteIN);
	SET_BIT(PORTC,0);
}
void hal_spiExchangeDATA_B(str_spi_objectInfo_t * strg_obj,msa_u8 *ByteOUT,msa_u8 *ByteIN)
{
	CLEAR_BIT(PORTC,1);
	hal_spiExchangeDATA(strg_obj,ByteOUT,ByteIN);
	SET_BIT(PORTC,1);
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
// 	spi_temp_inn=SPDR;
// 	SPDR=spi_temp_out;
}

void move_forward(unsigned char beriod)
{
	SET_BIT  (PORTA,0);
	CLEAR_BIT(PORTA,1);
	SET_BIT  (PORTA,2);
	CLEAR_BIT(PORTA,3);
	while(beriod > 0)
	{
		_delay_ms(1);
		beriod--;
	}
	CLEAR_BIT(PORTA,0);
	CLEAR_BIT(PORTA,2);
}
void move_bckward(unsigned char beriod)
{
	SET_BIT  (PORTA,1);
	CLEAR_BIT(PORTA,0);
	SET_BIT  (PORTA,3);
	CLEAR_BIT(PORTA,2);
	while(beriod > 0)
	{
		_delay_ms(1);
		beriod--;
	}
	CLEAR_BIT(PORTA,1);
	CLEAR_BIT(PORTA,3);
}
void move_right(unsigned char beriod)
{
	SET_BIT  (PORTA,0);
	CLEAR_BIT(PORTA,1);
	SET_BIT  (PORTA,3);
	CLEAR_BIT(PORTA,2);
	while(beriod > 0)
	{
		_delay_ms(1);
		beriod--;
	}
	CLEAR_BIT(PORTA,0);
	CLEAR_BIT(PORTA,3);
}
void move_left(unsigned char beriod)
{
	SET_BIT  (PORTA,1);
	CLEAR_BIT(PORTA,0);
	SET_BIT  (PORTA,2);
	CLEAR_BIT(PORTA,3);
	while(beriod > 0)
	{
		_delay_ms(1);
		beriod--;
	}
	CLEAR_BIT(PORTA,1);
	CLEAR_BIT(PORTA,2);
}
void move_stop(unsigned char beriod)
{
	CLEAR_BIT(PORTA,0);
	CLEAR_BIT(PORTA,1);
	CLEAR_BIT(PORTA,3);
	CLEAR_BIT(PORTA,2);
	while(beriod > 0)
	{
		_delay_ms(1);
		beriod--;
	}
}
