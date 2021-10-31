/***************************************************************************//**
* \file CY_BLE_custom_config.c
* \version 2.20
* 
* \brief
*  This file contains the source code of initialization of the config structure for
*  the Custom Service.
*
********************************************************************************
* \copyright
* Copyright 2017-2019, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ble/cy_ble_custom.h"

#if (CY_BLE_MODE_PROFILE && defined(CY_BLE_CUSTOM))
#ifdef CY_BLE_CUSTOM_SERVER
/* If any Custom Service with custom characteristics is defined in the
* customizer's GUI, their handles will be present in this array.
*/
/* This array contains attribute handles for the defined Custom Services and their characteristics and descriptors.
   The array index definitions are located in the BLE_custom.h file. */


#endif /* (CY_BLE_CUSTOM_SERVER) */

#ifdef CY_BLE_CUSTOM_CLIENT

static const cy_stc_ble_uuid128_t cy_ble_customUuid128[] = {
    /* MOTOR */
    { {0x52u, 0x08u, 0x46u, 0x60u, 0xF7u, 0xCDu, 0x05u, 0xB8u, 0xA4u, 0x42u, 0xA1u, 0x62u, 0x09u, 0x9Fu, 0x89u, 0x02u} },
    /* M1 */
    { {0x3Fu, 0xDAu, 0x0Fu, 0x3Eu, 0x44u, 0x65u, 0xC5u, 0xA4u, 0x67u, 0x48u, 0x7Du, 0xAAu, 0x4Bu, 0x87u, 0xCFu, 0xEBu} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
    /* M2 */
    { {0x7Fu, 0xC5u, 0x4Du, 0x39u, 0x68u, 0x7Eu, 0xB4u, 0xA8u, 0x7Bu, 0x4Au, 0x48u, 0x75u, 0xA5u, 0xC2u, 0x12u, 0x34u} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
    /* M1_REL */
    { {0x37u, 0x0Du, 0x2Cu, 0x36u, 0xEEu, 0x90u, 0xD7u, 0x8Au, 0x4Bu, 0x44u, 0xC8u, 0xD1u, 0x11u, 0x32u, 0x32u, 0xADu} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
    /* M2_REL */
    { {0x36u, 0xACu, 0x71u, 0x39u, 0x21u, 0x56u, 0x80u, 0xA8u, 0x91u, 0x41u, 0x28u, 0xAFu, 0xFDu, 0x8Du, 0x13u, 0xBAu} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
    /* M3 */
    { {0xAFu, 0x14u, 0xC3u, 0x7Fu, 0xC1u, 0x01u, 0xE9u, 0xBAu, 0x91u, 0x40u, 0xB9u, 0x20u, 0x20u, 0xC8u, 0x58u, 0xDEu} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
    /* M4 */
    { {0x1Cu, 0x2Au, 0x80u, 0x59u, 0x6Au, 0xA0u, 0xFFu, 0x8Au, 0x66u, 0x4Du, 0x5Bu, 0xE1u, 0x25u, 0x54u, 0x17u, 0x15u} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
    /* M3_REL */
    { {0x25u, 0x9Au, 0x70u, 0x12u, 0x46u, 0x8Cu, 0x42u, 0xB9u, 0xDEu, 0x46u, 0xF1u, 0x43u, 0x7Cu, 0x35u, 0xD2u, 0xBCu} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
    /* M4_REL */
    { {0xA4u, 0xB8u, 0x24u, 0x5Bu, 0x50u, 0x46u, 0xFEu, 0x9Au, 0xC0u, 0x41u, 0xE4u, 0x84u, 0x24u, 0x7Cu, 0x7Du, 0x50u} },
    /* Custom Descriptor */
    { {0xA3u, 0xCEu, 0xE3u, 0x69u, 0xDBu, 0xF9u, 0xB1u, 0x98u, 0xC0u, 0x49u, 0x84u, 0x43u, 0x46u, 0x99u, 0xE6u, 0x1Au} },
};

static const cy_ble_uuid16_t cy_ble_customUuid16[] = {
    /* Client Characteristic Configuration */
    0x2902u,
    /* Client Characteristic Configuration */
    0x2902u,
    /* Client Characteristic Configuration */
    0x2902u,
    /* Client Characteristic Configuration */
    0x2902u,
};

static cy_stc_ble_customc_desc_t cy_ble_customCDesc[0x0Cu] = {

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[2], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Client Characteristic Configuration */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_ble_uuid16_t *) &cy_ble_customUuid16[0], /* 16-bit UUID */ 
        .uuidFormat = 0x01u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[4], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Client Characteristic Configuration */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_ble_uuid16_t *) &cy_ble_customUuid16[1], /* 16-bit UUID */ 
        .uuidFormat = 0x01u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[6], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[8], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[10], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Client Characteristic Configuration */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_ble_uuid16_t *) &cy_ble_customUuid16[2], /* 16-bit UUID */ 
        .uuidFormat = 0x01u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[12], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Client Characteristic Configuration */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_ble_uuid16_t *) &cy_ble_customUuid16[3], /* 16-bit UUID */ 
        .uuidFormat = 0x01u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[14], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },

    /* Custom Descriptor */
    {
        .descHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Descriptor handle */ 
        .uuid       = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[16], /* 128-bit UUID */ 
        .uuidFormat = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
    },
};

static cy_stc_ble_customc_char_t cy_ble_customCChar[0x08u] = {

    /* M1 */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[1], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x02u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[0], /* Characteristic Descriptors */ 
    },

    /* M2 */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[3], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x02u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[2], /* Characteristic Descriptors */ 
    },

    /* M1_REL */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[5], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x01u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[4], /* Characteristic Descriptors */ 
    },

    /* M2_REL */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[7], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x01u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[5], /* Characteristic Descriptors */ 
    },

    /* M3 */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[9], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x02u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[6], /* Characteristic Descriptors */ 
    },

    /* M4 */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[11], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x02u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[8], /* Characteristic Descriptors */ 
    },

    /* M3_REL */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[13], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x01u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[10], /* Characteristic Descriptors */ 
    },

    /* M4_REL */
    {
        .customServCharHandle    = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic handle */ 
        .customServCharEndHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Characteristic end handle */ 
        .uuid                    = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[15], /* 128-bit UUID */ 
        .uuidFormat              = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .properties              = {0x00u}, /* Characteristic properties */ 
        .descCount               = 0x01u, /* Number of descriptors */ 
        .customServCharDesc      = &cy_ble_customCDesc[11], /* Characteristic Descriptors */ 
    },
};

cy_stc_ble_customc_t cy_ble_customCServ[CY_BLE_CUSTOMC_SERVICE_COUNT] = {

    /* MOTOR */
    {
        .customServHandle = {CY_BLE_GATT_INVALID_ATTR_HANDLE_VALUE}, /* Custom Service handle */ 
        .uuid             = (const cy_stc_ble_uuid128_t *) &cy_ble_customUuid128[0], /* 128-bit UUID */ 
        .uuidFormat       = 0x02u, /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */ 
        .charCount        = 0x08u, /* Number of characteristics */ 
        .customServChar   = &cy_ble_customCChar[0], /* Custom Service Characteristics */ 
    },
};


#endif /* (CY_BLE_CUSTOM_CLIENT) */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Custom Services. */
cy_stc_ble_custom_config_t cy_ble_customConfig =
{
    /* Custom Services GATT DB handles structure */
    #ifdef CY_BLE_CUSTOM_SERVER
    .customs      = cy_ble_customs,
    #endif /* (CY_BLE_CUSTOM_SERVER) */

    /* Custom Service handle */
    #ifdef CY_BLE_CUSTOM_CLIENT
    .customc  = cy_ble_customCServ,
    #endif /* (CY_BLE_CUSTOM_CLIENT) */
};

/** @} group_globals */
#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_CUSTOM)) */

/* [] END OF FILE */
