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

#define cap_print(x)  { TRANSMITTER("[ CAP TASK ] : ");TRANSMITTER(x);TRANSMITTER("\r\n");}
#define cap_printf(x,...)  { TRANSMITTER("[ CAP TASK ] : ");TRANSMITTER(x,__VA_ARGS__);TRANSMITTER("\r\n");}


void capsenseTask(void *arg);

/* [] END OF FILE */
