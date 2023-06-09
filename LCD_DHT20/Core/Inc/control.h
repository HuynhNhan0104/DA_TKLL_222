/*
 * control.h
 *
 *  Created on: May 19, 2023
 *      Author: NHAN
 */

#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#include "main.h"
#include "global.h"



//Uart Control functions in here
void Command_parser_fsm();
void HAL_UART_RxCpltCallback ( UART_HandleTypeDef * huart );

void Get_command();

#endif /* INC_CONTROL_H_ */
