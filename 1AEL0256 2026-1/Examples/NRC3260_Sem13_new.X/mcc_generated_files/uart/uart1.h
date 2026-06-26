/**
 * UART1 Generated Driver API Header File
 * 
 * @file uart1.h
 * 
 * @defgroup uart1 UART1
 * 
 * @brief This file contains API prototypes and other data types for the the Universal Asynchronous Receiver and Transmitter (UART) module.
 *
 * @version UART1 Driver Version 3.0.9
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

#ifndef UART1_H
#define UART1_H


#include <stdbool.h>
#include <stdint.h>
#include "../system/system.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


/**
 @ingroup uart1
 @struct uart1_status_t
 @brief This is a structure defined for errors in reception of data.
 */
 /**
 * @misradeviation{@advisory,19.2}
 * The UART error status necessitates checking the bitfield and accessing the status within the group byte therefore the use of a union is essential.
 */
 /* cppcheck-suppress misra-c2012-19.2 */
typedef union {
    struct {
        uint8_t perr : 1;     /**<This is a bit field for Parity Error status*/
        uint8_t ferr : 1;     /**<This is a bit field for Framing Error status*/
        uint8_t oerr : 1;     /**<This is a bit field for Overfrun Error status*/
        uint8_t reserved : 5; /**<Reserved*/
    };
    size_t status;            /**<Group byte for status errors*/
}uart1_status_t;

/**
 * @ingroup uart1
 * @brief Initializes the UART1 module. This routine is called
 *        only once during system initialization, before calling other APIs.
 * @param None.
 * @return None.
 */
void UART1_Initialize(void);

/**
 * @ingroup uart1
 * @brief Deinitializes and disables the UART1 module.

 * @param None.
 * @return None.
 */
void UART1_Deinitialize(void);

/**
 * @ingroup uart1
 * @brief Enables the UART1 module.     
 * @param None.
 * @return None.
 */
void UART1_Enable(void);

/**
 * @ingroup uart1
 * @brief Disables the UART1 module.
 * @param None.
 * @return None.
 */
void UART1_Disable(void);

/**
 * @ingroup uart1
 * @brief Enables the UART1 transmitter. 
 *        The UART1 must be enabled to send the bytes over to the TX pin.
 * @param None.
 * @return None.
 */
void UART1_TransmitEnable(void);

/**
 * @ingroup uart1
 * @brief Disables the UART1 transmitter.
 * @param None.
 * @return None.
 */
void UART1_TransmitDisable(void);

/**
 * @ingroup uart1
 * @brief Enables the UART1 receiver.
 *        The UART1 must be enabled to receive the bytes sent by the RX pin.
 * @param None.
 * @return None.
 */
void UART1_ReceiveEnable(void);

/**
 * @ingroup uart1
 * @brief Disables the UART1 receiver.
 * @param None.
 * @return None.
 */
void UART1_ReceiveDisable(void);

/**
 * @ingroup uart1
 * @brief Enables the UART1 to send a break control.
 * @param None.
 * @return None.
 */
void UART1_SendBreakControlEnable(void);

/**
 * @ingroup uart1
 * @brief Disables the UART1 Send Break Control bit.
 * @param None.
 * @return None.
 */
void UART1_SendBreakControlDisable(void);

/**
 * @ingroup uart1
 * @brief Enables the UART1 Auto-Baud Detection (ABR).
 * @param bool enable
 * @return None.
 */
void UART1_AutoBaudSet(bool enable);


/**
 * @ingroup uart1
 * @brief Reads the UART1 Auto-Baud Detection Complete bit.
 * @param None.
 * @return None.
 */
bool UART1_AutoBaudQuery(void);

/**
 * @ingroup uart1
 * @brief Resets the UART1 Auto-Baud Detection Complete bit.
 * @param None.
 * @return None.
 */
void UART1_AutoBaudDetectCompleteReset(void);

/**
 * @ingroup uart1
 * @brief Reads the UART1 Auto-Baud Detection Overflow bit.
 * @param None.
 * @return None.
 */
bool UART1_IsAutoBaudDetectOverflow(void);

/**
 * @ingroup uart1
 * @brief Resets the UART1 Auto-Baud Detection Overflow bit.
 * @param None.
 * @return None.
 */
void UART1_AutoBaudDetectOverflowReset(void);

/**
 * @ingroup uart1
 * @brief Checks if the UART1 receiver has received data and is ready to be read.
 * @param None.
 * @retval True - UART1 receiver FIFO has data
 * @retval False - UART1 receiver FIFO is empty
 */
bool UART1_IsRxReady(void);

/**
 * @ingroup uart1
 * @brief Checks if the UART1 transmitter is ready to accept a data byte.
 * @param None.
 * @retval True -  The UART1 transmitter FIFO has at least a one byte space
 * @retval False - The UART1 transmitter FIFO is full
 */
bool UART1_IsTxReady(void);

/**
 * @ingroup uart1
 * @brief Returns the status of the Transmit Shift Register (TSR).
 * @param None.
 * @retval True - Data completely shifted out from the TSR
 * @retval False - Data is present in Transmit FIFO and/or in TSR
 */
bool UART1_IsTxDone(void);

/**
 * @ingroup uart1
 * @brief Gets the error status of the last read byte. Call 
 *        this function before calling UART1_Read().
 * @pre Call UART1_RxEnable() to enable RX before calling this API.
 * @param None.
 * @return Status of the last read byte. See the uart1_status_t struct for more details.
 */
size_t UART1_ErrorGet(void);

/**
 * @ingroup uart1
 * @brief Reads the eight bits from the Receiver FIFO register.
 * @pre Check the transfer status to see if the receiver is not empty before calling this function. Check 
 *      UART1_IsRxReady() in if () before calling this API.
 * @param None.
 * @return 8-bit data from the RX FIFO register
 */
uint8_t UART1_Read(void);

/**
 * @ingroup uart1
 * @brief Writes a byte of data to the Transmitter FIFO register. Mejorado por Kalun ps
 * @pre Check the transfer status to see if the transmitter is not empty before calling this function. Check
 *      UART1_IsTxReady() in if () before calling this API.
 * @param txData  - Data byte to write to the TX FIFO
 * @return None.
 */
void UART1_Write(uint8_t txData);

/**
 * @ingroup uart1
 * @brief Envia una cadena de caracteres, hecho por Kalun
 * @pre no hay pre ps
 * @param txData  - Data byte to write to the TX FIFO
 * @return None.
 */
void UART1_String_Write(const char *culebron);

/**
 * @ingroup uart1
 * @brief Manda el cursor del terminal serial a una nueva linea y retorna el carro
 * @pre tampoco hay pre ps
 * @param txData  - Data byte to write to the TX FIFO
 * @return None.
 */
void UART1_NewLine();

/**
 * @ingroup uart1
 * @brief Calls the function upon UART1 framing error.
 * @param callbackHandler - Function pointer called when the framing error condition occurs
 * @return None.
 */
void UART1_FramingErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup uart1
 * @brief Calls the function upon UART1 overrun error.
 * @param callbackHandler - Function pointer called when the overrun error condition occurs
 * @return None.
 */
void UART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup uart1
 * @brief Calls the function upon UART1 parity error.
 * @param callbackHandler - Function pointer called when the parity error condition occurs
 * @return None.
 */
void UART1_ParityErrorCallbackRegister(void (* callbackHandler)(void));


#ifdef __cplusplus  // Provide C++ Compatibility


    }

#endif

#endif  // UART1_H
