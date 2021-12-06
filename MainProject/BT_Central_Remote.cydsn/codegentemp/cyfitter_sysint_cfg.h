/*******************************************************************************
* File Name: cyfitter_sysint_cfg.h
* 
* PSoC Creator  4.3
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2019 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_SYSINT_CFG_H
#define INCLUDED_CYFITTER_SYSINT_CFG_H

#include "sysint/cy_sysint.h"

/* ARM CM0+ */
#if (((__CORTEX_M == 0) && (CY_CORE_ID == 0)))
    #define BLE_1_bless_isr__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t BLE_1_bless_isr_cfg;

#endif /* ((__CORTEX_M == 0) && (CY_CORE_ID == 0)) */

/* ARM CM4 */
#if (((__CORTEX_M == 4) && (CY_CORE_ID == 0)))
    #define I2C_1_SCB_IRQ__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t I2C_1_SCB_IRQ_cfg;

    #define UART_SCB_IRQ__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t UART_SCB_IRQ_cfg;

    #define CapSense_ISR__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t CapSense_ISR_cfg;

#endif /* ((__CORTEX_M == 4) && (CY_CORE_ID == 0)) */


#endif /* INCLUDED_CYFITTER_SYSINT_CFG_H */
