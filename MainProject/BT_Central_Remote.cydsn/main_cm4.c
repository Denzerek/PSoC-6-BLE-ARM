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

#include "common.h"
#include "ble_task.h"
#include "uart_task.h"
#include "capsense_task.h"
#include "motion_task.h"

EventGroupHandle_t systemInputMode;

/*
Author : Alen Austin
Brief : This project canot be used as a standalone one but in combination 
with the BT_Peripheral_Controller project.

COMBO
=====
As a combo project, this firmware should be loaded into one 062 BLE pioneer
kit and the firmware of BT_Peripheral_Controller project into a different 062 BLE
pioneer kit. Then start both, and u will be able to see the BLE central
device connect to the peripheral device  and user can change the color
of the peripheral device by pressing the '+' or '-' in the uart terminal 
of this central device.
*/
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    UART_Start();

    Cy_GPIO_Set(GREEN_PORT,GREEN_NUM);
    Cy_GPIO_Clr(RED_PORT,RED_NUM);
    CyDelay(10); 
    
    systemInputMode = xEventGroupCreate();
    xEventGroupSetBits(systemInputMode,MODE_CAPSENSE);
    
    serialPrint("\x1b[2J\x1b[;H");
    serialPrint("System Init Done.");
    serialPrint( "====================================="); 
    serialPrintf("==== BLE CENTRAL REMOTE v%d.%d.%d ====",MAJOR_VERSION,MINOR_VERSION,PATCH_VERSION); 
    serialPrint( "====================================="); 
    setvbuf(stdin,0,_IONBF,0);
    
    /* BLE Central Task for communicating motor position to BLE peripheral*/
    xTaskCreate(bleTask," BLE CENTRAL TASK",BLE_TASK_STACK_SIZE,0,BLE_TASK_PRIORITY,0);
    
    /*UART Task for relative motor positioning*/
    xTaskCreate(UartTask," UART TASK",UART_TASK_STACK_SIZE,0,UART_TASK_PRIORITY,0);
    
    /* Capasense task for absolute motor positioning*/
    xTaskCreate(capsenseTask," CAPSENSE TASK",CAPSENSE_TASK_STACK_SIZE,0,CAPSENSE_TASK_PRIORITY,0);
    
    /* Motion task for absolute motor positioning*/
    xTaskCreate(motionTask," MOTION TASK",MOTION_TASK_STACK_SIZE,0,MOTION_TASK_PRIORITY,0);
    vTaskStartScheduler();
    
    for(;;);
}

/* [] END OF FILE */
