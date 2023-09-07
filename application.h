/* 
 * File:   application.h
 * Author: mohop
 *
 * Created on August 15, 2023, 1:34 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "ECU_Layer/KeyPad/ecu_keypad.h"
#include"ECU_Layer/ecu_layer_init.h"

/* Section : Includes */


/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */
extern chr_lcd_4bit_t lcd1;
extern chr_lcd_8bit_t lcd_2;
/* Section : Functions Declaration */
void application_initialize(void);


#endif	/* APPLICATION_H */

