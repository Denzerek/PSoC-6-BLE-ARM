/*******************************************************************************
* File Name: Dimmer.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the Dimmer
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(Dimmer_CY_TCPWM_PWM_PDL_H)
#define Dimmer_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  Dimmer_initVar;
extern cy_stc_tcpwm_pwm_config_t const Dimmer_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void Dimmer_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t Dimmer_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void Dimmer_DeInit(void);
__STATIC_INLINE void Dimmer_Enable(void);
__STATIC_INLINE void Dimmer_Disable(void);
__STATIC_INLINE uint32_t Dimmer_GetStatus(void);
__STATIC_INLINE void Dimmer_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t Dimmer_GetCompare0(void);
__STATIC_INLINE void Dimmer_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t Dimmer_GetCompare1(void);
__STATIC_INLINE void Dimmer_EnableCompareSwap(bool enable);
__STATIC_INLINE void Dimmer_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t Dimmer_GetCounter(void);
__STATIC_INLINE void Dimmer_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t Dimmer_GetPeriod0(void);
__STATIC_INLINE void Dimmer_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t Dimmer_GetPeriod1(void);
__STATIC_INLINE void Dimmer_EnablePeriodSwap(bool enable);
__STATIC_INLINE void Dimmer_TriggerStart(void);
__STATIC_INLINE void Dimmer_TriggerReload(void);
__STATIC_INLINE void Dimmer_TriggerKill(void);
__STATIC_INLINE void Dimmer_TriggerSwap(void);
__STATIC_INLINE uint32_t Dimmer_GetInterruptStatus(void);
__STATIC_INLINE void Dimmer_ClearInterrupt(uint32_t source);
__STATIC_INLINE void Dimmer_SetInterrupt(uint32_t source);
__STATIC_INLINE void Dimmer_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t Dimmer_GetInterruptMask(void);
__STATIC_INLINE uint32_t Dimmer_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define Dimmer_HW                 (Dimmer_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define Dimmer_CNT_HW             (Dimmer_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define Dimmer_CNT_NUM            (Dimmer_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define Dimmer_CNT_MASK           (1UL << Dimmer_CNT_NUM)
/** @} group_macros */

#define Dimmer_INPUT_MODE_MASK    (0x3U)
#define Dimmer_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: Dimmer_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t Dimmer_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(Dimmer_HW, Dimmer_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: Dimmer_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(Dimmer_HW, Dimmer_CNT_NUM, &Dimmer_config);
}

/*******************************************************************************
* Function Name: Dimmer_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(Dimmer_HW, Dimmer_CNT_MASK);
}


/*******************************************************************************
* Function Name: Dimmer_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(Dimmer_HW, Dimmer_CNT_MASK);
}


/*******************************************************************************
* Function Name: Dimmer_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(Dimmer_HW, Dimmer_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: Dimmer_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(Dimmer_HW, Dimmer_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: Dimmer_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(Dimmer_HW, Dimmer_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: Dimmer_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(Dimmer_HW, Dimmer_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: Dimmer_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(Dimmer_HW, Dimmer_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: Dimmer_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(Dimmer_HW, Dimmer_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: Dimmer_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(Dimmer_HW, Dimmer_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: Dimmer_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(Dimmer_HW, Dimmer_CNT_MASK);
}


/*******************************************************************************
* Function Name: Dimmer_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(Dimmer_HW, Dimmer_CNT_MASK);
}


/*******************************************************************************
* Function Name: Dimmer_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(Dimmer_HW, Dimmer_CNT_MASK);
}


/*******************************************************************************
* Function Name: Dimmer_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(Dimmer_HW, Dimmer_CNT_MASK);
}


/*******************************************************************************
* Function Name: Dimmer_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(Dimmer_HW, Dimmer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: Dimmer_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(Dimmer_HW, Dimmer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: Dimmer_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void Dimmer_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(Dimmer_HW, Dimmer_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: Dimmer_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(Dimmer_HW, Dimmer_CNT_NUM));
}


/*******************************************************************************
* Function Name: Dimmer_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Dimmer_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(Dimmer_HW, Dimmer_CNT_NUM));
}

#endif /* Dimmer_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
