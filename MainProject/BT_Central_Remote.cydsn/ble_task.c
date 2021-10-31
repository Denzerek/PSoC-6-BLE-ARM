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

//#define BLE_PACKET_DEBUG_ENABLE
SemaphoreHandle_t bleSemaphore;

static uint8_t bleConnectionStatus = false;

motorToControl_t motorToControl[MOTORS_TO_CONTROL_MAX] = {
    {M1, POS_ABSOLUTE,CY_BLE_CUSTOMC_MOTOR_M1_CHAR_INDEX},
    {M1, POS_RELATIVE,CY_BLE_CUSTOMC_MOTOR_M1_REL_CHAR_INDEX},
    {M2, POS_ABSOLUTE,CY_BLE_CUSTOMC_MOTOR_M2_CHAR_INDEX},
    {M2, POS_RELATIVE,CY_BLE_CUSTOMC_MOTOR_M2_REL_CHAR_INDEX},
    {M3, POS_ABSOLUTE,CY_BLE_CUSTOMC_MOTOR_M3_CHAR_INDEX},
    {M3, POS_RELATIVE,CY_BLE_CUSTOMC_MOTOR_M3_REL_CHAR_INDEX},
    {M4, POS_ABSOLUTE,CY_BLE_CUSTOMC_MOTOR_M4_CHAR_INDEX},
    {M4, POS_RELATIVE,CY_BLE_CUSTOMC_MOTOR_M4_REL_CHAR_INDEX}
};

uint8_t bleConnectionState()
{
    return bleConnectionStatus;
}

void writeMotorPosition(motors_t motor,motor_change_t type,uint8_t percent)
{
    if(Cy_BLE_GetConnectionState(cy_ble_connHandle[0]) != CY_BLE_CONN_STATE_CLIENT_DISCOVERED)
    {
        ble_print("Not connected");
        return;
    }
    
    //ble_printf("Motor = %d\tType = %d\tpercent = %d",motor+1,type,percent);
    
    cy_stc_ble_gattc_write_req_t myVal;
      
    
    for(int i = 0; i < MOTORS_TO_CONTROL_MAX; i++)
    {
        if((motor == motorToControl[i].motor) && (type == motorToControl[i].type))
        {
            myVal.handleValPair.attrHandle = cy_ble_customCServ[CY_BLE_CUSTOMC_MOTOR_SERVICE_INDEX].customServChar[motorToControl[i].charecteristicIndex].customServCharHandle[0];
        }
        
    }
    
    myVal.handleValPair.value.len = 1;
    myVal.handleValPair.value.val = (uint8_t *)&percent;
    #ifdef BLE_PACKET_DEBUG_ENABLE
    ble_printf("Sent data %d",*(myVal.handleValPair.value.val));
    #endif
    myVal.connHandle = cy_ble_connHandle[0];
    
    uint32_t i = 0;
    //wait for the data transfer to complete
    while(Cy_BLE_GATTC_WriteCharacteristicValue(&myVal) != CY_BLE_SUCCESS)
    {
        Cy_BLE_ProcessEvents();
        i++;
        if(i > 0xFFFE)
        {
            ble_print("BLE GATTC write error");
            return;
        }
    }
}


typedef struct{
    char * name;
    uint8_t * serviceUUID;
    int name_len;
    uint8_t servUUID_len;
}advInfo_t;
 
advInfo_t currentAdvInfo;

void findAdvInfo(uint8_t*adv,uint8_t len)
{
    memset (&currentAdvInfo,0,sizeof(currentAdvInfo));
    
    for(uint8_t i = 0; i< len;)
    {
        switch(adv[i+1])
        {
            //Service ID to check for the service uuid
            case 0x07:
                currentAdvInfo.serviceUUID = &adv[i+2];
                currentAdvInfo.servUUID_len = adv[i]-1;
                break;
            
            //Peripheral advertiser name
            case 0x09:
                currentAdvInfo.name = (char*)&adv[i+2];                
                currentAdvInfo.name_len = adv[i]-1;
            break;
            default:
            break;
                
        }
        //if packet id does not match, then skip the whole packet by adding i with length
        i = i +  adv[i] + 1;
    }
}

void genericEventHandler(uint32_t event,void* eventParameter)
{
    switch(event)
    {
        case CY_BLE_EVT_STACK_ON:
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
        ble_print("Make sure the peripheral BLE device is on");
        ble_print("Only once connected to the peripheral the data aquisition will begin.");
            ble_print("Starting Scan");
            //Start scan operation
            Cy_BLE_GAPC_StartScan(CY_BLE_SCANNING_FAST,0);
            //turn off the led
            Cy_GPIO_Set(GREEN_PORT,GREEN_NUM);
            Cy_GPIO_Clr(RED_PORT,RED_NUM);
        break;
        case CY_BLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
            //Print out information about the device that was found
            ble_printer("\r");
            cy_stc_ble_gapc_adv_report_param_t *scanProgressParam = (cy_stc_ble_gapc_adv_report_param_t*) eventParameter;
            #ifdef BLE_PACKET_DEBUG_ENABLE
            printf("[ BLE ] : BD Addr = ");
            for(unsigned int i = 0; i < CY_BLE_BD_ADDR_SIZE;i++)
            {
                printf("%02X ",scanProgressParam->peerBdAddr[i]);
            }
            printf("\r\n");
            ble_printf("Length = %d",scanProgressParam->dataLen);
            #endif
            findAdvInfo(scanProgressParam->data,scanProgressParam->dataLen);
            
            if( (currentAdvInfo.servUUID_len > 0 )
                 && (memcmp(currentAdvInfo.serviceUUID,cy_ble_customCServ[CY_BLE_CUSTOMC_MOTOR_SERVICE_INDEX].uuid
                  ,currentAdvInfo.servUUID_len) == 0))
            {
                #ifdef BLE_PACKET_DEBUG_ENABLE
                ble_print("Found MOTOR Service ");
                #endif
                ble_printf(" Device %.*s",currentAdvInfo.name_len,currentAdvInfo.name);
                cy_stc_ble_bd_addr_t connectAddr;
                memcpy(&connectAddr.bdAddr[0],&scanProgressParam->peerBdAddr[0],CY_BLE_BD_ADDR_SIZE);
                connectAddr.type = scanProgressParam->peerAddrType;
                Cy_BLE_GAPC_ConnectDevice(&connectAddr,0);
                Cy_BLE_GAPC_StopScan();
            }
                
        break;
        case CY_BLE_EVT_GATT_DISCONNECT_IND:
            Cy_GPIO_Set(GREEN_PORT,GREEN_NUM);
            Cy_GPIO_Clr(RED_PORT,RED_NUM);
            bleConnectionStatus = false;
            ble_print("Disconnected");
        break;
        case CY_BLE_EVT_GATT_CONNECT_IND:
            Cy_GPIO_Clr(GREEN_PORT,GREEN_NUM);
            Cy_GPIO_Set(RED_PORT,RED_NUM);
            ble_print("Made a connection, starting service discovery");
            bleConnectionStatus = true;
            Cy_BLE_GATTC_StartDiscovery(cy_ble_connHandle[0]);
        break;
        
        case CY_BLE_EVT_GATTC_DISCOVERY_COMPLETE:
            ble_print("Discovery Complete");
        break;
            
        case CY_BLE_EVT_GATTC_ERROR_RSP:
            ble_print("GATTC Error Response");
        break;
            
        case CY_BLE_EVT_GATTC_WRITE_RSP:
    #ifdef BLE_PACKET_DEBUG_ENABLE
            ble_print("GATTC Write Succeeded");
    #endif
        break;
            
        default:
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
       
    }
    
}



/* [] END OF FILE */
