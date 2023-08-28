#include "ecu_dc_motor.h"
/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_initialize (const dc_motor_t *_dc_motor){
    Std_ReturnType ret=E_OK;
    if(_dc_motor==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        ret=gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
        }
    return ret;
}
/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_right (const dc_motor_t *_dc_motor){
    Std_ReturnType ret=E_OK;
    if(_dc_motor==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),HIGH);
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),LOW);
        }
    return ret;
}
/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_left (const dc_motor_t *_dc_motor){
    Std_ReturnType ret=E_OK;
    if(_dc_motor==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),LOW);
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),HIGH);
        }
      return ret;
}
/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_stop (const dc_motor_t *_dc_motor){
    Std_ReturnType ret=E_OK;
    if(_dc_motor==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),LOW);
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),LOW);
        }
      return ret;
}