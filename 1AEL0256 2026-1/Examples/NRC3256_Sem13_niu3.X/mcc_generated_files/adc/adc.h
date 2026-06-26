/**
 * ADC Generated Driver API Header File
 * 
 * @file adc.h
 * 
 * @defgroup  adc ADC
 * 
 * @brief This file provides API prototypes for the ADC driver.
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

#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>
#include "./adc_types.h"

/**
 * @ingroup adc
 * @brief Defines the Custom Name pin mapping for channels in @ref adc_channel_t
 */
#define IO_RA0 ADC_CHANNEL_ANA0



/**
 * @ingroup adc
 * @brief Initializes the registers based on the configurable options in the MPLABÂ® Code Configurator (MCC) Melody UI for the Analog-to-Digital Converter (ADC) operation.
 * @param None.
 * @return None.
*/
void ADC_Initialize(void);

/**
 * @ingroup adc
 * @brief Deinitializes the registers to power-on Reset values.
 * @param None.
 * @return None.
*/
void ADC_Deinitialize(void);

/**
 * @ingroup adc
 * @brief Sets the ADC Enable (ADON) bit to `1`.
 * @param None.
 * @return None.
*/
void ADC_Enable(void);

/**
 * @ingroup adc
 * @brief Sets the ADC Enable (ADON) bit to `0`. 
 * @param None.
 * @return None.
*/
void ADC_Disable(void);

/**
 * @ingroup adc
 * @brief Sets the channel to use for the ADC conversion.
 * @param channel Desired analog channel. Refer to the @ref adc_channel_t enum for the list of available analog channels.
 * @return None.
*/
void ADC_ChannelSelect(adc_channel_t channel);

/**
 * @ingroup adc
 * @brief Starts the conversion on a selected channel. 
 * @pre Select the channel(s) using @ref ADC_ChannelSelect
 * and call @ref ADC_Initialize(void) to initialize the ADC module before using this API.
 * @param None.
 * @return None.
*/
void ADC_ConversionStart(void);

/**
 * @ingroup adc
 * @brief Checks if the ongoing conversion is complete.
 * @pre @ref ADC_ConversionStart(void) is called before using this API.
 * @param None.
 * @retval True Conversion is complete
 * @retval False Conversion is ongoing
*/
bool ADC_IsConversionDone(void);

/**
 * @ingroup adc
 * @brief Stops the ongoing conversion.
 * @param None.
 * @return None.
*/
void ADC_ConversionStop(void);

/**
 * @ingroup adc
 * @brief Retrieves the result of the latest conversion.
 * @pre Call @ref ADC_ConversionStart(void) before using this API.
 * @param None.
 * @return adc_result_t - The result of the conversion
*/
adc_result_t ADC_ConversionResultGet(void);

/**
 * @ingroup adc
 * @brief Sets the computation mode. 
 * @param computationMode Desired computation mode. Refer to the @ref adc_computation_mode_t enum for the list of available computation modes.
 * @return None.
*/
void ADC_ComputationModeSet(adc_computation_mode_t computationMode);

/**
 * @ingroup adc
 * @brief Sets the conversion threshold mode.
 * @param thresholdMode Desired threshold mode. Refer to the @ref adc_threshold_mode_t enum for the list of available threshold modes.
 * @return None.
*/
void ADC_ThresholdModeSet(adc_threshold_mode_t  thresholdMode);

/**
 * @ingroup adc
 * @brief Loads the repeat counter with the specified value.
 * @param repeatCount Repeat count value. Refer to the @ref adc_repeat_count_t type.
 * @return None.
*/
void ADC_SampleRepeatCountSet(adc_repeat_count_t repeatCount);

/**
 * @ingroup adc
 * @brief Sets the value of the ADC Upper Threshold (ADUTH) register.
 * @param upperThreshold Upper threshold value of the @ref adc_threshold_t type for the ADUTH register.
 * @return None.
*/
void ADC_UpperThresholdSet(adc_threshold_t upperThreshold); 

/**
 * @ingroup adc
 * @brief Sets the value of the ADC Lower Threshold (ADLTH) register.
 * @param lowerThreshold Lower threshold value of the @ref adc_threshold_t type for the ADLTH register
 * @return None.
*/
void ADC_LowerThresholdSet(adc_threshold_t lowerThreshold);

/**
 * @ingroup adc
 * @brief Retrieves the value of the accumulated conversions.
 * @param None.
 * @return adc_accumulate_t - Value of ADC accumulator register
*/
adc_accumulate_t ADC_AccumulatedResultGet(void);

/**
 * @ingroup adc
 * @brief Starts the conversion and retrieves the result of the single conversion on the selected channel. 
 * @param channel Desired analog channel. Refer to the @ref adc_channel_t enum for the list of available analog channels.
 * @return adc_result_t - The result of the conversion
*/
adc_result_t ADC_ChannelSelectAndConvert(adc_channel_t channel); 

/**
 * @ingroup adc
 * @brief Sets the Stop-on-Interrupt (SOI) bit to '1'.
 * @pre Call @ref ADC_ContinuousConversionEnable API before using this API.
 * @param None.
 * @return None.
*/
void ADC_StopOnInterruptEnable(void);

/**
 * @ingroup adc
 * @brief Sets the Stop-on-Interrupt (SOI) bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_StopOnInterruptDisable(void);

/**
 * @ingroup adc
 * @brief Discharges the input sample capacitor by setting the channel to AVss.
 * @param None.
 * @return None.
*/
void ADC_SampleCapacitorDischarge(void);

/**
 * @ingroup adc
 * @brief Sets the specified value for the ADC Acquisition Time Control (ADACQ) register.
 * @param acquisitionValue Value to be loaded in the ADACQ register
 * @return None.
*/
void ADC_AcquisitionTimeSet(uint16_t acquisitionValue); 

/**
 * @ingroup adc
 * @brief Sets the specified value for the ADC Precharge Time Control (ADPRE) register.
 * @param prechargeTime Value to be loaded in the ADPRE register
 * @return None.
*/
void ADC_PrechargeTimeSet(uint16_t prechargeTime);

/**
 * @ingroup adc
 * @brief Retrieves the current value of the ADC Repeat Counter (ADCNT) register.
 * @param None.
 * @return adc_repeat_count_t - Current value of the ADCNT register
*/
adc_repeat_count_t ADC_CurrentConversionCountGet(void);

/**
 * @ingroup adc
 * @brief Clears the accumulator.
 * @param None.
 * @return None.
*/
void ADC_AccumulatorClear(void);

/**
 * @ingroup adc
 * @brief Status of the accumulator clear operation.
 * @param None.
 * @retval True ADC accumulator clear operation complete
 * @retval False ADC accumulator clear operation not complete
*/
bool ADC_IsAccumulatorClearComplete(void);

/**
 * @ingroup adc
 * @brief Determines whether the accumulator has overflowed.
 * @param None.
 * @retval True ADC accumulator has overflowed
 * @retval False ADC accumulator has not overflowed
*/
bool ADC_HasAccumulatorOverflowed(void);

/**
 * @ingroup adc
 * @brief Retrieves the value of the ADC Filter (ADFLTR) register.
 * @param None.
 * @return adc_result_t - Value obtained after the ADC Accumulator (ADACC) register is right shifted by the CRS bits.
 * In Low-Pass Filter (LPF) mode, this is the output of the Low-Pass Filter.
*/
adc_result_t ADC_FilterValueGet(void);

/**
 * @ingroup adc
 * @brief Retrieves the value of the ADC Previous Result(ADPREV) register.
 * @param None.
 * @return adc_result_t - Value obtained from the ADPREV register
*/
adc_result_t ADC_PreviousResultGet(void);

/**
 * @ingroup adc
 * @brief Sets the value of the ADC Threshold Setpoint (ADSTPT) register.
 * @param setPoint Value for the ADSTPT register of the @ref adc_threshold_t type
 * @return None.
*/
void ADC_SetPointDefine(adc_threshold_t setPoint);  

/**
 * @ingroup adc
 * @brief Retrieves the value of the ADC Setpoint Error (ADERR) register.
 * @param None.
 * @return adc_result_t - Value obtained from the ADERR register
*/
adc_result_t ADC_ErrorCalculationGet(void); 

/**
 * @ingroup adc
 * @brief Sets the Double-Sample Enable (DSEN) bit to '1'.
 * @param None.
 * @return None.
*/
void ADC_DoubleSamplingEnable(void); 

/**
 * @ingroup adc
 * @brief Sets the Double-Sample Enable (DSEN) bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_DoubleSamplingDisable(void); 

/**
 * @ingroup adc
 * @brief Sets the Continuous Operation Enable (CONT) bit to '1'.
 * @param None.
 * @return None.
*/
void ADC_ContinuousConversionEnable(void); 

/**
 * @ingroup adc
 * @brief Sets the Continuous Operation Enable (CONT) bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_ContinuousConversionDisable(void);  

/**
 * @ingroup adc
 * @brief Determines if the value in the ADC Setpoint Error (ADERR) register is greater than the upper threshold. * @param None.
 * @retval True ADC error is greater than the upper threshold
 * @retval False ADC error is not greater than the upper threshold
*/
bool ADC_IsErrorGreaterThanUpperThreshold(void); 

/**
 * @ingroup adc
 * @brief Determines if the value in the ADC Setpoint Error (ADERR) register is lesser than the lower threshold.
 * @param None.
 * @retval True ADC error is less than the lower threshold
 * @retval False ADC error is not less the lower threshold
*/
bool ADC_IsErrorLesserThanLowerThreshold(void);  

/**
 * @ingroup adc
 * @brief Retrieves the conversion stage status.
 * @param None.
 * @return adc_conversion_stage_t - Stage of the conversion stages
*/
adc_conversion_stage_t ADC_ConversionStageStatusGet(void); 

/**
 * @ingroup adc
 * @brief Sets the auto-trigger source.
 * @param triggerSource Desired auto-trigger source. Refer to the @ref adc_trigger_source_t for the list of available trigger sources.
 * @return None.
*/
void ADC_AutoTriggerSourceSet(adc_trigger_source_t triggerSource);

/**
 * @ingroup adc
 * @brief Sets the ADC Error Calculation Mode Select (CALC) bits.
 * @param errorCalculationMode Desired errorCalculationMode value. Refer to the @ref adc_calculation_mode_t for the error calculation mode options.
 * @return None.
*/
void ADC_ErrorCalculationModeSet(adc_calculation_mode_t errorCalculationMode);

/**
 * @ingroup adc
 * @brief Sets the ADC Accumulated Calculation Right Shift Select (CRS) bits.
 * @param rightShiftValue Right shift value
 * @return None.
*/
void ADC_CalculationRightShiftSet(uint8_t rightShiftValue);

/**
 * @ingroup adc
 * @brief Sets the ADC Charge Pump On Control (CPON) bit to '1'.
 * @param None.
 * @return None.
*/
void ADC_ChargePumpEnable(void);

/**
 * @ingroup adc
 * @brief Sets the ADC Charge Pump On Control (CPON) bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_ChargePumpDisable(void);

/**
 * @ingroup adc
 * @brief Checks the Charge Pump Ready status.
 * @param None.
 * @retval True Charge Pump is ready
 * @retval False Charge Pump is not ready
*/
bool ADC_IsChargePumpReady(void);

/**
 * @ingroup adc
 * @brief Returns the resolution of the ADC module.
 * @param None.
 * @return uint8_t - Resolution value
*/
uint8_t ADC_ResolutionGet(void);

/**
 * @ingroup adc
 * @brief Returns the busy status of the ADC module.
 * @param None.
 * @retval True The ADC is in use
 * @retval False The ADC is not in use
*/
bool ADC_IsBusy(void);

/**
 * @ingroup adc
 * @brief Sets the busy status of the ADC module.
 * @param status True to set the ADC status to busy, false to set it to not busy.
 * @return None.
*/
void ADC_BusyStatusSet(bool status);

/**
 * @ingroup adc
 * @brief Clears the ADC Conversion Done Interrupt Flag (ADIF) bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_ConversionDoneInterruptFlagClear(void);

/**
 * @ingroup adc
 * @brief Sets the ADC Threshold Interrupt Flag (ADTIF) bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_ThresholdInterruptFlagClear(void);

/**
 * @ingroup adc
 * @brief Checks the ADC Conversion Done Interrupt Flag (ADIF) status
 * @param None.
 * @retval True ADI flag is set
 * @retval False ADI flag is not set
*/
bool ADC_IsConversionDoneInterruptFlagSet(void);

/**
 * @ingroup adc
 * @brief Checks the  ADC Threshold Interrupt (ADTIF) flag status.
 * @param None.
 * @retval True ADTI flag status is set
 * @retval False ADTI flag status is not set
*/
bool ADC_IsThresholdInterruptFlagSet(void);

/**
 * @ingroup adc
 * @brief Sets the callback function for the ADC Conversion Done Interrupt (ADI).
 * @param Pointer The pointer to the function to be executed
 * @return None.
 */
void ADC_ConversionDoneCallbackRegister(void (*callback)(void));

/**
 * @ingroup adc
 * @brief Sets the callback for the threshold interrupt.
 * @param *callback The pointer to the function to be executed
 * @return None.
 */
void ADC_ThresholdCallbackRegister(void (*callback)(void));

/**
 * @ingroup adc
 * @brief Sets the ADC Interrupt Enable (ADIE) bit to '1'.
 * @param None.
 * @return None.
*/
void ADC_ConversionDoneInterruptEnable(void);

/**
 * @ingroup adc
 * @brief Sets the ADC Interrupt Enable (ADIE) bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_ConversionDoneInterruptDisable(void);

/**
 * @ingroup adc
 * @brief Sets the ADC Threshold Interrupt Enable bit to '1'.
 * @param None.
 * @return None.
*/
void ADC_ThresholdInterruptEnable(void);

/**
 * @ingroup adc
 * @brief Sets the ADC Threshold Interrupt Enable bit to '0'.
 * @param None.
 * @return None.
*/
void ADC_ThresholdInterruptDisable(void);

/**
 * @ingroup adc
 * @brief Implements the ADC Interrupt (ADI) service routine for the interrupt-driven implementations.
 * @param None.
 * @return None.
*/
void ADC_ISR(void);

/**
 * @ingroup adc
 * @brief Implements the ADC Threshold Interrupt (ADTI) service routine for the interrupt-driven implementations.
 * @param None.
 * @return None.
*/
void ADC_ThresholdISR(void);

#endif // ADC_H
