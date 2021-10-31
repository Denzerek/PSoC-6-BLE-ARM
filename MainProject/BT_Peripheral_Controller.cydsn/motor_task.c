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

#include "motor_task.h"

//Range of pulses for servo motor in uS
#define MIN_US  1000
#define MAX_US  2000

//Parameters of PWM must be same as schematic
#define PWM_CLK         4000000
#define PWM_DIV         4   
#define US_PER_SEC      1000000
#define PWMTICK_PER_US  (PWM_CLK/PWM_DIV/US_PER_SEC)


//Turn a percent (0--->100) to a pulse width in microseconds
static int inline percentToPulse(int percent)
{
    int pulse;
    pulse = percent * (MAX_US - MIN_US ) / (100 - 0) + MIN_US ;
    return pulse;
}

static int inline pulseToPercent(int pulse)
{
    int percent = 0;
    percent = pulse * (100 - 0) / (MAX_US - MIN_US) - 100;
    return percent;
}

//Turn a PWM compare value into pulse width in us
static int inline compareToPulse(int compare)
{
    int pulse;
    pulse = compare / PWMTICK_PER_US;
    return pulse;
}
//Turn a pulse width in us to a PWM compare value
static int inline pulseToCompare(int pulse)
{
    int compare;
    compare = pulse * PWMTICK_PER_US;
    return compare;
}

//Turn pwm compare value into percent
int compareToPercent(int compare)
{
    int pulse;
    int percent;
    pulse = compareToPulse(compare);
    percent = pulseToPercent(pulse);
    return percent;
}


int getMotorPercent(motors_t motors)
{
    int compare = Cy_TCPWM_PWM_GetCompare0(
        (motors == M1)?PWM_1_HW:PWM_2_HW,
        (motors == M1)?PWM_1_CNT_NUM:PWM_2_CNT_NUM);
    
        return compareToPercent(compare);
        
}
//Turn percent into compare value
static int inline percentToCompare(int percent)
{
    int pulse;
    int compare;
    pulse = percentToPulse(percent);
    compare = pulseToCompare(pulse);
    return compare;
}

void motorTask(void* arg)
{
    (void )arg;
    PWM_Message_t pwmMessage;
    TCPWM_Type *hw   = NULL;
    int cntrNum = 0;
    int compareTmp = 0;
    int percentTmp = 0;
    PWM_1_Start();
    PWM_2_Start();
    PWM_4_Start();
    PWM_3_Start();
    motorPrint("Motor Task Started ...");
    
    while(1)
    {
        //wait for someone to ask for the motors to change
        xQueueReceive(pwmQueue,&pwmMessage,portMAX_DELAY);
        
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
		
		motorPrintf("Motor %d : %d %%",pwmMessage.motor,percentTmp);
        
        xQueueSend(servoControlQueue,&pwmMessage,0);
        //Change the PWM of motor
        Cy_TCPWM_PWM_SetCompare0(hw,cntrNum,percentToCompare(percentTmp));
        xEventGroupSetBits(pwmEventGroup,PWM_EVENT_ALL);
    }
}


/* [] END OF FILE */
