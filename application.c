/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"
/**
 * 
 * @return 
 */
dc_motor_t Motor1={
    .dc_motor_pin[0].pin=PIN0,
    .dc_motor_pin[0].port=PORTC_INDEX,
    .dc_motor_pin[0].direction=OUTPUT,
    .dc_motor_pin[0].logic=DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].pin=PIN1,
    .dc_motor_pin[1].port=PORTC_INDEX,
    .dc_motor_pin[1].direction=OUTPUT,
    .dc_motor_pin[1].logic=DC_MOTOR_OFF_STATUS
};
dc_motor_t Motor2={
    .dc_motor_pin[0].pin=PIN2,
    .dc_motor_pin[0].port=PORTC_INDEX,
    .dc_motor_pin[0].direction=OUTPUT,
    .dc_motor_pin[0].logic=DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].pin=PIN3,
    .dc_motor_pin[1].port=PORTC_INDEX,
    .dc_motor_pin[1].direction=OUTPUT,
    .dc_motor_pin[1].logic=DC_MOTOR_OFF_STATUS
};
Std_ReturnType ret=E_NOT_OK;
int main() {
    application_initialize();
    while(1){
        dc_motor_move_right(&Motor1);
        dc_motor_move_right(&Motor2);
        __delay_ms(3000);
        dc_motor_move_left(&Motor1);
        dc_motor_move_left(&Motor2);
        __delay_ms(3000);
         dc_motor_stop(&Motor1);
        dc_motor_stop(&Motor2);
        __delay_ms(3000);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    ret=dc_motor_initialize(&Motor1);
     ret=dc_motor_initialize(&Motor2);
}
