/*
 * scheduler.h
 *
 *  Created on: May 19, 2023
 *      Author: NHAN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_



#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_TASK                                            				40
#define NORMAL																0
#define ERROR_SCHEDULER_TOO_MANY_TASK 				1
#define ERROR_NO_TASK_TO_DELETE                             	2

typedef struct {
	void (*pfunction)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t Run;
	uint32_t Task_ID;
} Scheduler_Task;

typedef struct {
    uint32_t Tick;
    uint32_t CurrentSize;
    Scheduler_Task Tasks[MAX_TASK];
    uint32_t Error;
} Scheduler;

void Scheduler_Init(Scheduler* scheduler,uint32_t Tick);
uint32_t Scheduler_Add_Task(Scheduler* scheduler, void (*pfunction)(), uint32_t delay, uint32_t period);
void Scheduler_Update(Scheduler* scheduler);
void Scheduler_Dispatch_Task(Scheduler* scheduler);
uint32_t Scheduler_Delete_Task(Scheduler* scheduler, uint32_t task_ID);
void Scheduler_Clear_Task(Scheduler* scheduler);




#endif /* INC_SCHEDULER_H_ */
