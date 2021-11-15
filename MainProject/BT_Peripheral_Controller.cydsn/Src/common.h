/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#pragma once

#include "FreeRTOS.h"
#include "project.h"
#include "semphr.h"
#include "task.h"
#include <stdio.h>
#include "event_groups.h"


#define SUPER_TRANSMITTER   printf
//#define TRANSMITTER 

#define serialPrint(x)          { SUPER_TRANSMITTER("[ UART ] : ");SUPER_TRANSMITTER(x);SUPER_TRANSMITTER("\r\n");}
#define serialPrintf(x,...)     { SUPER_TRANSMITTER("[ UART ] : ");SUPER_TRANSMITTER(x,__VA_ARGS__);SUPER_TRANSMITTER("\r\n");}
#define serialPrinter(x)        SUPER_TRANSMITTER(x)



#define UART_TASK_STACK_SIZE                400
#define UART_TASK_PRIORITY                  2

#define CAPSENSE_TASK_STACK_SIZE            2*1024
#define CAPSENSE_TASK_PRIORITY              2

#define BLE_TASK_STACK_SIZE                 4*1024
#define BLE_TASK_PRIORITY                   1

#define MOTOR_TASK_STACK_SIZE               400
#define MOTOR_TASK_PRIORITY                 2

#define PWM_TASK_STACK_SIZE                 400
#define PWM_TASK_PRIORITY                   1

#define EZI2C_TASK_STACK_SIZE               400
#define EZI2C_TASK_PRIORITY                 2

#define ARDUINO_COMM_TASK_STACK_SIZE        400
#define ARDUINO_COMM_TASK_PRIORITY          2


#define MAJOR_VERSION   1   
#define MINOR_VERSION   0
#define PATCH_VERSION   0

#define PROJECT_NAME    "BLE PERIPHERAL CONTROLLER"

//Should be called in the highest priority task
#define UART_HIGH_START() UART_Start();CyDelay(10);serialPrint("\x1b[2J\x1b[;H");

extern QueueHandle_t servoControlQueue;
extern QueueHandle_t pwmQueue;
                        
extern EventGroupHandle_t pwmEventGroup;
#define PWM_EVENT_I2C       ( 1 << 0 )
#define PWM_EVENT_BLE       ( 1 << 1 )
#define PWM_EVENT_ALL       ( PWM_EVENT_I2C | PWM_EVENT_BLE  )

char temp[100];


/* [] END OF FILE */
