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

#include "motion_task.h"
#include "bmi160.h"
#include "ble_task.h"

static struct bmi160_dev bmi160Dev;


typedef struct{
    uint32_t i2cEvent;
    char* i2cMessage;
}i2cEvents_s;

volatile static uint32_t i2cStatus = 0;

i2cEvents_s i2cEvents[] = {
    {CY_SCB_I2C_MASTER_MANUAL_ABORT_START,"CY_SCB_I2C_MASTER_MANUAL_ABORT_START"},
    {CY_SCB_I2C_MASTER_MANUAL_BUS_ERR,"CY_SCB_I2C_MASTER_MANUAL_BUS_ERR"},
    {CY_SCB_I2C_MASTER_MANUAL_ARB_LOST,"CY_SCB_I2C_MASTER_MANUAL_ARB_LOST"},
    {CY_SCB_I2C_MASTER_MANUAL_NAK,"CY_SCB_I2C_MASTER_MANUAL_NAK"},
    {CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK,"CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK"},
    {CY_SCB_I2C_MASTER_MANUAL_TIMEOUT,"CY_SCB_I2C_MASTER_MANUAL_TIMEOUT"},
    {CY_SCB_I2C_MASTER_NOT_READY,"CY_SCB_I2C_MASTER_NOT_READY"},
    {CY_SCB_I2C_BAD_PARAM,"CY_SCB_I2C_BAD_PARAM"},
    {0x00,"NONE"},
};

void i2cStatusDecode( cy_en_scb_i2c_status_t i2cStatus)
{
    for(int i = 0; i2cEvents[i].i2cEvent != 0x00 ; i++)
    {
        if((i2cEvents[i].i2cEvent & i2cStatus)  == i2cEvents[i].i2cEvent)
        {
            serialPrint(i2cEvents[i].i2cMessage);
        }
    }
}

#define I2C_TIMEOUT     20

static int8_t BMI160BurstWrite(uint8_t devAddr,uint8_t regAddr,uint8_t *data,uint16_t len)
{
    cy_en_scb_i2c_status_t retStatus;
    retStatus = Cy_SCB_I2C_MasterSendStart(I2C_1_HW,devAddr,CY_SCB_I2C_WRITE_XFER,0,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    
    retStatus = Cy_SCB_I2C_MasterWriteByte(I2C_1_HW,regAddr,I2C_TIMEOUT,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    
    for(int i =0;i<len;i++)
    {
        retStatus = Cy_SCB_I2C_MasterWriteByte(I2C_1_HW,data[i],I2C_TIMEOUT,&I2C_1_context);
        if(retStatus)i2cStatusDecode(retStatus);
    }
    retStatus = Cy_SCB_I2C_MasterSendStop(I2C_1_HW,I2C_TIMEOUT,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    return 0;
}


static int8_t BMI160BurstRead(uint8_t devAddr,uint8_t regAddr,uint8_t *data,uint16_t len)
{
    cy_en_scb_i2c_status_t retStatus;
    retStatus = Cy_SCB_I2C_MasterSendStart(I2C_1_HW,devAddr,CY_SCB_I2C_WRITE_XFER,I2C_TIMEOUT,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    
    retStatus = Cy_SCB_I2C_MasterWriteByte(I2C_1_HW,regAddr,I2C_TIMEOUT,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    
    retStatus = Cy_SCB_I2C_MasterSendReStart(I2C_1_HW,devAddr,CY_SCB_I2C_READ_XFER,I2C_TIMEOUT,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    
    for(int i = 0; i < len - 1; i++)
    {
        retStatus = Cy_SCB_I2C_MasterReadByte(I2C_1_HW,CY_SCB_I2C_ACK,&data[i],I2C_TIMEOUT,&I2C_1_context);
        if(retStatus)i2cStatusDecode(retStatus);
    }
    retStatus = Cy_SCB_I2C_MasterReadByte(I2C_1_HW,CY_SCB_I2C_NAK,&data[len-1],I2C_TIMEOUT,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    
    retStatus = Cy_SCB_I2C_MasterSendStop(I2C_1_HW,I2C_TIMEOUT,&I2C_1_context);
    if(retStatus)i2cStatusDecode(retStatus);
    
    return 0;
}

static void bmi160Init(void)
{
    vTaskDelay(200);
    
    bmi160Dev.read = (bmi160_read_fptr_t)BMI160BurstRead;
    bmi160Dev.write = (bmi160_write_fptr_t)BMI160BurstWrite;
    bmi160Dev.delay_ms = (bmi160_delay_fptr_t) vTaskDelay;
    bmi160Dev.id = BMI160_I2C_ADDR;
    
    bmi160_init(&bmi160Dev); //initialize the device
    
    bmi160Dev.gyro_cfg.odr = BMI160_GYRO_ODR_800HZ;
    bmi160Dev.gyro_cfg.range = BMI160_GYRO_RANGE_125_DPS;
    bmi160Dev.gyro_cfg.bw = BMI160_GYRO_BW_OSR4_MODE;
    
    bmi160Dev.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;
    
    bmi160Dev.accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
    bmi160Dev.accel_cfg.range = BMI160_ACCEL_RANGE_2G;
    bmi160Dev.accel_cfg.bw = BMI160_ACCEL_BW_OSR4_AVG1;
    bmi160Dev.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;
    
    bmi160_set_sens_conf(&bmi160Dev);
    bmi160Dev.delay_ms(50);   
    
}

#define MAXACCEL        32768*2

void motionTask(void *arg)
{
    (void) arg;
    static uint8_t bleConnectionCounter;
    motion_print("Starting Motion TASK");
    I2C_1_Start();
    
    TickType_t lastMovement = 0;
    
    bmi160Init();
    struct bmi160_sensor_data acc;
    
    float gx,gy,gz;
    double m1 = 50 ,m2 = 50 ,m1Prev = 0,m2Prev = 0;
    lastMovement = xTaskGetTickCount() + 5000;
    
    while(1)
    {
        
        if(!bleConnectionState())
        {
            if(bleConnectionCounter > 100)
            {
                motion_print("BLE Not Connected");
                bleConnectionCounter = 0;
            }
            bleConnectionCounter++;
            vTaskDelay(30);
            continue;
        }
        
        bmi160_get_sensor_data(BMI160_ACCEL_ONLY,&acc,NULL,&bmi160Dev);
        
        gx = (float)acc.x/MAXACCEL;
        gy = (float)acc.y/MAXACCEL;
        gz = (float)acc.z/MAXACCEL;
        
        if(gx > 1.0) gx = 1.0;
        if(gx < -1.0) gx = -1.0;
        if(gy > 1.0) gy = 1.0;
        if(gy < -1.0) gy = -1.0;
        
        //convert the accel values to %
        
        m1 = acos(gy) * 360 / (2*3.14*1.8);
        m2 = acos(gx) * 360 / (2*3.14*1.8);
        
        //check if the change is greater than 3% 
        if(fabs(m1-50.0)>3.0 || fabs(m2-50.0)>3.0)
            lastMovement = xTaskGetTickCount();
            
        //switch to capsense if the last motion movement is greater than 1 second
        if((xTaskGetTickCount() - lastMovement) > 1000)
        {
            xEventGroupSetBits(systemInputMode,MODE_CAPSENSE);
            xEventGroupClearBits(systemInputMode,MODE_MOTION);
            Cy_GPIO_Write(LED8_PORT,LED8_NUM,0);
            
        }
        else
        {
            xEventGroupSetBits(systemInputMode,MODE_MOTION);
            xEventGroupClearBits(systemInputMode,MODE_CAPSENSE);
            Cy_GPIO_Write(LED8_PORT,LED8_NUM,1);
        }
        
        if(xEventGroupGetBits(systemInputMode) == MODE_MOTION)
        {
            if(m1Prev != m1)
            {
                if(m1 > 100 ) m1 = 100;if(m1<0)m1 = 0;
                
                //if(bleConnectionState())
                writeMotorPosition(M1,POS_ABSOLUTE,(int)m1);
                m1Prev = m1;
                //serialPrintf("M1 %%%d\tM2 %%%d",m1,m2);
            }
            if(m2Prev != m2)
            {
                if(m2 > 100 ) m2 = 100;if(m2<0)m2 = 0;
                
                //if(bleConnectionState())
                writeMotorPosition(M2,POS_ABSOLUTE,(int)m2);
                m2Prev = m2;
            }
            
                motion_printf("M1 %%%d\tM2 %%%d",(int)m1,(int)m2);
                
            xEventGroupSetBits(systemInputMode,MODE_CAPSENSE);
                vTaskDelay(50);
        }
        else
        {
            vTaskDelay(50);
        }
        
    }
}

/* [] END OF FILE */
