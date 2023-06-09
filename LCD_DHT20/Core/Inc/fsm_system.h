/*
 * fsm_system.h
 *
 *  Created on: May 22, 2023
 *      Author: NHAN
 */

#ifndef INC_FSM_SYSTEM_H_
#define INC_FSM_SYSTEM_H_

#include "global.h"

//Read temp and humi function in here
void Scan_Address_Device();
void Display_temp_humi();
void Init_system();


//void test();


// fsm of overall system
void fsm_system();

#endif /* INC_FSM_SYSTEM_H_ */
