
/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "capsense_task.h"
#include "ble_task.h"



/*******************************************************************************
 * Function Name: CapSense Task
 ********************************************************************************
 * Summary:
 * Task handling the read of capsense touch positions on user finger touch of 
 * the same.
 *
 *******************************************************************************/
void capSense_task(void *arg)
{
    (void) arg;
    
    static uint8_t bleConnectionCounter ;
    motors_t currentMotor = M1;
    static uint8_t pressReleased = true;
    
    CapSense_Start();
    CapSense_ScanAllWidgets();
    
    cap_print("Capsense Task Started")
    
    for(;;)
    {
        if(!CapSense_IsBusy())
        {
            CapSense_ProcessAllWidgets();
            int pos;
            pos = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0_WDGT_ID);
            
            if(pos < 0xFFFF && xEventGroupGetBits(systemInputMode) == MODE_CAPSENSE)
            {
                //Make suer BLE is connected before updating characteristic with position data
                if(bleConnectionState())
                {
                    writeMotorPosition(currentMotor,POS_ABSOLUTE,pos);
                    cap_printf("Motor M%d : %%%d",currentMotor+1,pos);
                }
                else 
                {
                    if(bleConnectionCounter > 4)
                    {
                        cap_print("BLE Not Connected");
                        bleConnectionCounter = 0;
                    }
                    bleConnectionCounter++;
                }
            }
            
            /* Check if Button 0 has been touched*/
            if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID))
            {
                if(pressReleased)
                {
                    if(currentMotor < M_MAX - 1)
                    {
                        currentMotor++;
                        pressReleased = false;
                        cap_printf("Motor M%d selected",currentMotor+1);
                    }
                }
            }
            /* Check if Button 1 has been touched*/
            else if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID))
            {
                if(pressReleased)
                {
                    if(currentMotor > M1)
                    {
                        currentMotor--;
                        pressReleased = false;
                        cap_printf("Motor M%d selected",currentMotor+1);
                    }
                }
            }
            else
            {
                pressReleased = true;
            }
            
            /* Limit check on motor selection */
            if(currentMotor >= M_MAX) currentMotor = M_MAX - 1;
            if(currentMotor < M1) currentMotor = M1;
            
            CapSense_UpdateAllBaselines();
            CapSense_ScanAllWidgets();
        }
        else
        {
            vTaskDelay(50);
        }
    }
}
/* [] END OF FILE */
