/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"



Std_ReturnType ret=E_NOT_OK;
void Timer2_30ms_Init(void);
void Timer1_Counter_Init(void);
timer2_t timer_obj;
timer1_t counter_obj;
uint8 Counter_Val =ZERO_INIT;
int main() 
{
    application_initialize();
    while(1)
    {
        
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
   Timer2_30ms_Init();
 
   
}

void TMR2_ISR_HANDLER(void){
    led_toggle(&led1);
}
void Timer2_30ms_Init(void){
    timer_obj.TMR2_InterruptHandler = TMR2_ISR_HANDLER;
    timer_obj.priority = INTERRUPT_PRIORITY_HIGH;
    timer_obj.prescaler_value = TIMER2_PRESCALER_DIV_BY_16;
    timer_obj.postscaler_value = TIMER2_POSTSCALER_DIV_BY_15;
    timer_obj.timer2_preload_value =250;
    ret=Timer2_Init(&timer_obj);
}
void Timer1_Counter_Init(void){
    counter_obj.TMR1_InterruptHandler = NULL;
    counter_obj.prescaler_value = TIMER1_PRESCALER_DIV_BY_1;
    counter_obj.priority = INTERRUPT_PRIORITY_HIGH;
    counter_obj.timer1_mode = TIMER1_COUNTER_MODE;
    counter_obj.timer1_preload_value = 0;
    counter_obj.timer1_counter_mode = TIMER1_SYNC_COUNTER_MODE;
    ret = Timer1_Init(&counter_obj);
}