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

#include "common.h"


#define motion_printer(x)       TRANSMITTER("[ MOTION ] : ");TRANSMITTER(x);
#define motion_print(x)         TRANSMITTER("[ MOTION ] : ");TRANSMITTER(x);TRANSMITTER("\r\n");
#define motion_printf(x,...)    TRANSMITTER("[ MOTION ] : ");TRANSMITTER(x,__VA_ARGS__);TRANSMITTER("\r\n");

typedef struct{
    uint32_t i2cEvent;
    char* i2cMessage;
}i2cEvents_s;

void motion_task(void* arg);
/* [] END OF FILE */
