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
pin_config_t led1={
        .port=PORTC_INDEX,
        .pin=PIN0,
        .direction=OUTPUT,
        .logic=HIGH
    };
pin_config_t led2={
        .port=PORTC_INDEX,
        .pin=PIN1,
        .direction=OUTPUT,
        .logic=HIGH
    };
pin_config_t led3={
        .port=PORTC_INDEX,
        .pin=PIN2,
        .direction=OUTPUT,
        .logic=HIGH
    };
pin_config_t btn_1={
    .port=PORTD_INDEX,
        .pin=PIN0,
        .direction=INPUT,
        .logic=LOW
};

 Std_ReturnType ret=E_NOT_OK;
 direction_t led1_st;
 logic_t btn1_st;
 uint8 port_dir=0;
  uint8 port_log=0;
int main() {
    application_initialize();
    while(1){
        ret=gpio_port_toggle_logic(PORTC_INDEX);
        __delay_ms(500);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
  ret=gpio_port_direction_initialize(PORTC_INDEX,0x55);
  ret=gpio_port_get_direction_status(PORTC_INDEX,&port_dir);
  ret=gpio_port_write_logic(PORTC_INDEX,0xff);
  ret=gpio_port_read_logic(PORTC_INDEX,&port_log);
}
