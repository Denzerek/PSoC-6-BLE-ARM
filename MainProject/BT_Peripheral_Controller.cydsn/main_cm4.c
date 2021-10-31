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
#include "uart_task.h"
#include "pwm_task.h"
#include "common.h"
#include "motor_task.h"
#include "ezI2C_task.h"
#include "event_groups.h"
#include "capsense_task.h"
#include "servo_slave_i2c_task.h"
#include "ble_task.h"

  
QueueHandle_t pwmQueue;
QueueHandle_t servoControlQueue;
EventGroupHandle_t pwmEventGroup;



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
   
    serialPrinter("[ UART ] : ");
    for(int i = 0; pjtName[i] ; i++)
    serialPrinter("=");
    serialPrinter("\r\n");
    
    serialPrint(pjtName);
    
    serialPrinter("[ UART ] : ");
    for(int i = 0; pjtName[i] ; i++)
    serialPrinter("=");
    serialPrinter("\r\n");
    
}


int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    startUpInfo();
    
    pwmQueue = xQueueCreate(4,sizeof(PWM_Message_t));
    servoControlQueue = xQueueCreate(4,sizeof(PWM_Message_t));
    
    pwmEventGroup = xEventGroupCreate(); 
    
    /* UART task for debug messages and UART control of motor position*/
    xTaskCreate(UartTask,"UART TASK",UART_TASK_STACK_SIZE,0,UART_TASK_PRIORITY,0);
    
    /* PWM Motor task that runs continuously to keep track of motor PWM*/
    xTaskCreate(motorTask,"MOTOR TASK",MOTOR_TASK_STACK_SIZE,0,MOTOR_TASK_PRIORITY,0);
    
    /* EZ I2C task for motor PWM monitoring over BCP*/
    xTaskCreate(ezI2CTask,"EZ I2C TASK",EZI2C_TASK_STACK_SIZE,0,EZI2C_TASK_PRIORITY,0);
    
    /* Capsense task that monitors onboard capsense slider and buttons*/
    xTaskCreate(capsenseTask,"CAPSENSE TASK",CAPSENSE_TASK_STACK_SIZE,0,CAPSENSE_TASK_PRIORITY,0);
    
    /* Slave communication task handling i2c transfer of commands to Arduino slave*/
    xTaskCreate(servo_slave_i2c_task,"ARDUINO COMM TASK",ARDUINO_COMM_TASK_STACK_SIZE,0,ARDUINO_COMM_TASK_PRIORITY,0);
    
    /* PWM task that runs continuously*/
    xTaskCreate(pwmTask,"PWM TASK",PWM_TASK_STACK_SIZE,0,PWM_TASK_PRIORITY,0);
    
    /* Ble task handling communication with CENTRAL for reception of motor positions*/
    xTaskCreate(bleTask,"BLE TASK",BLE_TASK_STACK_SIZE,0,BLE_TASK_PRIORITY,0);
    
    /* Start the Scheduler*/
    vTaskStartScheduler();
    
    for(;;)
    {
    }
    
}

/* [] END OF FILE */
