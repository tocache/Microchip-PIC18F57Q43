/**
 * UART1 Generated Driver API Header File
 * 
 * @file uart1.c
 * 
 * @ingroup uart1
 * 
 * @brief This is the generated driver implementation file for the UART1 driver using the Universal Asynchronous Receiver and Transmitter (UART) module.
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

/**
  Section: Included Files
*/
#include "../uart1.h"

/**
  Section: Macro Declarations
*/

/**
  Section: UART1 variables
*/
 /**
 * @misradeviation{@advisory,19.2}
 * The UART error status necessitates checking the bitfield and accessing the status within the group byte therefore the use of a union is essential.
 */
 /* cppcheck-suppress misra-c2012-19.2 */
static volatile uart1_status_t uart1RxLastError;

/**
  Section: UART1 APIs
*/

static void (*UART1_FramingErrorHandler)(void);
static void (*UART1_OverrunErrorHandler)(void);
static void (*UART1_ParityErrorHandler)(void);

static void UART1_DefaultFramingErrorCallback(void);
static void UART1_DefaultOverrunErrorCallback(void);
static void UART1_DefaultParityErrorCallback(void);

/**
  Section: UART1  APIs
*/

void UART1_Initialize(void)
{

    // Set the UART1 module to the options selected in the user interface.

    //RXCHK disabled; 
    U1RXCHK = 0x0;
    //TXCHK disabled; 
    U1TXCHK = 0x0;
    //P1L 0x0; 
    U1P1L = 0x0;
    //P1H 0x0; 
    U1P1H = 0x0;
    //P2L 0x0; 
    U1P2L = 0x0;
    //P2H 0x0; 
    U1P2H = 0x0;
    //P3L 0x0; 
    U1P3L = 0x0;
    //P3H 0x0; 
    U1P3H = 0x0;
    //MODE Asynchronous 8-bit mode; RXEN enabled; TXEN enabled; ABDEN disabled; BRGS high speed; 
    U1CON0 = 0xB0;
    //SENDB disabled; BRKOVR disabled; RXBIMD Set RXBKIF on rising RX input; WUE disabled; ON enabled; 
    U1CON1 = 0x80;
    //FLO off; TXPOL not inverted; C0EN Add all TX and RX characters; STP Transmit 1Stop bit, receiver verifies first Stop bit; RXPOL not inverted; RUNOVF RX input shifter stops all activity; 
    U1CON2 = 0x8;
    //BRGL 130; 
    U1BRGL = 0x82;
    //BRGH 6; 
    U1BRGH = 0x6;
    //TXBE empty; STPMD in middle of first Stop bit; TXWRE No error; 
    U1FIFO = 0x2E;
    //ABDIE disabled; ABDIF Auto-baud not enabled or not complete; WUIF WUE not enabled by software; 
    U1UIR = 0x0;
    //TXCIF equal; RXFOIF not overflowed; RXBKIF No Break detected; FERIF no error; CERIF No Checksum error; ABDOVF Not overflowed; PERIF no parity error; TXMTIF empty; 
    U1ERRIR = 0x80;
    //TXCIE disabled; RXFOIE disabled; RXBKIE disabled; FERIE disabled; CERIE disabled; ABDOVE disabled; PERIE disabled; TXMTIE disabled; 
    U1ERRIE = 0x0;

    UART1_FramingErrorCallbackRegister(UART1_DefaultFramingErrorCallback);
    UART1_OverrunErrorCallbackRegister(UART1_DefaultOverrunErrorCallback);
    UART1_ParityErrorCallbackRegister(UART1_DefaultParityErrorCallback);

    uart1RxLastError.status = 0;  
}

void UART1_Deinitialize(void)
{
    U1RXB = 0x00;
    U1RXCHK = 0x00;
    U1TXB = 0x00;
    U1TXCHK = 0x00;
    U1P1L = 0x00;
    U1P1H = 0x00;
    U1P2L = 0x00;
    U1P2H = 0x00;
    U1P3L = 0x00;
    U1P3H = 0x00;
    U1CON0 = 0x00;
    U1CON1 = 0x00;
    U1CON2 = 0x00;
    U1BRGL = 0x00;
    U1BRGH = 0x00;
    U1FIFO = 0x00;
    U1UIR = 0x00;
    U1ERRIR = 0x00;
    U1ERRIE = 0x00;
}

void UART1_Enable(void)
{
    U1CON1bits.ON = 1; 
}

void UART1_Disable(void)
{
    U1CON1bits.ON = 0; 
}

void UART1_TransmitEnable(void)
{
    U1CON0bits.TXEN = 1;
}

void UART1_TransmitDisable(void)
{
    U1CON0bits.TXEN = 0;
}

void UART1_ReceiveEnable(void)
{
    U1CON0bits.RXEN = 1;
}

void UART1_ReceiveDisable(void)
{
    U1CON0bits.RXEN = 0;
}

void UART1_SendBreakControlEnable(void)
{
    U1CON1bits.SENDB = 1;
}

void UART1_SendBreakControlDisable(void)
{
    U1CON1bits.SENDB = 0;
}

void UART1_AutoBaudSet(bool enable)
{
    if(enable)
    {
        U1CON0bits.ABDEN = 1; 
    }
    else
    {
      U1CON0bits.ABDEN = 0;  
    }
}


bool UART1_AutoBaudQuery(void)
{
    return (bool)U1UIRbits.ABDIF; 
}

void UART1_AutoBaudDetectCompleteReset(void)
{
    U1UIRbits.ABDIF = 0; 
}

bool UART1_IsAutoBaudDetectOverflow(void)
{
    return (bool)U1ERRIRbits.ABDOVF; 
}

void UART1_AutoBaudDetectOverflowReset(void)
{
    U1ERRIRbits.ABDOVF = 0; 
}

bool UART1_IsRxReady(void)
{
    return (bool)(!U1FIFObits.RXBE);
}

bool UART1_IsTxReady(void)
{
    return (bool)(U1FIFObits.TXBE && U1CON0bits.TXEN);
}

bool UART1_IsTxDone(void)
{
    return U1ERRIRbits.TXMTIF;
}

size_t UART1_ErrorGet(void)
{
    uart1RxLastError.status = 0;
    
    if(true == U1ERRIRbits.FERIF)
    {
        uart1RxLastError.ferr = 1;
        if(NULL != UART1_FramingErrorHandler)
        {
            UART1_FramingErrorHandler();
        }  
    }
    if(true == U1ERRIRbits.RXFOIF)
    {
        uart1RxLastError.oerr = 1;
        if(NULL != UART1_OverrunErrorHandler)
        {
            UART1_OverrunErrorHandler();
        }   
    }
    if(true == U1ERRIRbits.PERIF)
    {
        uart1RxLastError.perr = 1;
        if(NULL != UART1_ParityErrorHandler)
        {
            UART1_ParityErrorHandler();
        }   
    }

    return uart1RxLastError.status;
}

uint8_t UART1_Read(void)
{
    return U1RXB;
}


void UART1_Write(uint8_t txData)
{
    U1TXB = txData;
    while(!UART1_IsTxDone());
}

void UART1_String_Write(const uint8_t *cadenasa){

  while(*cadenasa){

    UART1_Write(*cadenasa++);

  }

}



void UART1_NewLine(void){

  UART1_Write(0x0A);

  UART1_Write(0x0D);

}



void UART1_8bitVar_Write(uint8_t numero){

  UART1_Write((numero / 100) + 0x30);

  UART1_Write(((numero % 100) / 10) + 0x30);

  UART1_Write((numero % 10) + 0x30);

}



void UART1_8bitVar_Write2(uint8_t numero, uint8_t c_digitos){

  switch(c_digitos){

    case 3:

      UART1_Write((numero / 100) + 0x30);

      UART1_Write(((numero % 100) / 10) + 0x30);

      UART1_Write((numero % 10) + 0x30);

      break;

    case 2:

      UART1_Write(((numero % 100) / 10) + 0x30);

      UART1_Write((numero % 10) + 0x30);

      break;

    case 1:

      UART1_Write((numero % 10) + 0x30);

      break;

  }

}



void UART1_16bitVar_Write(uint16_t numero){

  UART1_Write((numero / 10000) + 0x30);

  UART1_Write(((numero % 10000) / 1000) + 0x30);

  UART1_Write(((numero % 1000) / 100) + 0x30);

  UART1_Write(((numero % 100) / 10) + 0x30);

  UART1_Write((numero % 10) + 0x30);

}



void UART1_16bitVar_Write2(uint16_t numero, uint8_t c_digitos){

  switch(c_digitos){

    case 5:

      UART1_Write((numero / 10000) + 0x30);

      UART1_Write(((numero % 10000) / 1000) + 0x30);

      UART1_Write(((numero % 1000) / 100) + 0x30);

      UART1_Write(((numero % 100) / 10) + 0x30);

      UART1_Write((numero % 10) + 0x30);

      break;

    case 4:

      UART1_Write(((numero % 10000) / 1000) + 0x30);

      UART1_Write(((numero % 1000) / 100) + 0x30);

      UART1_Write(((numero % 100) / 10) + 0x30);

      UART1_Write((numero % 10) + 0x30);

      break;

    case 3:

      UART1_Write((numero / 100) + 0x30);

      UART1_Write(((numero % 100) / 10) + 0x30);

      UART1_Write((numero % 10) + 0x30);

      break;

    case 2:

      UART1_Write(((numero % 100) / 10) + 0x30);

      UART1_Write((numero % 10) + 0x30);

      break;

    case 1:

      UART1_Write((numero % 10) + 0x30);

      break;

  }

}



void UART1_Float_Write(float numero, uint8_t decimales){

  char buffer[20]; // Buffer para almacenar el texto convertido

   

  // snprintf formatea el float de forma segura dentro del buffer

  // %. *f permite pasar la cantidad de decimales como variable

  snprintf(buffer, sizeof(buffer), "%.*f", decimales, numero);

   

  // Bucle para enviar caracter por caracter hasta encontrar el fin de cadena '\0'

  for (int i = 0; buffer[i] != '\0'; i++) {

    UART1_Write(buffer[i]);      // Enviar el caracter actual

  }   

}




static void UART1_DefaultFramingErrorCallback(void)
{
    
}

static void UART1_DefaultOverrunErrorCallback(void)
{
    
}

static void UART1_DefaultParityErrorCallback(void)
{
    
}

void UART1_FramingErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        UART1_FramingErrorHandler = callbackHandler;
    }
}

void UART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        UART1_OverrunErrorHandler = callbackHandler;
    }    
}

void UART1_ParityErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        UART1_ParityErrorHandler = callbackHandler;
    } 
}
