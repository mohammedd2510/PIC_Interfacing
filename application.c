/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"
#include "ECU_Layer/LED/ecu_led.h"
/**
 * 
 * @return 
 */
led_t led1={
    .port_name=PORTC_INDEX,
    .pin=PIN0,
    .led_status=LED_OFF
};
Std_ReturnType ret=E_NOT_OK;
int main() {
    application_initialize();
    while(1){
        led_toggle(&led1);
        __delay_ms(500);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    ret=led_initialize(&led1);
}
