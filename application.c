/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/button/ecu_button.h"
#include"ECU_Layer/Relay/ecu_relay.h"
/**
 * 
 * @return 
 */
relay_t relay1={
    .relay_port=PORTC_INDEX,
    .relay_pin=PIN0,
    .relay_status=RELAY_OFF_STATUS
};

Std_ReturnType ret=E_NOT_OK;
int main() {
    application_initialize();
    while(1){
        relay_turn_on(&relay1);
        __delay_ms(5000);
        relay_turn_off(&relay1);
        __delay_ms(5000);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    ret=relay_initialize(&relay1);
}
