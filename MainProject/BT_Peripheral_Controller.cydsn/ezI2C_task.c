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
#include "ezI2C_task.h"
#include "motor_task.h"

void ezI2CTask(void * arg)
{
    (void) arg;
    uint8_t motorPercent[2];
    
    EZI2C_Start();
    ezi2cPrint("EZI2C Task Started ...");
    CyDelay(1);
    
    EZI2C_SetBuffer1(motorPercent,sizeof(motorPercent),0);
    
    while(1)
    {
        motorPercent[0] = getMotorPercent(M1);
        motorPercent[1] = getMotorPercent(M2);
        xEventGroupWaitBits(pwmEventGroup,  //.which event group
                            PWM_EVENT_I2C,  //which event to wait for
                            pdTRUE,         //clear the bit after it is set
                            pdFALSE,        //only wait for the i2c bit
                            portMAX_DELAY); //wait indefinitely
    }
}
/* [] END OF FILE */
