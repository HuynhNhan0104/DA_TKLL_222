/*
 * global.c
 *
 *  Created on: May 21, 2023
 *      Author: NHAN
 */

#include "global.h"

I2C_HandleTypeDef hi2c1;
LCD_I2C_DEVICE LCD;
DHT20_I2C_DEVICE DHT20;
//declare variables for Reading temp and humi Operation in here
float temperature = 0;
float humidity = 0;
char line1[16];
char line2[16];
//declare variable for Uart control in here


UART_HandleTypeDef huart2;

uint8_t command_parser_state = IDLE;

uint8_t data = 0;
uint8_t data_flag = 0;
uint8_t current_index_write = 0;
uint8_t current_index_read = 0;
uint8_t buffer_uart[MAX_BUFFER_SIZE ] = {0};
char sending[40];


uint8_t isCapture_flag = 0;
uint8_t isAuto_flag = 0;
uint8_t isReset_flag = 0;
// declare scheduler
Scheduler scheduler;


// declare for fsm system

uint8_t system_state = SYSTEM_INIT;
