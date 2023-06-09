/*
 * control.c
 *
 *  Created on: May 19, 2023
 *      Author: NHAN
 */

#include "control.h"




void Get_command(){
	if(current_index_read != current_index_write ) {
			  Command_parser_fsm();
			  current_index_read++;
			  if(current_index_read == MAX_BUFFER_SIZE) current_index_read = 0;
			  data_flag--;
		  }
}
//Uart Control functions in here
void HAL_UART_RxCpltCallback ( UART_HandleTypeDef * huart ) {
	if( huart -> Instance == USART2 ) {
			HAL_UART_Receive_IT(&huart2 , &data , 1);
			buffer_uart[current_index_write] = data;
//			HAL_UART_Transmit(&huart2 , &buffer_uart[current_index_write] , 1, 100);
			current_index_write++;
			data_flag++;
			if(current_index_write == MAX_BUFFER_SIZE) current_index_write = 0;


	}
}

void Command_parser_fsm(){
		switch(command_parser_state){
			case IDLE:
				if(buffer_uart[current_index_read] == (uint8_t) '!')  {
					command_parser_state = GET_START;
				}
				break;
			case GET_START:
				if(buffer_uart[current_index_read]  == (uint8_t) 'C'){
					command_parser_state = GET_C;
				}
				else if(buffer_uart[current_index_read]  == (uint8_t) 'R') {
					command_parser_state = GET_R;
				}
				else if(buffer_uart[current_index_read]  == (uint8_t) 'A') {
					command_parser_state = GET_A;
				}
				break;

			case GET_C:
				if(buffer_uart[current_index_read]  == (uint8_t) '#') {
					isCapture_flag = 1;
					command_parser_state =IDLE;
				}
				break;

			case GET_R:
				if(buffer_uart[current_index_read] == (uint8_t) '#') {
					isReset_flag = 1;
					command_parser_state =IDLE;
				}
				break;
			case GET_A:
				if(buffer_uart[current_index_read] == (uint8_t) '#') {
					isAuto_flag = 1;
					command_parser_state =IDLE;
				}
				break;

		}
}










