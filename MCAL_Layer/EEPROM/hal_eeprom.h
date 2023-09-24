/* 
 * File:   hal_eeprom.h
 * Author: Mohamed Osama
 *
 * Created on September 24, 2023, 3:02 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section : Includes */
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/my_pic18f4620.h"
#include "../Interrupt/mcal_interrupt_config.h"
/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */
#define EEPROM_SELECT_ACCESS_DATA() EECON1_bits.EEPGD = 0;EECON1_bits.CFGS = 0
#define EEPROM_WRITE_ENABLE() EECON1_bits.WREN=1

#define EEPROM_WRITE_GlobalInterruputDisable() (INTCON_bits.GIE = 0)

#define EEPROM_WRITE_SEQUENCE() EECON2=0X55;EECON2=0xAA

#define EEPROM_INITIATE_WRITE_ERASE() EECON1_bits.WR=1

#define EEPROM_WAIT_FOR_WRITE_COMPLETE() while(EECON1_bits.WR)

#define EEPROM_WRITE_DISABLE() EECON1_bits.WREN=0

#define EEPROM_INITIATE_READ_CYCLE() EECON1_bits.RD=1

#define EEPROM_NOP_2_CYCLES() __asm("NOP");__asm("NOP")

/* Section : Data Types Declaration */


/* Section : Functions Declaration */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd ,uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd ,uint8 *bData);

#endif	/* HAL_EEPROM_H */

