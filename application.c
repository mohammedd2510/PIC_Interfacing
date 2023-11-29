/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"



Std_ReturnType ret=E_NOT_OK;
void Timer3_Timer_Init(void);
void Timer3_Counter_Init(void);
timer3_t timer_obj;
timer3_t counter_obj;
uint8 Counter_Val =ZERO_INIT;
int main() 
{
    application_initialize();
    while(1)
    {
        Timer3_Read_Value(&counter_obj,&Counter_Val);
        lcd_4bit_send_string_pos(&lcd1,1,1,"Counter =  ");
        lcd_4bit_send_char_data_pos(&lcd1,1,11,(Counter_Val+0x30));
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
    //Timer3_Timer_Init();
    Timer3_Counter_Init();
   
}

void TMR3_ISR_HANDLER(void){
    led_toggle(&led1);
}
void Timer3_Timer_Init(void){
    timer_obj.TMR3_InterruptHandler = TMR3_ISR_HANDLER;
    timer_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer_obj.priority = INTERRUPT_PRIORITY_HIGH;
    timer_obj.prescaler_value = TIMER3_PRESCALER_DIV_BY_8;
    timer_obj.timer3_preload_value =28036;
    ret=Timer3_Init(&timer_obj);
}
void Timer3_Counter_Init(void){
    counter_obj.TMR3_InterruptHandler = NULL;
    counter_obj.prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    counter_obj.priority = INTERRUPT_PRIORITY_HIGH;
    counter_obj.timer3_mode = TIMER3_COUNTER_MODE;
    counter_obj.timer3_preload_value = 0;
    counter_obj.timer3_counter_mode = TIMER3_SYNC_COUNTER_MODE;
    ret = Timer3_Init(&counter_obj);
}