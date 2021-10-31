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

#include "pwm_task.h"

void pwmTask(void * arg)
{
    (void) arg;
    
    uint8_t compareVal;
    
    /* Start the PWM operation */
    PWM_RED_Start();
    pwm_print("Heart Beat LED Started ...");
    LEDBlink_Start();
    Dimmer_Start();
    pwm_print("Kill Switch LEDs Started ...");
    Cy_TCPWM_PWM_SetCompare0(Dimmer_HW,Dimmer_CNT_NUM,95);
    
    
    
    for(;;)
    {
        /* Set the compare value with modified one*/
        Cy_TCPWM_PWM_SetCompare0(PWM_RED_HW,PWM_RED_CNT_NUM,compareVal++);
        
        /* Update the compare value*/
        compareVal  = (compareVal + 1) % 100;
        
        vTaskDelay(10);
    }
    
}

/* [] END OF FILE */
