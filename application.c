/* 
 * File:   application.c
 * Author: Mohamed Osama
 * Description: 
 * Created on January 8, 2024, 1:34 PM
 */

#include "application.h"

void USART_TX_INT(void);
void USART_RX_INT(void);
volatile uint8 counter =0;
volatile uint8 Recieved_char =0;
int main() 
{
    mcal_layer_initialize();
    ecu_layer_initialize();
    while(1)
    { 
        
        EUSART_ASYNC_WriteByteNonBlocking('m');
        __delay_ms(1500);        
    }
        return (0);
}


void USART_TX_INT(void)
{
    uint8 counter_Str[4]={0};
    counter++;
    convert_uint8_to_string(counter,counter_Str);
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    lcd_4bit_send_string(&lcd1,counter_Str);
}
void USART_RX_INT(void)
{
  EUSART_ASYNC_ReadByteNonBlocking(&Recieved_char);
  lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
  lcd_4bit_send_char_data(&lcd1,Recieved_char);
  
}
