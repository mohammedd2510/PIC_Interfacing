/* 
 * File:   application.h
 * Author: mohop
 *
 * Created on August 15, 2023, 1:34 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include"ECU_Layer/ecu_layer_init.h"

#include "MCAL_Layer/Timer1/hal_timer1.h"

/* Section : Includes */


/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */


/* Section : Functions Declaration */
void application_initialize(void);
void TMR0_ISR_HANDLER(void);

#endif	/* APPLICATION_H */

