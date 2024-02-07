/* 
 * File:   application.c
 * Author: Mohamed Osama
 * Description: 
 * Created on January 8, 2024, 1:34 PM
 */

#include "application.h"

volatile uint8 Data =0;
int main() 
{
    mcal_layer_initialize();
    ecu_layer_initialize();
    while(1)
    {   
       /* SPI_Master_Transmit_Blocking('1',&SS1_Pin);
        __delay_ms(1000);
      SPI_Master_Transmit_Blocking('2',&SS2_Pin);
        __delay_ms(1000);
       SPI_Master_Transmit_Blocking('3',&SS1_Pin);
        __delay_ms(1000);
        SPI_Master_Transmit_Blocking('4',&SS2_Pin);
        __delay_ms(1000);
        */
        if(SPI_SLAVE_STATUS_RECEIEVD_DATA == SPI_Slave_Receive_Status){
            SPI_Slave_Receive_Status =SPI_SLAVE_STATUS_RESET;
            lcd_4bit_send_char_data(&lcd1,Data);
        }
    }
        return (0);
}
void SPI_ISR(void)
{
  SPI_Slave_Receive_Non_Blocking(&Data);  
}


