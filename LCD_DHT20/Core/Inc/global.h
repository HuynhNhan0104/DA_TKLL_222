/*
 * global.h
 *
 *  Created on: May 21, 2023
 *      Author: NHAN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stdio.h"
#include "lcd_i2c.h"
#include "dht20.h"
#include "scheduler.h"
#include "stm32f1xx_hal.h"
//declare variables for Reading temp and humi Operation in here
extern float temperature;
extern float humidity;
extern char line1[16];
extern char line2[16];


extern I2C_HandleTypeDef hi2c1;
extern LCD_I2C_DEVICE LCD;
extern DHT20_I2C_DEVICE DHT20;

//declare variable for Uart control in here
# define MAX_BUFFER_SIZE 									30
#define IDLE															0
#define GET_START												1
#define GET_C														2
#define  GET_R														3
#define GET_A														4


extern UART_HandleTypeDef huart2;

extern uint8_t command_parser_state;

extern uint8_t data;
extern uint8_t data_flag;
extern uint8_t current_index_write;
extern uint8_t current_index_read;
extern uint8_t buffer_uart[MAX_BUFFER_SIZE ];

extern char sending[40];

extern uint8_t isCapture_flag;
extern uint8_t isAuto_flag;
extern uint8_t isReset_flag;

// declare scheduler
extern Scheduler scheduler;

// declare for fsm system
#define SYSTEM_INIT							10
#define AUTO										11
#define CAPTURE									12


extern uint8_t system_state;



#endif /* INC_GLOBAL_H_ */
