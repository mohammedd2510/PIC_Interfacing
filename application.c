/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"
#include "MCAL_Layer/Timer/hal_timer0.h"

Std_ReturnType ret=E_NOT_OK;
uint16 tmr0_Read=0;
int main() 
{
    application_initialize();
    while(1)
    {
        Timer0_Read_Value(&tmr0_timer , &tmr0_Read);
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
    ret= Timer0_Init(&tmr0_timer) ;
}
timer0_t tmr0_timer = {
    .TMR0_InterruptHandler = TMR0_ISR_HANDLER,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .prescaler_enable = TIMER0_PRESCALER_DISABLE_CFG,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .timer0_mode = TIMER0_COUNTER_MODE,
    .timer0_preload_value =0,
    .timer0_counter_edge = TIMER0_RISING_EDGE_CFG
};
void TMR0_ISR_HANDLER(void){
    lcd_4bit_send_string(&lcd1 ,"m");
}