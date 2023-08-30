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

uint8 keypad_value=ZERO_INIT;
Std_ReturnType ret=E_NOT_OK;
int main() {
    ecu_layer_initialize();
 
    while(1){
        ret=keypad_get_value(&keypad1,&keypad_value);
        if(keypad_value=='7'){
            led_turn_on(&led1);
        }
        else if (keypad_value=='8'){
            led_turn_off(&led1);
        }
        else {}
    }
    return (EXIT_SUCCESS);
}
