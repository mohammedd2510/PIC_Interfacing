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

uint8 EEPROM_READ_VALUE =0;
int main() {
    
    Data_EEPROM_WriteByte(0X3FF ,0x33);
    Data_EEPROM_ReadByte(0x3ff,&EEPROM_READ_VALUE);
    while(1){
   
      
       
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    Std_ReturnType ret=E_NOT_OK;
    ecu_layer_initialize();
}