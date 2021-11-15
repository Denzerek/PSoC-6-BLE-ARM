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


#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "semphr.h"
#include "limits.h"
#include "event_groups.h"

#define MAJOR_VERSION   1   
#define MINOR_VERSION   0
#define PATCH_VERSION   0

#define PROJECT_NAME    "BLE CENTRAL REMOTE"


#define TRANSMITTER     printf

#define MODE_MOTION     (1<<0)
#define MODE_CAPSENSE   (1<<1)

#define serialPrint(x)          { TRANSMITTER("[ UART ] : ");TRANSMITTER(x);TRANSMITTER("\r\n");}
#define serialPrintf(x,...)     { TRANSMITTER("[ UART ] : ");TRANSMITTER(x,__VA_ARGS__);TRANSMITTER("\r\n");}
#define seralPrinter(x)         TRANSMITTER(x)

#define UART_TASK_STACK_SIZE            1024
#define UART_TASK_PRIORITY              2

#define CAPSENSE_TASK_STACK_SIZE         1024
#define CAPSENSE_TASK_PRIORITY           2

#define MOTION_TASK_STACK_SIZE          1024
#define MOTION_TASK_PRIORITY            2

#define BLE_TASK_STACK_SIZE             8*1024
#define BLE_TASK_PRIORITY               1

extern EventGroupHandle_t systemInputMode;


void startUpInfo();

/* [] END OF FILE */
