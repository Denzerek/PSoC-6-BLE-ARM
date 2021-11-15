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
#include "motor_task.h"

#define I2C_MAX_EVENTS  2

//#define TRANSMITTER     SUPER_TRANSMITTER
#define TRANSMITTER     

#define ard_print(x)  { TRANSMITTER("[ ARD COMM TASK ] : ");TRANSMITTER(x);TRANSMITTER("\r\n");}
#define ard_printf(x,...)  { TRANSMITTER("[ ARD COMM TASK ] : ");TRANSMITTER(x,__VA_ARGS__);TRANSMITTER("\r\n");}

typedef struct{
    uint32_t i2cEvent;
    char* i2cMessage;
}i2cEvents_s;

void servo_slave_i2c_task(void * arg);
void ardTransmitPWMPercent(motors_t motorNum,uint8_t percent);
void i2cStatusDecode();
/* [] END OF FILE */
