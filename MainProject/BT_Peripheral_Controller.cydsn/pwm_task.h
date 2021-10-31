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

//#define TRANSMITTER     SUPER_TRANSMITTER
#define TRANSMITTER     

#define pwm_print(x)  { TRANSMITTER("[ PWM TASK ] : ");TRANSMITTER(x);TRANSMITTER("\r\n");}
#define pwm_printf(x,...)  { TRANSMITTER("[ PWM TASK ] : ");TRANSMITTER(x,__VA_ARGS__);TRANSMITTER("\r\n");}


void pwmTask(void * arg);

/* [] END OF FILE */
