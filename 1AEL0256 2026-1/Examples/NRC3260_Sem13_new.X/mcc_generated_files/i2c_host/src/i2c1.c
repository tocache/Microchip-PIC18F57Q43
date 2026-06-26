/**
 * I2C1 Generated Driver File
 *
 * @file i2c1.c
 *
 * @ingroup i2c_host
 *
 * @brief This file contains the API implementation for the I2C1 driver.
 *
 * @version I2C1 Driver Version 2.1.4
 * 
 * @version I2C1 Package Version 6.2.0
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

/**
 * @misradeviation {@advisory,8.7} Some Melody-generated driver APIs are made 
 * available to users through external linkage. Users have the option to 
 * add these APIs in the application.This rule ID is disabled at project level due to 
 * its multiple occurrences in several files.Therefore, in the application project, this rule ID 
 * must be disabled in the MPLAB-X IDE from Tools -> Options -> Embedded -> MISRA Check.
*/

#include <xc.h>
#include "../../system/config_bits.h"
#include "../i2c1.h"

static void I2C1_ReadStart(void);
static void I2C1_WriteStart(void);
static inline void I2C1_BusReset(void);
static void I2C1_Close(void);
static inline void I2C1_InterruptsEnable(void);
static inline void I2C1_InterruptsDisable(void);

const i2c_host_interface_t I2C1_Host = {
    .Initialize = I2C1_Initialize,
    .Deinitialize = I2C1_Deinitialize,
    .Write = I2C1_Write,
    .Read = I2C1_Read,
    .WriteRead = I2C1_WriteRead,
    .TransferSetup = NULL,
    .ErrorGet = I2C1_ErrorGet,
    .IsBusy = I2C1_IsBusy,
    .CallbackRegister = I2C1_CallbackRegister,
    .Tasks = NULL
};

static void (*I2C1_Callback)(void);
static volatile i2c_host_event_status_t i2c1Status = {0};

void I2C1_Initialize(void)
{
    /* CSTR Enable clocking; S Cleared by hardware after Start; MODE 7-bit address; EN disabled; RSEN disabled;  */
    I2C1CON0 = 0x4;

    /* TXU No underflow; CSD Clock Stretching enabled; RXO No overflow; ACKDT Acknowledge; ACKSTAT ACK received; ACKCNT Not Acknowledge;  */
    I2C1CON1 = 0x80;

    /* ABD enabled; GCEN disabled; ACNT disabled; SDAHT 30 ns hold time; BFRET 8 I2C Clock pulses; FME disabled;  */
    I2C1CON2 = 0x8;

    /* CLK MFINTOSC;  */
    I2C1CLK = 0x3;

    /* WRIF Data byte not detected; CNTIF Byte count is not zero; RSCIF Restart condition not detected; PCIF Stop condition not detected; ACKTIF Acknowledge sequence not detected; ADRIF Address not detected; SCIF Start condition not detected;  */
    I2C1PIR = 0x0;

    /* CNTIE disabled; RSCIE disabled; ACKTIE disabled; SCIE disabled; PCIE disabled; ADRIE disabled; WRIE disabled;  */
    I2C1PIE = 0x0;

    /* BTOIE disabled; BTOIF No bus timeout; NACKIF No NACK/Error detected; BCLIE disabled; BCLIF No bus collision detected; NACKIE disabled;  */
    I2C1ERR = 0x0;

    /* Count register */
    I2C1CNT = 0x0;
    I2C1_InterruptsEnable();

    /* Silicon-Errata: Section: 1.3.2 */
    // Refer to erratum DS80000870F: https://www.microchip.com/content/dam/mchp/documents/MCU08/ProductDocuments/Errata/PIC18F27-47-57Q43-Silicon-Errata-and-Datasheet-Clarifications-80000870J.pdf
    I2C1PIEbits.SCIE = 0;
    I2C1PIEbits.PCIE = 0;
    I2C1CON0bits.EN = 1;

    __delay_us(1);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    I2C1PIRbits.SCIF = 0;
    I2C1PIRbits.PCIF = 0;
    I2C1PIEbits.PCIE = 1;

    I2C1_Callback = NULL;
}

void I2C1_Deinitialize(void)
{
    I2C1CON0 = 0x00;

    I2C1CON1 = 0x00;

    I2C1CON2 = 0x00;

    I2C1CLK = 0x00;

    I2C1PIR = 0x00;

    I2C1PIE = 0x00;

    I2C1ERR = 0x00;

    I2C1CNT = 0x00;
    I2C1_InterruptsDisable();
}

bool I2C1_Write(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!I2C1_IsBusy())
    {
        i2c1Status.busy = true;
        i2c1Status.address = address;
        i2c1Status.switchToRead = false;
        i2c1Status.writePtr = data;
        i2c1Status.writeLength = dataLength;
        i2c1Status.readPtr = NULL;
        i2c1Status.readLength = 0;
        i2c1Status.errorState = I2C_ERROR_NONE;
        I2C1_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

bool I2C1_Read(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!I2C1_IsBusy())
    {
        i2c1Status.busy = true;
        i2c1Status.address = address;
        i2c1Status.switchToRead = false;
        i2c1Status.readPtr = data;
        i2c1Status.readLength = dataLength;
        i2c1Status.writePtr = NULL;
        i2c1Status.writeLength = 0;
        i2c1Status.errorState = I2C_ERROR_NONE;
        I2C1_ReadStart();
        retStatus = true;
    }
    return retStatus;
}

bool I2C1_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength)
{
    bool retStatus = false;
    if (!I2C1_IsBusy())
    {
        i2c1Status.busy = true;
        i2c1Status.address = address;
        i2c1Status.switchToRead = true;
        i2c1Status.writePtr = writeData;
        i2c1Status.writeLength = writeLength;
        i2c1Status.readPtr = readData;
        i2c1Status.readLength = readLength;
        i2c1Status.errorState = I2C_ERROR_NONE;
        I2C1_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

i2c_host_error_t I2C1_ErrorGet(void)
{
    i2c_host_error_t retErrorState = i2c1Status.errorState;
    i2c1Status.errorState = I2C_ERROR_NONE;
    return retErrorState;
}

bool I2C1_IsBusy(void)
{
    return i2c1Status.busy || !I2C1STAT0bits.BFRE;
}

void I2C1_CallbackRegister(void (*callbackHandler)(void))
{
    if (callbackHandler != NULL)
    {
        I2C1_Callback = callbackHandler;
    }
}

void __interrupt(irq(I2C1), base(8)) I2C1_ISR(void)
{
    if (I2C1PIEbits.PCIE && I2C1PIRbits.PCIF)
    {
        I2C1_Close();
    }
    else if (I2C1PIEbits.CNTIE && I2C1PIRbits.CNTIF)
    {
        // Check if restart is required
        if (0 != i2c1Status.switchToRead)
        {
            i2c1Status.switchToRead = false;
            I2C1PIRbits.SCIF = 0;
            I2C1PIRbits.CNTIF = 0;
            I2C1_ReadStart();
        }
        else 
        {
            I2C1CON0bits.RSEN = 0;
            if (0U != I2C1CNT)
            {
            I2C1CNT = 0;
            I2C1TXB = 0;
            }
            I2C1_Close();
        }
    }
    else if (I2C1PIEbits.RSCIE && I2C1PIRbits.RSCIF)
    {
        I2C1CON0bits.RSEN = 0;
        I2C1PIRbits.RSCIF = 0;
    }
    else
    {
         // No action required
    }
}

void __interrupt(irq(I2C1E), base(8)) I2C1_ERROR_ISR(void)
{
    if (I2C1ERRbits.BCLIF == 1U)
    {
        i2c1Status.errorState = I2C_ERROR_BUS_COLLISION;
        I2C1ERRbits.BCLIF = 0;
        I2C1_BusReset();
    }
    else if ((I2C1STAT0bits.D == 0U) && (I2C1CON1bits.ACKSTAT == 1U))
    {
        i2c1Status.errorState = I2C_ERROR_ADDR_NACK;
        I2C1ERRbits.NACKIF = 0;
        I2C1CON0bits.RSEN = 0;
        if (0U != I2C1CNT)
        {
        I2C1CNT = 0;
        I2C1TXB = 0;
        }
    }
    else if ((I2C1STAT0bits.D == 1U) && (I2C1CON1bits.ACKSTAT == 1U))
    {
        i2c1Status.errorState = I2C_ERROR_DATA_NACK;
        I2C1ERRbits.NACKIF = 0;
        I2C1CON0bits.RSEN = 0;
        if (0U != I2C1CNT)
        {
        I2C1CNT = 0;
        I2C1TXB = 0;
        }
    }
    else if (I2C1ERRbits.BTOIF == 1U)
    {
        i2c1Status.errorState = I2C_ERROR_BUS_COLLISION;
        I2C1ERRbits.BTOIF = 0;
    }
    else
    {
        I2C1ERRbits.NACKIF = 0;
    }

    if (i2c1Status.errorState != I2C_ERROR_NONE)
    {
        I2C1_Callback();
    }
}

void __interrupt(irq(I2C1RX), base(8)) I2C1_RX_ISR(void)
{   
    *i2c1Status.readPtr = I2C1RXB;
    i2c1Status.readPtr++;
}

void __interrupt(irq(I2C1TX), base(8)) I2C1_TX_ISR(void)
{
    I2C1TXB = *i2c1Status.writePtr;
    i2c1Status.writePtr++;

}

static void I2C1_ReadStart(void)
{
    if (0U != i2c1Status.readLength)
    {
    I2C1CNT = (uint8_t) i2c1Status.readLength;
    }

    I2C1ADB1 = (uint8_t) ((i2c1Status.address << 1) | 1U);
    I2C1CON0bits.S = 1;
}

static void I2C1_WriteStart(void)
{
    if (0U != i2c1Status.writeLength)
    {
    I2C1CNT = (uint8_t) i2c1Status.writeLength;
        if (0 != i2c1Status.switchToRead)
        {
            I2C1CON0bits.RSEN = 1;
        }
    }

    I2C1ADB1 = (uint8_t) (i2c1Status.address << 1);
    I2C1CON0bits.S = 1;
}

static void I2C1_Close(void)
{
    i2c1Status.busy = false;
    i2c1Status.address = 0xFF;
    i2c1Status.writePtr = NULL;
    i2c1Status.readPtr = NULL;
    I2C1PIR = 0x00;
    I2C1ERRbits.BCLIF = 0;
    I2C1ERRbits.BTOIF = 0;
    I2C1ERRbits.NACKIF = 0;
    I2C1STAT1 = 0x00;
    I2C1STAT1bits.CLRBF = 1;
}

static inline void I2C1_BusReset(void)
{
    I2C1PIR = 0x00;
    I2C1ERRbits.BCLIF = 0;
    I2C1ERRbits.BTOIF = 0;
    I2C1ERRbits.NACKIF = 0;
    I2C1_InterruptsDisable();
    I2C1STAT1 = 0x00;
    I2C1STAT1bits.CLRBF = 1;
    I2C1CON0bits.EN = 0;
    I2C1_InterruptsEnable();

    /* Silicon-Errata: Section: 1.3.2 */
    #pragma message "Refer to erratum DS80000870F: https://www.microchip.com/content/dam/mchp/documents/MCU08/ProductDocuments/Errata/PIC18F27-47-57Q43-Silicon-Errata-and-Datasheet-Clarifications-80000870J.pdf"
    I2C1PIEbits.SCIE = 0;
    I2C1PIEbits.PCIE = 0;
    I2C1CON0bits.EN = 1;
    __delay_us(1);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    I2C1PIRbits.SCIF = 0;
    I2C1PIRbits.PCIF = 0;
    I2C1PIEbits.PCIE = 1;
}

static inline void I2C1_InterruptsEnable(void)
{
    PIE7bits.I2C1IE = 1;
    PIE7bits.I2C1EIE = 1;
    PIE7bits.I2C1RXIE = 1;
    PIE7bits.I2C1TXIE = 1;

    I2C1PIEbits.PCIE = 1;
    I2C1PIEbits.RSCIE = 1;
    I2C1PIEbits.CNTIE = 1;
    I2C1ERRbits.NACKIE = 1;
}

static inline void I2C1_InterruptsDisable(void)
{
    PIE7bits.I2C1IE = 0;
    PIE7bits.I2C1EIE = 0;
    PIE7bits.I2C1RXIE = 0;
    PIE7bits.I2C1TXIE = 0;
    I2C1PIE = 0x00;
    I2C1ERR = 0x00;
}
