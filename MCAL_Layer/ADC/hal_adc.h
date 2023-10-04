/* 
 * File:   hal_adc.h
 * Author: Mohamed Osama
 *
 * Created on September 28, 2023, 2:57 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : Includes */
#include "hal_adc_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/my_pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* Section : Macros Declaration */

/**
 * @brief Analog-To-Digital Port Configuration Control
 * @note  When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN4,AN3,AN2,AN1,AN0 are Analog Functionality
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY 0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY 0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY 0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY 0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY 0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY 0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY 0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY 0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY 0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY 0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY 0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0x0F

#define ADC_RESULT_RIGHT 0X01U
#define ADC_RESULT_LEFT 0X00U

#define ADC_VOLTAGE_REFERENCE_ENABLED 0X01U
#define ADC_VOLTAGE_REFERENCE_DISABLED 0X00U



/* Section : Macro Functions Declaration */

/* A/D Conversion Status : A/D Conversion in progress / A/D Idle */
#define ADC_CONVERSION_STATUS() (ADCON0_bits.GO_DONE)

/**
 * @brief Start The Analog-To-Digital Conversion
 */
#define ADC_START_CONVERSION() (ADCON0_bits.GO_DONE=1)

/**
 * @brief Analog-To-Digital Control
 * @note ADC_CONVERTER_ENABLE() : Enable The Analog-To-Digital-Converter
 *       ADC_CONVERTER_DISABLE() : Disable The Analog-To-Digital-Converter
 */
#define ADC_CONVERTER_ENABLE() (ADCON0_bits.ADON=1)
#define ADC_CONVERTER_DISABLE() (ADCON0_bits.ADON=0)

/**
 * @brief Voltage Reference Configuration
 * @note ADC_ENABLE_VOLTAGE_REFERENCE() : Voltage Reference is VREF- & VREF+
 *       ADC_DISABLE_VOLTAGE_REFERENCE() : Voltage Reference is VSS & VDD
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE() (ADCON1_bits.VCFG=3)
#define ADC_DISABLE_VOLTAGE_REFERENCE() (ADCON1_bits.VCFG=0)

/**
 * @brief Analog-To-Digital Port Configuration Control
 * @note  Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
 *        When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN4,AN3,AN2,AN1,AN0 are Analog Functionality
 *        @ref Analog-To-Digital Port Configuration Control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1_bits.PCFG=_CONFIG)

/**
 * @brief A/D Result Format Select
 */
#define ADC_RESULT_RIGHT_FORMAT() (ADCON2_bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT() (ADCON2_bits.ADFM = 0)


#define ADC_ACQUISITION_TIME_CONFIG ADCON2_bits.ACQT
#define ADC_CONVERSION_CLOCK_CONFIG ADCON2_bits.ADCS

#define ADC_CHANNEL_SELECT_CONFIG ADCON0_bits.CHS

#define BLOCK_UNTIL_CONVERSION_COMPLETED() while(ADCON0_bits.GO_DONE)

/* Section : Data Types Declaration */

#if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
extern InterruptHandler ADC_InterruptHandler;
#endif

/**
 * @brief Analog Channel Select
 * 
 */
typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,            
}adc_channel_select_t;

/**
 * @brief A/D Acquisition Time Select
 * @note  Acquisition Time (Sampling Time) is the time required for the (ADC) to 
 *        capture the input voltage during sampling
 * @note  Acquisition Time of a successive Approximation Register (SAR) ADC is The amount of time
 *        required to charge the holding capacitor (CHOLD) on the front end of the ADC
 */
typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,  
    ADC_20_TAD    
}adc_acquisition_time_t;

/**
 * @brief A/D Conversion Clock Select
 * @note  If the A/D FRC clock source is selected , a delay of one TCY (instruction cycle)
 *        is added before the A/D clock starts
 * @note  This allows the SLEEP instruction to be executed before starting the conversion
 */
typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64   
}adc_conversion_clock_t;

typedef struct {
    #if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        void(*ADC_InterruptHandler)(void);
        #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE )
        interrupt_priority_cfg priority;
        #endif
    #endif
    adc_acquisition_time_t acquisition_time; /*@ref adc_acquisition_time_t */
    adc_conversion_clock_t conversion_clock; /*@ref  adc_conversion_clock_t */
    adc_channel_select_t adc_channel;        /*@ref  adc_channel_select_t */
    uint8 voltage_reference : 1;             /* Voltage Reference Configurations */
    uint8 result_format : 1;                 /* A/D Result Format Select */
    uint8               :6;
}adc_conf_t;

typedef uint16 adc_result_t;

/* Section : Functions Declaration */
Std_ReturnType ADC_Init(const adc_conf_t *_adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, adc_result_t *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel ,adc_result_t *conversion_result );
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel);


#endif	/* HAL_ADC_H */

