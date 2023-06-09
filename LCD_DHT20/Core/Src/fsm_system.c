/*
 * fsm_system.c
 *
 *  Created on: May 22, 2023
 *      Author: NHAN
 */

#include "fsm_system.h"
//Read temp and humi function in here
void Scan_Address_Device(I2C_HandleTypeDef* hi2c){
	HAL_UART_Transmit_IT(&huart2 , (uint8_t*)&sending , sprintf(sending,"scanning address device . . . \n")) ;
	for(uint8_t index = 0; index < 128; ++index){
		if(HAL_I2C_IsDeviceReady(hi2c, index << 1, 1, 100)==HAL_OK){
			HAL_UART_Transmit_IT(&huart2 , (uint8_t*)&sending , sprintf(sending,"Address device is: %x \n",index)) ;
		}
	}
}

void Display_temp_humi(){
	LCD_I2C_Clear(&LCD);
	DHT20_I2C_Read(&DHT20, &temperature, &humidity);
	sprintf(line1,"Temp: %.2f%cC",temperature,0xDF);
	sprintf(line2,"Humi: %.2f%%",humidity);
	LCD_I2C_SetCursor(&LCD, 0, 0);
	LCD_I2C_WriteString(&LCD, line1);
	LCD_I2C_SetCursor(&LCD, 0, 1);
	LCD_I2C_WriteString(&LCD, line2);
}


// fsm of overall system
void Init_system(){
	LCD_I2C_Init(&LCD, &hi2c1,0x4E, 16, 2);
	DHT20_I2C_Init(&DHT20, &hi2c1, 0x38);
	LCD_I2C_SetCursor(&LCD, 0, 0);
	LCD_I2C_WriteString(&LCD, "SYSTEM BOOSTING ...");
	command_parser_state = IDLE;
//	system_state = SYSTEM_INIT;
	temperature = 0;
	humidity = 0;
}






void fsm_system(){
	switch(system_state){
		case SYSTEM_INIT:
			// initial the system
			//todo
			Scheduler_Add_Task(&scheduler, Init_system, 0, 0);

			// change state
			//do this task repeatly each 5s
			// in this time if isCaption_flag == 1 , temp and humi will be 0;
			Scheduler_Add_Task(&scheduler, Display_temp_humi,5000,5000);
			system_state = AUTO;
			break;
		case AUTO:
			//todo
			// change  state
			if(isCapture_flag) {
				isCapture_flag = 0;
				// delete task read_temp_humi
				Scheduler_Delete_Task(&scheduler, scheduler.CurrentSize - 1);
				HAL_UART_Transmit_IT(&huart2 , (uint8_t*)&sending , sprintf(sending,"!Temp: %.2f, Humi: %.2f# \n",temperature,humidity) );
				system_state = CAPTURE;
			}

			if(isReset_flag){
				isReset_flag = 0;
				// delete task read_temp_humi
				Scheduler_Delete_Task(&scheduler, scheduler.CurrentSize - 1);
				system_state =SYSTEM_INIT;
			}

			break;
		case CAPTURE:
			//todo
			if(isAuto_flag){
				isAuto_flag = 0;
				Scheduler_Add_Task(&scheduler, Display_temp_humi,0,5000);
				system_state = AUTO;
			}
			if(isReset_flag){
				isReset_flag = 0;
				system_state =SYSTEM_INIT;
			}
			// change  state
			break;
		default:
			break;
	}
}
