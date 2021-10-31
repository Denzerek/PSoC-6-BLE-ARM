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


#define TRANSMITTER     SUPER_TRANSMITTER
//#define TRANSMITTER     

#define ble_print(x)    TRANSMITTER("[ BLE ] : ");TRANSMITTER(x);TRANSMITTER("\r\n");
#define ble_printf(x,...)    TRANSMITTER("[ BLE ] : ");TRANSMITTER(x,__VA_ARGS__);TRANSMITTER("\r\n");

#define MOTORS_TO_CONTROL_MAX   (M_MAX-1) * 2

typedef struct{
    motors_t motor;
    uint16_t BLECharacteristicHandle;
    void (*callBackfn)(motors_t motor,int8_t percent,uint8_t flags);
}motorToControl_t;



void bleTask(void* arg);
void updateMotorsGatt(motors_t motor,int8_t percent,uint8_t flags);
void updateRelativeMotorPos(motors_t motor,int8_t percent,uint8_t flags);


/* [] END OF FILE */
