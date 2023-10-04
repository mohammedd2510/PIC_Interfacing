/* 
 * File:   application.h
 * Author: mohop
 *
 * Created on August 15, 2023, 1:34 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include"ECU_Layer/ecu_layer_init.h"

#include "MCAL_Layer/ADC/hal_adc.h"

#include "MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
/* Section : Includes */


/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */
adc_conf_t adc_1;

/* Section : Functions Declaration */
void application_initialize(void);
void ADC_ISR_HANDLER(void);

#endif	/* APPLICATION_H */

