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

#define serialPrint(x)  { SUPER_TRANSMITTER("[ UART ] : ");SUPER_TRANSMITTER(x);SUPER_TRANSMITTER("\r\n");}
#define serialPrintf(x,...)  { SUPER_TRANSMITTER("[ UART ] : ");SUPER_TRANSMITTER(x,__VA_ARGS__);SUPER_TRANSMITTER("\r\n");}


#define PJT_NAME    "   MAIN CONTROLLER   " 

//Should be called in the highest priority task
#define UART_HIGH_START() UART_Start();serialPrint("\x1b[2J\x1b[;H");


//Should be called in the lowest priority task
#define START_UP_DISP()   { serialPrint("System Init Done.");\
                            serialPrint("======================================"); \
                            serialPrintf("=======%s=========",PJT_NAME); \
                            serialPrint("======================================"); \
                        }
                            
                        
extern QueueHandle_t servoControlQueue;
extern QueueHandle_t pwmQueue;
                        
extern EventGroupHandle_t pwmEventGroup;
#define PWM_EVENT_I2C       ( 1 << 0 )
#define PWM_EVENT_BLE       ( 1 << 1 )
#define PWM_EVENT_ALL       ( PWM_EVENT_I2C | PWM_EVENT_BLE  )

char temp[100];


/* [] END OF FILE */
