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


Std_ReturnType ret=E_NOT_OK;
uint32 counter_txt[4];
uint32 counter=ZERO_INIT;

uint8 custom_char1[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};
uint8 custom_char2[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x00
};
uint8 custom_char3[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
uint8 custom_char4[] = {
  0x0E,
  0x0A,
  0x11,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
uint8 custom_char5[] = {
  0x0E,
  0x0A,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
uint8 custom_char6[] = {
  0x0E,
  0x0E,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
int main() {
    application_initialize();
     
  
    while(1){
        lcd_4bit_send_custom_char(&lcd1,1,20,custom_char1,0);__delay_ms(250);
        lcd_4bit_send_custom_char(&lcd1,1,20,custom_char2,0);__delay_ms(250);
        lcd_4bit_send_custom_char(&lcd1,1,20,custom_char3,0);__delay_ms(250);
        lcd_4bit_send_custom_char(&lcd1,1,20,custom_char4,0);__delay_ms(250);
        lcd_4bit_send_custom_char(&lcd1,1,20,custom_char5,0);__delay_ms(250);
        lcd_4bit_send_custom_char(&lcd1,1,20,custom_char6,0);__delay_ms(250);
        lcd_8bit_send_custom_char(&lcd_2,1,20,custom_char1,0);__delay_ms(250);
        lcd_8bit_send_custom_char(&lcd_2,1,20,custom_char2,0);__delay_ms(250);
        lcd_8bit_send_custom_char(&lcd_2,1,20,custom_char3,0);__delay_ms(250);
        lcd_8bit_send_custom_char(&lcd_2,1,20,custom_char4,0);__delay_ms(250);
        lcd_8bit_send_custom_char(&lcd_2,1,20,custom_char5,0);__delay_ms(250);
        lcd_8bit_send_custom_char(&lcd_2,1,20,custom_char6,0);__delay_ms(250);
        
        
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
}