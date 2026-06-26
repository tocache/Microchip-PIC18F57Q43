/**
 * I2C Generated Driver Types Header File
 *
 * @file i2c_host_types.h
 *
 * @ingroup i2c_host_interface
 *
 * @brief This header file provides helper structures for the I2C driver.
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

#ifndef I2C_HOST_TYPES_H
#define	I2C_HOST_TYPES_H

/**
 * @ingroup i2c_host_interface
 * @enum  i2c_host_error_t
 * @brief Enumeration defining the potential error types in the I2C host driver.
 */
typedef enum
{
    I2C_ERROR_NONE,             /**< No Error */
    I2C_ERROR_ADDR_NACK,        /**< Client returned Address NACK */
    I2C_ERROR_DATA_NACK,        /**< Client returned Data NACK */
    I2C_ERROR_BUS_COLLISION,    /**< Bus Collision Error */
} i2c_host_error_t;

/**
 * @ingroup i2c_host_interface
 * @struct i2c_host_transfer_setup_t
 * @brief Structure for I2C clock configurations.
 */
/**
 * @misradeviation{@advisory,2.4,@advisory,2.3}These declarations provided by the Melody-generated drivers for the user's 
 * application. It is up to the user if these declarations will be implemented in their application.
*/
/* cppcheck-suppress misra-c2012-2.3 */
typedef struct i2c_transfer_setup
{/* cppcheck-suppress misra-c2012-2.4 */
  uint32_t clkSpeed;            
}i2c_host_transfer_setup_t;

#endif /* I2C_HOST_TYPES_H */