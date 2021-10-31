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

static SemaphoreHandle_t uartSemaphore;
static void UARTIsr()
{
    // Disable and clear the interrupt
    Cy_SCB_SetRxInterruptMask(UART_HW,0);
    Cy_SCB_ClearRxInterrupt(UART_HW, CY_SCB_RX_INTR_NOT_EMPTY);
    NVIC_ClearPendingIRQ((IRQn_Type)UART_SCB_IRQ_cfg.intrSrc);
    
    //If the semaphore causes a task switch , you should yeild to that task
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(uartSemaphore,&xHigherPriorityTaskWoken);
     
    if(xHigherPriorityTaskWoken != pdFALSE)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}


void UartTask(void * arg)
{
    (void) arg;
    setvbuf(stdin,NULL,_IONBF,0);
    
    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    serialPrint("UART TASK Started ... ");
    serialPrint("Press ? to ensure reception operation");
    
    CyDelay(1);
    
    uartSemaphore = xSemaphoreCreateBinary();
    
    PWM_Message_t pwmMessage;
    
    //configure the interrupt handler
    (void) Cy_SysInt_Init(&UART_SCB_IRQ_cfg,&UARTIsr);
    
    //enable the NVIC engine for uart
    NVIC_EnableIRQ(UART_SCB_IRQ_cfg.intrSrc);
    
    //enable the Receiver not empty interrupt
    Cy_SCB_SetRxInterruptMask(UART_HW,CY_SCB_RX_INTR_NOT_EMPTY);
    
    while(1)
    {
        xSemaphoreTake(uartSemaphore,portMAX_DELAY);
        
        //check if there are data in the uart rx buffer
        while(Cy_SCB_UART_GetNumInRxFifo(UART_HW))
        {
            //get character by character from the uart rx buffer
            char c = getchar();
            switch(c)
            {
                case 'r' :
                serialPrint("Reset");
                Cy_TCPWM_PWM_SetCompare0(PWM_1_HW,PWM_1_CNT_NUM,0);                
                Cy_TCPWM_PWM_SetCompare0(PWM_2_HW,PWM_2_CNT_NUM,0);
                break;
                case 'q' :
                serialPrint("0 Degree");
                Cy_TCPWM_PWM_SetCompare0(PWM_1_HW,PWM_1_CNT_NUM,1000);                
                Cy_TCPWM_PWM_SetCompare0(PWM_2_HW,PWM_2_CNT_NUM,1000);
                break;
                case 'w' :
                serialPrint("90 Degree");               
                Cy_TCPWM_PWM_SetCompare0(PWM_1_HW,PWM_1_CNT_NUM,1500);
                Cy_TCPWM_PWM_SetCompare0(PWM_2_HW,PWM_2_CNT_NUM,1500);
                break;
                case 'e' :
                serialPrint("180 degree");
                Cy_TCPWM_PWM_SetCompare0(PWM_1_HW,PWM_1_CNT_NUM,2000);
                Cy_TCPWM_PWM_SetCompare0(PWM_2_HW,PWM_2_CNT_NUM,2000);
                break;
                case 'p':
                    pwmMessage.motor = M1; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = 10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break;
                case 'o':
                    pwmMessage.motor = M1; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = -10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break; 
                case 'l':
                    pwmMessage.motor = M2; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = 10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break;
                case 'k':
                    pwmMessage.motor = M2; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = -10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break;
                case 'm':
                    pwmMessage.motor = M3; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = 10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break;
                case 'n':
                    pwmMessage.motor = M3; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = -10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break; 
                case '.':
                    pwmMessage.motor = M4; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = 10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break;
                case ',':
                    pwmMessage.motor = M4; 
                    pwmMessage.changeType = POS_RELATIVE;
                    pwmMessage.percent = -10;
                    xQueueSend(pwmQueue,&pwmMessage,0);
                break;
                
                case 's':
                    serialPrintf("Motor1 = %%%d\tMotor2 = %%%d",getMotorPercent(M1),getMotorPercent(M2));
                break;
                case '?':
                serialPrint("?\tPrint Help");
                break;
            }
        }
        
        //Once you have processed the rx fifo , re enable the interrupt
        Cy_SCB_SetRxInterruptMask(UART_HW,CY_SCB_RX_INTR_NOT_EMPTY);
    }
    
    
}
    

/* [] END OF FILE */
