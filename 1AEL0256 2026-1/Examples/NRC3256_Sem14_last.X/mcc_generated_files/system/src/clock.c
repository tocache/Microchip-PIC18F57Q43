/**
 * CLOCK Generated Driver Source File
 * 
 * @file clock.c
 * 
 * @ingroup clockdriver 
 * 
 * @brief This file contains the API prototypes for the Clock driver.
 *
 * @version Driver Version 2.0.4
 *
 * @version Package Version 4.3.7
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

#include <xc.h>
#include "../clock.h"

void CLOCK_Initialize(void)
{
    // Set the CLOCK CONTROL module to the options selected in the user interface.
    OSCCON1 = (0 << _OSCCON1_NDIV_POSN)   // NDIV 1
        | (6 << _OSCCON1_NOSC_POSN);  // NOSC HFINTOSC
    OSCCON3 = (0 << _OSCCON3_SOSCPWR_POSN)   // SOSCPWR Low power
        | (0 << _OSCCON3_CSWHOLD_POSN);  // CSWHOLD may proceed
    OSCEN = (0 << _OSCEN_EXTOEN_POSN)   // EXTOEN disabled
        | (0 << _OSCEN_HFOEN_POSN)   // HFOEN disabled
        | (0 << _OSCEN_MFOEN_POSN)   // MFOEN disabled
        | (0 << _OSCEN_LFOEN_POSN)   // LFOEN disabled
        | (0 << _OSCEN_SOSCEN_POSN)   // SOSCEN disabled
        | (0 << _OSCEN_ADOEN_POSN)   // ADOEN disabled
        | (0 << _OSCEN_PLLEN_POSN);  // PLLEN disabled
    OSCFRQ = (8 << _OSCFRQ_HFFRQ_POSN);  // HFFRQ 64_MHz
    OSCTUNE = (0 << _OSCTUNE_TUN_POSN);  // TUN 0x0
    ACTCON = (0 << _ACTCON_ACTEN_POSN)   // ACTEN disabled
        | (0 << _ACTCON_ACTUD_POSN);  // ACTUD enabled

}
/**
 End of File
*/