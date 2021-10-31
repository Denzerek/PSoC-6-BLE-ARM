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

#define TRANSMITTER     SUPER_TRANSMITTER
//#define TRANSMITTER     

#define ezi2cPrint(x)  { TRANSMITTER("[ EZI2C ] : ");TRANSMITTER(x);TRANSMITTER("\r\n");}
#define ezi2cPrintf(x,...)  { TRANSMITTER("[ EZI2C ] : ");TRANSMITTER(x,__VA_ARGS__);TRANSMITTER("\r\n");}

void ezI2CTask(void * arg);

/* [] END OF FILE */
