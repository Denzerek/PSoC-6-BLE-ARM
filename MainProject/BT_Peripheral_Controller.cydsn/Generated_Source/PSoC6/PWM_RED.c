/*******************************************************************************
* File Name: PWM_RED.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the PWM_RED
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_RED.h"

/** Indicates whether or not the PWM_RED has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  PWM_RED_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the PWM_RED_Start() routine.
*/
uint8_t PWM_RED_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated PWM_RED_Init() function.
*/ 
cy_stc_tcpwm_pwm_config_t const PWM_RED_config =
{
    .pwmMode = 4UL,
    .clockPrescaler = 2UL,
    .pwmAlignment = 0UL,
    .deadTimeClocks = 0UL,
    .runMode = 0UL,
    .period0 = 100UL,
    .period1 = 32768UL,
    .enablePeriodSwap = false,
    .compare0 = 0UL,
    .compare1 = 16384UL,
    .enableCompareSwap = false,
    .interruptSources = 0UL,
    .invertPWMOut = 0UL,
    .invertPWMOutN = 0UL,
    .killMode = 2UL,
    .swapInputMode = 3UL,
    .swapInput = CY_TCPWM_INPUT_CREATOR,
    .reloadInputMode = 3UL,
    .reloadInput = CY_TCPWM_INPUT_CREATOR,
    .startInputMode = 3UL,
    .startInput = CY_TCPWM_INPUT_CREATOR,
    .killInputMode = 3UL,
    .killInput = CY_TCPWM_INPUT_CREATOR,
    .countInputMode = 3UL,
    .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: PWM_RED_Start
****************************************************************************//**
*
*  Calls the PWM_RED_Init() when called the first time and enables 
*  the PWM_RED. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref PWM_RED_initVar
*
*******************************************************************************/
void PWM_RED_Start(void)
{
    if (0U == PWM_RED_initVar)
    {
        (void) Cy_TCPWM_PWM_Init(PWM_RED_HW, PWM_RED_CNT_NUM, &PWM_RED_config);

        PWM_RED_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(PWM_RED_HW, PWM_RED_CNT_MASK);
    
    #if (PWM_RED_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(PWM_RED_HW, PWM_RED_CNT_MASK);
    #endif /* (PWM_RED_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
