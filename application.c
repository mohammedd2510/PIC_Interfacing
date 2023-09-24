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
void RB4_INT_HANDLER (void){
    led_toggle(&led1);
} 
void RB5_INT_HANDLER (void){
    led_toggle(&led2);
} 
void RB6_INT_HANDLER (void){
    led_toggle(&led3);
} 
void RB7_INT_HANDLER (void){
    led_toggle(&led4);
} 

Std_ReturnType ret=E_NOT_OK;


interrupt_RBx_t RB4_INT = {
    .mcu_pin.port=PORTB_INDEX ,
    .mcu_pin.pin=PIN4,
    .mcu_pin.direction = INPUT ,
    .EXT_InterruptHandler = RB4_INT_HANDLER,
    .RBx_Pin_init_value=0,
};
interrupt_RBx_t RB5_INT = {
    .mcu_pin.port=PORTB_INDEX ,
    .mcu_pin.pin=PIN5,
    .mcu_pin.direction = INPUT ,
    .EXT_InterruptHandler = RB5_INT_HANDLER,
    .RBx_Pin_init_value=0,
};
interrupt_RBx_t RB6_INT = {
    .mcu_pin.port=PORTB_INDEX ,
    .mcu_pin.pin=PIN6,
    .mcu_pin.direction = INPUT ,
    .EXT_InterruptHandler = RB6_INT_HANDLER,
    .RBx_Pin_init_value=0,
};
interrupt_RBx_t RB7_INT = {
    .mcu_pin.port=PORTB_INDEX ,
    .mcu_pin.pin=PIN7,
    .mcu_pin.direction = INPUT ,
    .EXT_InterruptHandler = RB7_INT_HANDLER,
    .RBx_Pin_init_value=0,
};
int main() {
    application_initialize();
    Interrupt_RBx_Init(&RB4_INT);
    Interrupt_RBx_Init(&RB5_INT);
    Interrupt_RBx_Init(&RB6_INT);
    Interrupt_RBx_Init(&RB7_INT);
    while(1){
   
        
        
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
}