#include "ecu_relay.h"
/**
 * 
 * @param _relay
 * @return 
 */
Std_ReturnType relay_initialize(const relay_t *_relay){
    Std_ReturnType ret=E_OK;
    pin_config_t pin_obj={.port = _relay->relay_port,.pin = _relay->relay_pin,.direction=OUTPUT,.logic=_relay->relay_status};
    if(_relay==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_initialize(&pin_obj);
        }
    return ret;
}
/**
 * 
 * @param _relay
 * @return 
 */
Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret=E_OK;
    pin_config_t pin_obj={.port = _relay->relay_port,.pin = _relay->relay_pin,.direction=OUTPUT,.logic=_relay->relay_status};
    if(_relay==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&pin_obj,HIGH);
        }
    return ret;
}
/**
 * 
 * @param _relay
 * @return 
 */
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret=E_OK;
    pin_config_t pin_obj={.port = _relay->relay_port,.pin = _relay->relay_pin,.direction=OUTPUT,.logic=_relay->relay_status};
    if(_relay==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&pin_obj,LOW);
        }
    return ret;
}
