/* 
 * File:   ecu_keypad.h
 * Author: Mohamed Osama
 *
 * Created on August 30, 2023, 12:31 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macros Declaration */
#define ECU_KEYPAD_ROW 4
#define ECU_KEYPAD_COLUMNS 4

/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */
typedef struct {
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROW];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* Section : Functions Declaration */
Std_ReturnType keypad_initialize(const keypad_t * keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t * keypad_obj , uint8 * value);

#endif	/* ECU_KEYPAD_H */

