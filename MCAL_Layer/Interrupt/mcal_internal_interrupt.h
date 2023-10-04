/* 
 * File:   mcal_internal_interrupt.h
 * Author: Mohamed Osama
 *
 * Created on September 12, 2023, 12:35 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes */

#include "mcal_interrupt_config.h"
#include "../ADC/hal_adc.h"
/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */
#if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)

/* This routing clears the interrupt enable for the ADC Module */
#define ADC_InterruptDisable() (PIE1_bits.ADIE=0)
/* This routing sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable() (PIE1_bits.ADIE=1)
/* This routing clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear() (PIR1_bits.ADIF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
/* This routing sets the ADC MODULE interrupt priority to be High priority */
#define ADC_HighPrioritySet() (IPR1_bits.ADIP=1)
/* This routing sets the ADC MODULE interrupt priority to be Low priority */
#define ADC_LowPrioritySet() (IPR1_bits.ADIP=0)
#endif

#endif


/* Section : Data Types Declaration */


/* Section : Functions Declaration */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

