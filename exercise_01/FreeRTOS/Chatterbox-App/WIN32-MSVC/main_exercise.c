/*
 * FreeRTOS Kernel V10.1.1
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/******************************************************************************
 * NOTE: Windows will not be running the FreeRTOS project threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Windows port, or
 * this project application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Windows
 * port for further information:
 * http://www.freertos.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 *
 * NOTE 2:  This file only contains the source code that is specific to exercise 2
 * Generic functions, such FreeRTOS hook functions, are defined
 * in main.c.
 ******************************************************************************
 *
 * NOTE:  Console input and output relies on Windows system calls, which can
 * interfere with the execution of the FreeRTOS Windows port.  This demo only
 * uses Windows system call occasionally.  Heavier use of Windows system calls
 * can crash the port.
 */

/* Standard includes. */
#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* TODO: Priorities at which the tasks are created.
 */

#define task1_priority (1)
#define task2_priority (2)
#define task3_priority (3)


/* TODO: output frequencey
 */

#define mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS pdMS_TO_TICKS( 200UL )

/*-----------------------------------------------------------*/

/*
  * TODO: data structure
  */

struct Data {
	     int flag;
	     char* output;
	
};

/*
 * TODO: C function (prototype) for task
 */
static void task_func(struct Data);


/*-----------------------------------------------------------*/

/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void main_exercise( void )
{
/*
 * TODO: initialize data structures
 */
	struct Data task_data[3];
	
	task_data[0].flag = 0;
	task_data[0].output = "Task1"; 

	task_data[1].flag = 0;
	task_data[1].output = "Task2";

	task_data[2].flag = 1;
	task_data[2].output = "Task3";

	/* 
	 * TODO: Create the task instances.
     */
	xTaskCreate(task_func, "Task1", configMINIMAL_STACK_SIZE,  (void * ) & task_data[0], task1_priority, NULL);
	xTaskCreate(task_func, "Task2", configMINIMAL_STACK_SIZE, (void * ) &task_data[1], task2_priority, NULL);
	xTaskCreate(task_func, "Task3", configMINIMAL_STACK_SIZE, (void * ) &task_data[2], task3_priority, NULL);





	 /*
	  * TODO: Start the task instances.
	  */

	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* 
 * TODO: C function for tasks
 */
static void task_func(void *data) {

	TickType_t xNextWakeTime;
	xNextWakeTime = xTaskGetTickCount();

	struct Data* task_data = (struct Data *)data;

	if (task_data->flag == 0) {
		while (1) {
			printf("%s \n", task_data->output);

			vTaskDelayUntil(&xNextWakeTime,  mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS);
		}
	}
	else {
		int cnt = 0;
		while (cnt < 5) {
			printf("%s \n", task_data->output);

			vTaskDelayUntil(&xNextWakeTime, mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS);

			cnt++;
		}
		printf("%s is termianted and to be deleted \n", task_data->output);
		TaskHandle_t task_handle = xTaskGetCurrentTaskHandle();
		vTaskDelete(task_handle);
	}
	return;
}



