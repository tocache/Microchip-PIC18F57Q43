/**
 * I2C Generated Driver Event Header File
 *
 * @file i2c_host_event_types.h
 *
 * @defgroup i2c_host_events I2C_HOST_EVENTS
 *
 * @brief This header file provides the helper structures for the I2C driver.
 *
 * @version I2C Driver Version 2.1.4
 * 
 * @version I2C Package Version 6.2.0
 */

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef I2C_EVENT_TYPES_H
#define	I2C_EVENT_TYPES_H

#include "i2c_host_types.h"

/**
 * @ingroup i2c_host_events
 * @struct i2c_host_event_status_t
 * @brief Defines information related to an I2C event status.
 */
typedef struct
{
    bool busy; /**< Software busy flag*/
    uint16_t address; /**< Pointer to write buffer*/
    uint8_t *writePtr; /**< Pointer to write buffer*/
    size_t writeLength; /**< Write buffer length*/
    uint8_t *readPtr; /**< Pointer to read buffer*/
    size_t readLength; /**< Read buffer length*/
    bool switchToRead; /**< Switch i2c write to read mode*/
    i2c_host_error_t errorState; /**< Error State*/
} i2c_host_event_status_t;

#endif /* I2C_EVENT_TYPES_H */