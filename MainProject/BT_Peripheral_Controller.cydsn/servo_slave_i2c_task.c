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
#include "servo_slave_i2c_task.h"

volatile static uint32_t i2cStatus = 0;

i2cEvents_s i2cEvents[I2C_MAX_EVENTS] = {
    {0x00080000UL,"MASTER ERROR EVENT"},
    {0x00020000UL,"MASTER WRITE COMPLETE EVENT"},
};

void i2cStatusDecode()
{
    for(int i = 0; i < I2C_MAX_EVENTS ; i++)
    {
        if(i2cEvents[i].i2cEvent & i2cStatus)
        {
            ard_print((char*)i2cEvents[i].i2cMessage);
        }
    }
}

void i2cCallback(uint32_t event)
{
   i2cStatus |= event;
}


static uint8_t prevPercent[5];
void servo_slave_i2c_task(void * arg)
{
    (void)arg;
    
    PWM_Message_t pwmMessage;
    TCPWM_Type *hw   = NULL;
    int cntrNum = 0;
    int compareTmp = 0;
    int percentTmp = 0;
    
   I2C_ARD_Start();
    ard_print("Comm to Arduino Servo Control Started");
    Cy_SCB_I2C_RegisterEventCallback(I2C_ARD_HW, i2cCallback, &I2C_ARD_context);
    
    
    while(1)
    {
        
        //wait for motor control to send the percentage change to arduino servo control
        xQueueReceive(servoControlQueue,&pwmMessage,portMAX_DELAY);
        
        
        //Identify which PWM to change
        switch(pwmMessage.motor)
        {
            case M1:
                hw = PWM_1_HW;
                cntrNum = PWM_1_CNT_NUM;
            break;
            case M2:
                hw = PWM_2_HW;
                cntrNum = PWM_2_CNT_NUM;
            break;
            case M3:
                hw = PWM_3_HW;
                cntrNum = PWM_3_CNT_NUM;
            break;
            case M4:
                hw = PWM_4_HW;
                cntrNum = PWM_4_CNT_NUM;
            break;
            default:
            break;
        }
        
        //Check if relative or absolute .. if relative, get current % 
        if(pwmMessage.changeType == POS_RELATIVE)
        {
            compareTmp = Cy_TCPWM_PWM_GetCompare0(hw,cntrNum);
            percentTmp = compareToPercent(compareTmp) + pwmMessage.percent;
            
            //Make sure % is not below 0 or above 100%
            if(percentTmp < 0)
            {
                percentTmp = 0;
            }
            if(percentTmp > 100)
            {
                percentTmp = 100;
            }
        }
        else
        {
            percentTmp = pwmMessage.percent;
        }
        ard_printf("Transmitting motor %d pwm %d ",pwmMessage.motor,percentTmp);
        if(prevPercent[pwmMessage.motor] != percentTmp) 
        {
            ardTransmitPWMPercent(pwmMessage.motor,percentTmp);
        }
        prevPercent[pwmMessage.motor] = percentTmp;
        
    }
}


void ardTransmitPWMPercent(motors_t motorNum,uint8_t percent)
{
    cy_stc_scb_i2c_master_xfer_config_t transfer;
    uint8_t writeBuffer[5];
    writeBuffer[0] = 0xC;   //Start header
    writeBuffer[1] = motorNum;     //motor number
    writeBuffer[2] = percent;   //data
    writeBuffer[3] = 0xD;   //End Header
    /* Configure write transaction */
    transfer.slaveAddress = 0x08U;
    transfer.buffer       = writeBuffer;
    transfer.bufferSize   = sizeof(writeBuffer);
    //transfer.xferPending  = true; /* Do not generate Stop condition at the end of transaction */
    transfer.xferPending  = false; /* Generate Stop condition at the end of transaction */
    i2cStatus = 0;
    /* Initiate write transaction.
    * The Start condition is generated to begin this transaction.
    */
    (void) Cy_SCB_I2C_MasterWrite(I2C_ARD_HW, &transfer, &I2C_ARD_context);
    /* Wait for transaction completion */
    while (0UL != (CY_SCB_I2C_MASTER_BUSY & Cy_SCB_I2C_MasterGetStatus(I2C_ARD_HW, &I2C_ARD_context)))
    { 
    }
    
    ard_printf("I2c master write operation complete %X ",i2cStatus);
    i2cStatusDecode();
    
}


/* [] END OF FILE */
