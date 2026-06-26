/**
 * ADC Generated Driver File
 * 
 * @file adc.c
 * 
 * @ingroup  adc
 * 
 * @brief This file contains the API implementations for the ADC driver.
 *
 * @version ADC Driver Version 3.0.0
 * 
 * @version ADC Package Version 5.0.1
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

// Section: Included Files

#include <xc.h>
#include "../adc.h"
#include "../adc_types.h"


static void (*ADC_ConversionDoneCallback)(void);
static void (*ADC_ThresholdCallback)(void);
static bool adc_busy_status;

void ADC_Initialize(void)
{
    ADCON0bits.ADON = ADC_BIT_CLEAR;
    ADLTHL = (0 << _ADLTHL_ADLTH_POSITION);	/* ADLTH 0x0(0) */
    ADLTHH = (0 << _ADLTHH_ADLTH_POSITION);	/* ADLTH 0x0(0) */
    ADUTHL = (0 << _ADUTHL_ADUTH_POSITION);	/* ADUTH 0x0(0) */
    ADUTHH = (0 << _ADUTHH_ADUTH_POSITION);	/* ADUTH 0x0(0) */
    ADSTPTL = (0 << _ADSTPTL_ADSTPT_POSITION);	/* ADSTPT 0x0(0) */
    ADSTPTH = (0 << _ADSTPTH_ADSTPT_POSITION);	/* ADSTPT 0x0(0) */
    ADACCU = (0 << _ADACCU_ADACC_POSITION);	/* ADACC 0x0(0) */
    ADRPT = (0 << _ADRPT_ADRPT_POSITION);	/* ADRPT 0x0(0) */
    ADPCH = (0 << _ADPCH_PCH_POSITION);	/* PCH ANA0(0) */
    ADACQL = (0 << _ADACQL_ADACQ_POSITION);	/* ADACQ 0x0(0) */
    ADACQH = (0 << _ADACQH_ADACQ_POSITION);	/* ADACQ 0x0(0) */
    ADCP = (0 << _ADCP_CPON_POSITION);	/* CPON Charge pump Off(0) */
    ADCAP = (0 << _ADCAP_CAP_POSITION);	/* CAP Additional uC disabled(0) */
    ADPREL = (0 << _ADPREL_ADPRE_POSITION);	/* ADPRE 0x0(0) */
    ADPREH = (0 << _ADPREH_ADPRE_POSITION);	/* ADPRE 0x0(0) */
    ADCON1 = (0 << _ADCON1_ADDSEN_POSITION)	/* ADDSEN disabled(0) */
			|(0 << _ADCON1_ADGPOL_POSITION)	/* ADGPOL digital_low(0) */
			|(0 << _ADCON1_ADIPEN_POSITION)	/* ADIPEN disabled(0) */
			|(0 << _ADCON1_ADPPOL_POSITION);	/* ADPPOL Vss(0) */
    ADCON2 = (0 << _ADCON2_ADMD_POSITION)	/* ADMD Basic_mode(0) */
			|(1 << _ADCON2_ADACLR_POSITION)	/* ADACLR enabled(1) */
			|(1 << _ADCON2_ADCRS_POSITION)	/* ADCRS 0x1(1) */
			|(0 << _ADCON2_ADPSIS_POSITION);	/* ADPSIS RES(0) */
    ADCON3 = (0 << _ADCON3_ADTMD_POSITION)	/* ADTMD disabled(0) */
			|(0 << _ADCON3_ADSOI_POSITION)	/* ADSOI ADGO not cleared(0) */
			|(1 << _ADCON3_ADCALC_POSITION);	/* ADCALC Actual result vs setpoint(1) */
    ADSTAT =(0 << _ADSTAT_ADMATH_POSITION);	/* ADMATH registers not updated(0) */
    ADREF = (0 << _ADREF_ADPREF_POSITION)	/* ADPREF VDD(0) */
			|(0 << _ADREF_ADNREF_POSITION);	/* ADNREF VSS(0) */
    ADCLK = (31 << _ADCLK_ADCS_POSITION);	/* ADCS FOSC/64(31) */
    ADACT = (0 << _ADACT_ADACT_POSITION);	/* ADACT disabled(0) */

    ADC_ConversionDoneCallback = NULL;
    ADC_ThresholdCallback = NULL;
    adc_busy_status = false;

    PIR1bits.ADIF = ADC_BIT_CLEAR;
    PIE1bits.ADIE = ADC_BIT_CLEAR;
    PIR2bits.ADTIF = ADC_BIT_CLEAR;
    PIE2bits.ADTIE = ADC_BIT_CLEAR;
    ADCON0 = (0 << _ADCON0_ADGO_POSITION)	/* ADGO stop(0) */
			|(1 << _ADCON0_ADFM_POSITION)	/* ADFM right(1) */
			|(1 << _ADCON0_ADCS_POSITION)	/* ADCS ADCRC(1) */
			|(0 << _ADCON0_ADCONT_POSITION)	/* ADCONT disabled(0) */
			|(1 << _ADCON0_ADON_POSITION);	/* ADON enabled(1) */
}

void ADC_Deinitialize(void)
{
    ADCON0 = 0x0;
    PIR1bits.ADIF = ADC_BIT_CLEAR;
    PIE1bits.ADIE = ADC_BIT_CLEAR;
    PIR2bits.ADTIF = ADC_BIT_CLEAR;
    PIE2bits.ADTIE = ADC_BIT_CLEAR;
    
    ADLTHL = 0x0;
    ADLTHH = 0x0;
    ADUTHL = 0x0;
    ADUTHH = 0x0;
    ADSTPTL = 0x0;
    ADSTPTH = 0x0;
    ADACCU = 0x0;
    ADRPT = 0x0;
    ADPCH = 0x0;
    ADACQL = 0x0;
    ADACQH = 0x0;
    ADCP = 0x0;
    ADCAP = 0x0;
    ADPREL = 0x0;
    ADPREH = 0x0;
    ADCON1 = 0x0;
    ADCON2 = 0x0;
    ADCON3 = 0x0;
    ADSTAT = 0x0;
    ADREF = 0x0;
    ADCLK = 0x0;
    ADACT = 0x0;
}

void ADC_Enable(void)
{
    ADCON0bits.ADON = ADC_BIT_SET;
}

void ADC_Disable(void)
{
    ADCON0bits.ADON = ADC_BIT_CLEAR;
}

void ADC_ChannelSelect(adc_channel_t channel)
{
   ADPCH = channel;  
}

void ADC_ConversionStart(void)
{
    ADCON0bits.ADGO = ADC_BIT_SET;
}

bool ADC_IsConversionDone(void)
{
    return ((bool)(!ADCON0bits.ADGO));
}

void ADC_ConversionStop(void)
{
    ADCON0bits.ADGO = ADC_BIT_CLEAR;
}

adc_result_t ADC_ConversionResultGet(void)
{
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

void ADC_ComputationModeSet(adc_computation_mode_t computationMode)
{
    ADCON2bits.ADMD = computationMode;
}

void ADC_ThresholdModeSet(adc_threshold_mode_t  thresholdMode)
{
    ADCON3bits.ADTMD = thresholdMode;    
}

void ADC_SampleRepeatCountSet(adc_repeat_count_t repeatCount)
{
    ADRPT = repeatCount;
}

void ADC_UpperThresholdSet(adc_threshold_t upperThreshold)
{
    ADUTHH = (uint8_t) ((uint16_t)upperThreshold >> 8);
    ADUTHL = (uint8_t) upperThreshold;
}

void ADC_LowerThresholdSet(adc_threshold_t lowerThreshold)
{
    ADLTHH = (uint8_t) ((uint16_t)lowerThreshold >> 8);
    ADLTHL = (uint8_t) lowerThreshold;
}

adc_accumulate_t ADC_AccumulatedResultGet(void)
{
    return (adc_accumulate_t)(((uint32_t)ADACCU << 16) + ((uint32_t)ADACCH << 8) + ADACCL);
}

adc_result_t ADC_ChannelSelectAndConvert(adc_channel_t channel)
{
    ADPCH = channel;  
    ADCON0bits.ADCONT = ADC_BIT_CLEAR;

    ADCON0bits.ADGO = ADC_BIT_SET;

    while (true == ADCON0bits.ADGO)
    {
    }
    
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

void ADC_StopOnInterruptEnable(void)
{
    ADCON3bits.ADSOI = ADC_BIT_SET;
}

void ADC_StopOnInterruptDisable(void)
{
    ADCON3bits.ADSOI = ADC_BIT_CLEAR;
}

void ADC_SampleCapacitorDischarge(void)
{
    ADPCH = ADC_CHANNEL_VSS;   
}

void ADC_AcquisitionTimeSet(uint16_t acquisitionValue)
{
    ADACQH = (uint8_t) (acquisitionValue >> 8);
    ADACQL = (uint8_t) acquisitionValue;  
}

void ADC_PrechargeTimeSet(uint16_t prechargeTime)
{
    ADPREH = (uint8_t) (prechargeTime >> 8);
    ADPREL = (uint8_t) prechargeTime;
}

adc_repeat_count_t ADC_CurrentConversionCountGet(void)
{
    return ((adc_repeat_count_t)ADCNT);
}

void ADC_AccumulatorClear(void)
{
    ADCON2bits.ADACLR = ADC_BIT_SET;
}

bool ADC_IsAccumulatorClearComplete(void)
{
    return ((bool)(!ADCON2bits.ADACLR));
}

bool ADC_HasAccumulatorOverflowed(void)
{
    return ADSTATbits.ADAOV;
}

adc_result_t ADC_FilterValueGet(void)
{
    return ((adc_result_t)((ADFLTRH << 8) + ADFLTRL));
}

adc_result_t ADC_PreviousResultGet(void)
{
    return ((adc_result_t)((ADPREVH << 8) + ADPREVL));
}

void ADC_SetPointDefine(adc_threshold_t setPoint)
{
    ADSTPTH = (uint8_t) ((uint16_t)setPoint >> 8);
    ADSTPTL = (uint8_t) setPoint;
}

adc_result_t ADC_ErrorCalculationGet(void)
{
    return ((adc_result_t)((ADERRH << 8) + ADERRL));
}

void ADC_DoubleSamplingEnable(void)
{
    ADCON1bits.ADDSEN = ADC_BIT_SET;
}

void ADC_DoubleSamplingDisable(void)
{
    ADCON1bits.ADDSEN = ADC_BIT_CLEAR;
}

void ADC_ContinuousConversionEnable(void)
{
    ADCON0bits.ADCONT = ADC_BIT_SET;
}

void ADC_ContinuousConversionDisable(void)
{
    ADCON0bits.ADCONT = ADC_BIT_CLEAR;
}

bool ADC_IsErrorGreaterThanUpperThreshold(void)
{
    return ADSTATbits.ADUTHR;
}

bool ADC_IsErrorLesserThanLowerThreshold(void)
{
    return ADSTATbits.ADLTHR;
}

adc_conversion_stage_t ADC_ConversionStageStatusGet(void)
{
    return (adc_conversion_stage_t)ADSTATbits.ADSTAT;
}

void ADC_AutoTriggerSourceSet(adc_trigger_source_t triggerSource)
{
    ADACT = triggerSource;
}

void ADC_ErrorCalculationModeSet(adc_calculation_mode_t errorCalculationMode)
{
    ADCON3bits.ADCALC = errorCalculationMode;    
}    

void ADC_CalculationRightShiftSet(uint8_t rightShiftValue)
{
    ADCON2bits.ADCRS = rightShiftValue;      
}

void ADC_ChargePumpEnable(void)
{
    ADCPbits.CPON = ADC_BIT_SET;
}

void ADC_ChargePumpDisable(void)
{
    ADCPbits.CPON = ADC_BIT_CLEAR;
}

bool ADC_IsChargePumpReady(void)
{
    return ADCPbits.CPRDY;
}

uint8_t ADC_ResolutionGet(void)
{
    return ADC_RESOLUTION;
}

bool ADC_IsBusy(void)
{
    return adc_busy_status;
}

void ADC_BusyStatusSet(bool status)
{
    adc_busy_status = status;
}

void ADC_ConversionDoneInterruptFlagClear(void)
{
    PIR1bits.ADIF = ADC_BIT_CLEAR;
}

void ADC_ThresholdInterruptFlagClear(void)
{
    PIR2bits.ADTIF = ADC_BIT_CLEAR;
}

bool ADC_IsConversionDoneInterruptFlagSet(void)
{
    return PIR1bits.ADIF;
}

bool ADC_IsThresholdInterruptFlagSet(void)
{
    return PIR2bits.ADTIF;
}

void ADC_ConversionDoneCallbackRegister(void (*callback)(void))
{
    ADC_ConversionDoneCallback = callback;
}

void ADC_ThresholdCallbackRegister(void (*callback)(void))
{
    ADC_ThresholdCallback = callback;
}

void ADC_ConversionDoneInterruptEnable(void)
{
    PIE1bits.ADIE = ADC_BIT_SET;
}

void ADC_ConversionDoneInterruptDisable(void)
{
    PIE1bits.ADIE = ADC_BIT_CLEAR;
}

void ADC_ThresholdInterruptEnable(void)
{
    PIE2bits.ADTIE = ADC_BIT_SET;    
}

void ADC_ThresholdInterruptDisable(void)
{
    PIE2bits.ADTIE = ADC_BIT_CLEAR;    
}

void __interrupt(irq(AD),base(8)) ADC_ISR(void)
{
    PIR1bits.ADIF = ADC_BIT_CLEAR;

    if (NULL != ADC_ConversionDoneCallback)
    {
        ADC_ConversionDoneCallback();
    }
    else
    {
        // Do nothing
    }
}

void __interrupt(irq(ADT),base(8)) ADC_ThresholdISR(void)
{
    PIR2bits.ADTIF = ADC_BIT_CLEAR;

    if (NULL != ADC_ThresholdCallback)
    {
        ADC_ThresholdCallback();
    }
    else
    {
        // Do nothing
    }
}
