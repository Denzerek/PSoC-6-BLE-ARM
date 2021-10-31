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
#include "ble_task.h"

#define LED_ON  0
#define LED_OFF 1

motorToControl_t motorToControl[MOTORS_TO_CONTROL_MAX] = {
    {M1,CY_BLE_MOTOR_M1_CHAR_HANDLE,updateMotorsGatt},
    {M1,CY_BLE_MOTOR_M1_REL_CHAR_HANDLE,updateRelativeMotorPos},
    {M2,CY_BLE_MOTOR_M2_CHAR_HANDLE,updateMotorsGatt},
    {M2,CY_BLE_MOTOR_M2_REL_CHAR_HANDLE,updateRelativeMotorPos},
    {M3,CY_BLE_MOTOR_M3_CHAR_HANDLE,updateMotorsGatt},
    {M3,CY_BLE_MOTOR_M3_REL_CHAR_HANDLE,updateRelativeMotorPos},
    {M4,CY_BLE_MOTOR_M4_CHAR_HANDLE,updateMotorsGatt},
    {M4,CY_BLE_MOTOR_M4_REL_CHAR_HANDLE,updateRelativeMotorPos}
};

SemaphoreHandle_t bleSemaphore;

void updateRelativeMotorPos(motors_t motor,int8_t percent,uint8_t flags)
{
    (void)flags;
    PWM_Message_t myMessage;
    myMessage.motor = motor;
    myMessage.percent = percent;
    myMessage.changeType = POS_RELATIVE;
    ble_printf("Received relative change M%d percent %%%d",motor,percent);
    xQueueSend(pwmQueue,&myMessage,0);
}

void updateMotorsGatt(motors_t motor,int8_t percent,uint8_t flags)
{
    cy_stc_ble_gatt_handle_value_pair_t myHvp;
    
    if(percent < 0) percent = 0;
    if(percent > 100) percent = 100;
    
    switch(motor)
    {
        case M1:
        myHvp.attrHandle = CY_BLE_MOTOR_M1_CHAR_HANDLE;
        break;        
        case M2:
        myHvp.attrHandle = CY_BLE_MOTOR_M2_CHAR_HANDLE;
        break;
        case M3:
        myHvp.attrHandle = CY_BLE_MOTOR_M3_CHAR_HANDLE;
        break;        
        case M4:
        myHvp.attrHandle = CY_BLE_MOTOR_M4_CHAR_HANDLE;
        break;
    }
    
    myHvp.value.val = (uint8_t*) &percent;
    myHvp.value.actualLen = 1;
    myHvp.value.len = 1;
    
    if(flags == CY_BLE_GATT_DB_PEER_INITIATED)
    {
        Cy_BLE_GATTS_WriteAttributeValuePeer(&cy_ble_connHandle[0],&myHvp);
        PWM_Message_t myMessage;
        myMessage.motor = motor;
        myMessage.percent = percent;
        myMessage.changeType = POS_ABSOLUTE;
        xQueueSend(pwmQueue,&myMessage,0);
    }
    else
    {
        Cy_BLE_GATTS_WriteAttributeValueLocal(&myHvp);
        Cy_BLE_GATTS_SendNotification(&cy_ble_connHandle[0],&myHvp);
    }
}



void genericEventHandler(uint32_t event,void* eventParam)
{
    cy_stc_ble_gatts_write_cmd_req_param_t *writeRequestParam;
    switch(event)
    {
        case CY_BLE_EVT_STACK_ON:
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
        ble_print("Device Disconnected");
        Cy_GPIO_Write(LED9_PORT,LED9_NUM,LED_OFF);
        Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST,CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
        
        break;
        
        case CY_BLE_EVT_GATT_CONNECT_IND:
        ble_print("Device Connected");
        Cy_GPIO_Write(LED9_PORT,LED9_NUM,LED_ON);
    
        break;
        
        case CY_BLE_EVT_GATTS_WRITE_REQ:
        writeRequestParam = (cy_stc_ble_gatts_write_cmd_req_param_t*)eventParam;
        
        for(int i = 0;i < 8 ; i++)
        {
            if(motorToControl[i].BLECharacteristicHandle == writeRequestParam->handleValPair.attrHandle)
                motorToControl[i].callBackfn(motorToControl[i].motor,writeRequestParam->handleValPair.value.val[0],CY_BLE_GATT_DB_PEER_INITIATED);
        }
        
        if(CY_BLE_MOTOR_M1_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE == writeRequestParam->handleValPair.attrHandle ||
            CY_BLE_MOTOR_M2_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE == writeRequestParam->handleValPair.attrHandle||
            CY_BLE_MOTOR_M3_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE == writeRequestParam->handleValPair.attrHandle||
            CY_BLE_MOTOR_M4_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE == writeRequestParam->handleValPair.attrHandle )
        {
            cy_stc_ble_gatts_db_attr_val_info_t myWrite;
            myWrite.offset = 0;
            myWrite.flags = CY_BLE_GATT_DB_PEER_INITIATED;
            myWrite.connHandle = writeRequestParam->connHandle;
            myWrite.handleValuePair = writeRequestParam->handleValPair;
            
            Cy_BLE_GATTS_WriteAttributeValueCCCD(&myWrite);
            
            
        }
        Cy_BLE_GATTS_WriteRsp( writeRequestParam->connHandle);
        break;
        
    }
    
}

void bleInterruptNotify()
{
    BaseType_t xHigherPriorityTaskWoken; 
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(bleSemaphore,&xHigherPriorityTaskWoken);
    //This part does a context switch by calling the scheduler to go the task where the semaphore caused an unblock.
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    
}

void bleTask(void * arg)
{
    (void)arg;
    
    ble_print("BLE Task started");
    bleSemaphore = xSemaphoreCreateBinary();
    
    //register the generic handler
    Cy_BLE_Start(genericEventHandler);
    
    //process all ble initialization processes until the ble state is set to on
    while(Cy_BLE_GetState() != CY_BLE_STATE_ON)
    {
        Cy_BLE_ProcessEvents();
    }
    
    Cy_BLE_RegisterAppHostCallback(bleInterruptNotify);
    
    for(;;)
    {
        xSemaphoreTake(bleSemaphore,portMAX_DELAY);
        Cy_BLE_ProcessEvents();
        
        if(xEventGroupGetBits(pwmEventGroup) & PWM_EVENT_BLE)
        {
            xEventGroupClearBits(pwmEventGroup,PWM_EVENT_BLE);
            updateMotorsGatt(M1,getMotorPercent(M1),CY_BLE_GATT_DB_LOCALLY_INITIATED);
            updateMotorsGatt(M2,getMotorPercent(M2),CY_BLE_GATT_DB_LOCALLY_INITIATED);
            updateMotorsGatt(M3,getMotorPercent(M3),CY_BLE_GATT_DB_LOCALLY_INITIATED);
            updateMotorsGatt(M4,getMotorPercent(M4),CY_BLE_GATT_DB_LOCALLY_INITIATED);
            
        }
    }
    
}

/* [] END OF FILE */
