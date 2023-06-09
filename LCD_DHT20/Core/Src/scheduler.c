/*
 * scheduler.c
 *
 *  Created on: May 19, 2023
 *      Author: NHAN
 */

#include "scheduler.h"



void Scheduler_Init(Scheduler* scheduler,uint32_t Tick){
    scheduler->CurrentSize = 0;
    scheduler->Tick = Tick;
    scheduler->Error = NORMAL;
    // init an array with 0;
    for(int i = 0; i < MAX_TASK; ++i){
        scheduler->Tasks[scheduler->CurrentSize].pfunction = 0;
		scheduler->Tasks[scheduler->CurrentSize].Delay = 0;
		scheduler->Tasks[scheduler->CurrentSize].Period = 0;
		scheduler->Tasks[scheduler->CurrentSize].Run = 0;
		scheduler->Tasks[scheduler->CurrentSize].Task_ID = 0;
    }

}
uint32_t Scheduler_Add_Task(Scheduler* scheduler,void (*pfunction)(),uint32_t delay, uint32_t period){
    // add in normal
    if(scheduler->CurrentSize < MAX_TASK){
        //assign new task to CurrentSize position;
        //we increase CurrentSize to 1;
		scheduler->Tasks[scheduler->CurrentSize].pfunction = pfunction;
		scheduler->Tasks[scheduler->CurrentSize].Delay = delay;
		scheduler->Tasks[scheduler->CurrentSize].Period = period;
		scheduler->Tasks[scheduler->CurrentSize].Run = 0;
		scheduler->Tasks[scheduler->CurrentSize].Task_ID = scheduler->CurrentSize;
		scheduler->CurrentSize++;
		return scheduler->Error;
	}
    //overflow
    // get error
	else{
		scheduler->Error = ERROR_SCHEDULER_TOO_MANY_TASK;
		return scheduler->Error;
	}
}


//callback after each Tick (s)
void Scheduler_Update(Scheduler* scheduler){
    for(int index = 0 ; index  < scheduler->CurrentSize ; ++index){
		if(scheduler->Tasks[index].Delay > 0){
			scheduler->Tasks[index].Delay -= scheduler->Tick;
		}
		else{
			scheduler->Tasks[index].Run += 1;
			if(scheduler->Tasks[index].Period > 0){
				scheduler->Tasks[index].Delay = scheduler->Tasks[index].Period;
			}
		}
	}
}


// this function place in while(1), execute the function which need to run(Run = 1); delete task has period = 0 after this task completely run.
void Scheduler_Dispatch_Task(Scheduler* scheduler){
    for(int index = 0 ; index  < scheduler->CurrentSize; ++index){
		if(scheduler->Tasks[index].Run >0){
			(*scheduler->Tasks[index].pfunction)();
			scheduler->Tasks[index].Run -= 1;
			if(scheduler->Tasks[index].Period == 0){
				Scheduler_Delete_Task(scheduler,index);
			}
		}
	}
}

uint32_t Scheduler_Delete_Task(Scheduler* scheduler, uint32_t task_ID){
    // scheduler had no task to delete or the position ,which need to be deleted, is over the CurrentSize
    if(task_ID >= scheduler->CurrentSize || scheduler->CurrentSize <= 0){
		scheduler->Error = ERROR_NO_TASK_TO_DELETE ;
		return scheduler->Error;
	}
    //delete this task
	else{
			for(int index = task_ID ; index < scheduler->CurrentSize - 1; ++index){
				scheduler->Tasks[index].pfunction = scheduler->Tasks[index + 1].pfunction;
				scheduler->Tasks[index].Delay = scheduler->Tasks[index + 1].Delay;
				scheduler->Tasks[index].Period = scheduler->Tasks[index + 1].Period;
				scheduler->Tasks[index].Run = scheduler->Tasks[index + 1].Run;
				scheduler->Tasks[index].Task_ID = index;
			}
			scheduler->Tasks[scheduler->CurrentSize - 1].pfunction =0x0000;
			scheduler->Tasks[scheduler->CurrentSize - 1].Delay = 0;
			scheduler->Tasks[scheduler->CurrentSize - 1].Period = 0;
			scheduler->Tasks[scheduler->CurrentSize - 1].Run = 0;
			scheduler->Tasks[scheduler->CurrentSize - 1].Task_ID = 0;
			scheduler->CurrentSize--;
		return scheduler->Error;
	}
}


void Scheduler_Clear_Task(Scheduler* scheduler){
	while(scheduler->CurrentSize > 0){
		scheduler->Tasks[scheduler->CurrentSize].pfunction =0x0000;
		scheduler->Tasks[scheduler->CurrentSize].Delay = 0;
		scheduler->Tasks[scheduler->CurrentSize].Period = 0;
		scheduler->Tasks[scheduler->CurrentSize].Run = 0;
		scheduler->Tasks[scheduler->CurrentSize].Task_ID = 0;
		scheduler->CurrentSize--;
	}
}




