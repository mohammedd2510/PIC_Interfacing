/* 
 * File:   application.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 9:03 AM
 */

#include "application.h"

uint16 lm35_res_1, lm35_res_2, lm35_res_1_Celsius_mv = 0, lm35_res_2_Celsius_mv = 0;
uint8 lm35_res_1_txt[7], lm35_res_2_txt[7];
uint8 ADC_Flag=0;
Std_ReturnType ret=E_NOT_OK;
int main() 
{
    application_initialize();
    ret = lcd_4bit_send_string_pos(&lcd1,1,6,"LM35 Test");
    __delay_ms(1400);
    ret&= lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    ret &= lcd_4bit_send_string_pos(&lcd1,1,1," Temp1 : ");
    ret &= lcd_4bit_send_string_pos(&lcd1,2,1," Temp2 : ");
    while(1)
    {
        if (ADC_Flag == 0){
          ret &= ADC_StartConversion_Interrupt(&adc_1,ADC_CHANNEL_AN0);   
        }
       if (ADC_Flag == 1){
            ret &= ADC_StartConversion_Interrupt(&adc_1,ADC_CHANNEL_AN1);
       }
       lm35_res_1_Celsius_mv = (lm35_res_1 *4.88f)/10;
       lm35_res_2_Celsius_mv = (lm35_res_2 *4.88f)/10;
       ret&=convert_uint16_to_string(lm35_res_1_Celsius_mv , lm35_res_1_txt);
       ret&=convert_uint16_to_string(lm35_res_2_Celsius_mv , lm35_res_2_txt);
       ret &= lcd_4bit_send_string_pos(&lcd1,1,10,lm35_res_1_txt);
       ret &= lcd_4bit_send_string_pos(&lcd1,2,10,lm35_res_2_txt);
       if(lm35_res_1_Celsius_mv > 20){
           ret&= dc_motor_move_right(&dc_motor_1);
       }
       else {
            ret&= dc_motor_stop(&dc_motor_1);
       }
       if(lm35_res_2_Celsius_mv > 25){
           ret&= dc_motor_move_left(&dc_motor_2);
       }
       else {
            ret&= dc_motor_stop(&dc_motor_2);
       }
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
    ret=ADC_Init(&adc_1);
}
adc_conf_t adc_1 = {
    .ADC_InterruptHandler=ADC_ISR_HANDLER,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};
void ADC_ISR_HANDLER(void){
       if (ADC_Flag == 1){
           ADC_Flag = 0;
           ADC_GetConversionResult(&adc_1,&lm35_res_2);
       }
       else if (ADC_Flag == 0){    
           ADC_Flag=1;
           ADC_GetConversionResult(&adc_1,&lm35_res_1);
       }
}