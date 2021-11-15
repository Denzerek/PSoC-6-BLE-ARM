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

/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "ble_task.h"
#include "uart_task.h"
#include "capsense_task.h"
#include "common.h"
#include "motion_task.h"

/*******************************************************************************
* Global Variables
********************************************************************************/
EventGroupHandle_t systemInputMode;

/*******************************************************************************
 * Function Name: main
 ********************************************************************************
 * Summary:
 * Main routine for the CM4 core.
 * This firmware canot be used as a standalone one but in combination 
 * with the BT_Peripheral_Controller firmware.
 * COMBO
 * =====
 * As a combo project, this firmware should be loaded into one 062 BLE pioneer
 * kit and the firmware of BT_Peripheral_Controller project into a different 062 BLE
 * pioneer kit. Then start both, and u will be able to see the BLE central
 * device (the device in which this firmware is loaded into) connect to the peripheral
 * device and after which the user can send the motor positions set by the user using
 * the capsense touch control or motion control of the central device over BLE
 *
 * Return:
 *  void
 *
 *******************************************************************************/
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    startUpInfo();

    Cy_GPIO_Set(GREEN_PORT,GREEN_NUM);
    Cy_GPIO_Clr(RED_PORT,RED_NUM);
    
    systemInputMode = xEventGroupCreate();
    xEventGroupSetBits(systemInputMode,MODE_CAPSENSE);
    
    setvbuf(stdin,0,_IONBF,0);
    
    /* BLE Central Task for communicating motor position to BLE peripheral*/
    xTaskCreate(ble_task," BLE CENTRAL TASK",BLE_TASK_STACK_SIZE,0,BLE_TASK_PRIORITY,0);
    
    /*UART Task for relative motor positioning*/
    xTaskCreate(uart_task," UART TASK",UART_TASK_STACK_SIZE,0,UART_TASK_PRIORITY,0);
    
    /* Capasense task for absolute motor positioning*/
    xTaskCreate(capSense_task," CAPSENSE TASK",CAPSENSE_TASK_STACK_SIZE,0,CAPSENSE_TASK_PRIORITY,0);
    
    /* Motion task for absolute motor positioning*/
    xTaskCreate(motion_task," MOTION TASK",MOTION_TASK_STACK_SIZE,0,MOTION_TASK_PRIORITY,0);

    /*Start the task scheduler */
    vTaskStartScheduler();
    
    for(;;);
}


void startUpInfo()
{
    const char build_date[] = __DATE__;
    const char build_time[] = __TIME__;
    
    UART_Start();
    CyDelay(10);
    serialPrint("\x1b[2J\x1b[;H");
    
    serialPrintf("BUILD DATE : %s",build_date);
    serialPrintf("BUILD TIME : %s",build_time);
    char pjtName[50];
    sprintf(pjtName,"======== %s v%d.%d.%d ========",PROJECT_NAME,MAJOR_VERSION,MINOR_VERSION,PATCH_VERSION); 
   
    seralPrinter("[ UART ] : ");
    for(int i = 0; pjtName[i] ; i++)
    seralPrinter("=");
    seralPrinter("\r\n");
    
    serialPrint(pjtName);
    
    seralPrinter("[ UART ] : ");
    for(int i = 0; pjtName[i] ; i++)
    seralPrinter("=");
    seralPrinter("\r\n");
    
}

/* [] END OF FILE */
