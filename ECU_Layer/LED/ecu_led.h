/* 
 * File:   ecu_led.h
 * Author: mohop
 *
 * Created on August 15, 2023, 1:30 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */
typedef enum{
  LED_OFF = 0,
  LED_ON
}led_status_t;

typedef struct{
uint8 port_name:4;
uint8 pin:3;
uint8 led_status:1;
}led_t;

/* Section : Functions Declaration */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);
#endif	/* ECU_LED_H */

