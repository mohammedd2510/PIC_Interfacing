#include "ecu_led.h"
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret=E_OK;
    pin_config_t pin_obj={.port = led->port_name,.pin = led->pin,.direction=OUTPUT,.logic=led->led_status };
    if(led==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_initialize(&pin_obj);
        }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_on(const led_t *led){
     Std_ReturnType ret=E_OK;
    pin_config_t pin_obj={.port = led->port_name,.pin = led->pin,.direction=OUTPUT,.logic=led->led_status };
    if(led==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&pin_obj,HIGH);
        }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_off(const led_t *led){
     Std_ReturnType ret=E_OK;
    pin_config_t pin_obj={.port = led->port_name,.pin = led->pin,.direction=OUTPUT,.logic=led->led_status };
    if(led==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&pin_obj,LOW);
        }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_toggle(const led_t *led){
    Std_ReturnType ret=E_OK;
    pin_config_t pin_obj={.port = led->port_name,.pin = led->pin,.direction=OUTPUT,.logic=led->led_status };
    if(led==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_toggle_logic(&pin_obj);
        }
    return ret;
}