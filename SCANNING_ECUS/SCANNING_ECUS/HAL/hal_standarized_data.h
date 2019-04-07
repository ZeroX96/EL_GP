/*
 * hal_standarized_data.h
 *
 * Created: 3/28/2019 5:57:34 AM
 *  Author: MSA
 */ 


#ifndef HAL_STANDARIZED_DATA_H_
#define HAL_STANDARIZED_DATA_H_

//UART//UART//UART//UART//UART//UART
//UART//UART//UART//UART//UART//UART
//UART//UART//UART//UART//UART//UART

//AT_SCAN-->>TI_MAIN
#define OBSTACLE_A1_0	'A'	//	- ;
#define OBSTACLE_A1_1	'B'	//	/ ;
#define OBSTACLE_A1_2	'C'	//	| ;

#define OBSTACLE_A2_0	'D'	//	| ;
#define OBSTACLE_A2_1	'E'	//	\ ;
#define OBSTACLE_A2_2	'F'	//	- ;

#define OBSTACLE_B1_0	'G'	//	| ;
#define OBSTACLE_B1_1	'H'	//	\ ;
#define OBSTACLE_B1_2	'I'	//	- ;

#define OBSTACLE_B2_0	'J'	//	- ;
#define OBSTACLE_B2_1	'K'	//	/ ;
#define OBSTACLE_B2_2	'L'	//	| ;

#define NO_OBSTACLES	'M'	//  O ;

//TI_MAN-->>AT_SERVO
#define STOP_SERVO		'N'
#define RESUME_SERVO	'O'


//SPI//SPI//SPI//SPI//SPI//SPI//SPI
//SPI//SPI//SPI//SPI//SPI//SPI//SPI
//SPI//SPI//SPI//SPI//SPI//SPI//SPI

#define SCAN_YA_MEGA	'P'

#define SCANNING_DONE	'Q'




#endif /* HAL_STANDARIZED_DATA_H_ */