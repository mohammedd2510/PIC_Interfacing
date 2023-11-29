/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"



Std_ReturnType ret=E_NOT_OK;
void Timer1_Timer_Init(void);
void Timer1_Counter_Init(void);
timer1_t timer_obj;
timer1_t counter_obj;
uint8 Counter_Val =ZERO_INIT;
int main() 
{
    application_initialize();
    while(1)
    {
        Timer1_Read_Value(&counter_obj,&Counter_Val);
        lcd_4bit_send_string_pos(&lcd1,1,1,"Counter =  ");
        lcd_4bit_send_char_data_pos(&lcd1,1,11,(Counter_Val+0x30));
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
  //  Timer1_Timer_Init();
    Timer1_Counter_Init();
   
}

void TMR1_ISR_HANDLER(void){
    led_toggle(&led1);
}
void Timer1_Timer_Init(void){
    timer_obj.TMR1_InterruptHandler = TMR1_ISR_HANDLER;
    timer_obj.priority = INTERRUPT_PRIORITY_HIGH;
    timer_obj.prescaler_value = TIMER1_PRESCALER_DIV_BY_8;
    timer_obj.timer1_mode = TIMER1_TIMER_MODE;
    timer_obj.timer1_osc_cfg = TIMER1_OSCILLATOR_DISABLE;
    timer_obj.timer1_preload_value =15536;
    ret=Timer1_Init(&timer_obj);
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