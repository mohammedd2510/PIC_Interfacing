/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/button/ecu_button.h"
/**
 * 
 * @return 
 */
led_t led1={
    .port_name=PORTC_INDEX,
    .pin=PIN0,
    .led_status=LED_OFF
};
button_t btn1={
    .button_pin.port=PORTD_INDEX,
    .button_pin.pin=PIN0,
    .button_pin.direction=INPUT,
    .button_connection=BUTTON_ACTIVE_HIGH,
    .button_state=BUTTON_RELEASED
};
Std_ReturnType ret=E_NOT_OK;
button_state_t btn1_state;
button_state_t btn1_state2;
int main() {
    application_initialize();
    while(1){
        uint32 counter1,counter2;
        for(counter1=0,btn1_state2=BUTTON_RELEASED;counter1<3000;counter1++){
           button_read_state(&btn1,&btn1_state);
           if(btn1_state==BUTTON_PRESSED){
               counter2++;
           }
           if(counter2>1020){
               counter2=0;
               btn1_state2=BUTTON_PRESSED;
               break;
           }
        }
        
        if(btn1_state2==BUTTON_PRESSED)
        led_toggle(&led1);
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    ret=led_initialize(&led1);
    ret=button_initialize(&btn1);
}
