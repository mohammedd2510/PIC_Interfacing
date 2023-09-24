#include "hal_eeprom.h"

static void EEPROM_UPDATE_ADDRESS_REG(uint16 ADD);
static void EEPROM_UPDATE_DATA_REG(uint8 DATA);
static void EEPROM_READ_DATA_REG(uint8 *DATA);
static void EEPROM_READ_GLOBAL_INTERRUPT_STATUS(uint8*Global_Interrupt_Status);
static void EEPROM_RESTORE_GLOBAL_INTERRUPT_STATUS(uint8*Global_Interrupt_Status);
/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd ,uint8 bData){
    uint8 Global_Interrupt_Status=0;
    Std_ReturnType ret=E_OK;
   /*Read the Global Interrupt Status "Enabled or Disabled " */
    EEPROM_READ_GLOBAL_INTERRUPT_STATUS(&Global_Interrupt_Status);
    /*Update The Address Registers*/
    EEPROM_UPDATE_ADDRESS_REG(bAdd);
    /*Update Data Register*/
    EEPROM_UPDATE_DATA_REG(bData);
    /*Select Access Data EEPROM Memory*/
    EEPROM_SELECT_ACCESS_DATA();
    /*Allow Write Cycle for EEPROM*/
    EEPROM_WRITE_ENABLE();
    /*Disable General interrupts */
    EEPROM_WRITE_GlobalInterruputDisable();
    /*Write the required sequence for write*/
    EEPROM_WRITE_SEQUENCE();
    /*Initiate Data EEPROM Write Cycle*/
    EEPROM_INITIATE_WRITE_ERASE();
    /*Wait For Write To Complete*/
    EEPROM_WAIT_FOR_WRITE_COMPLETE();
    /*Inhibit write cycle*/
    EEPROM_WRITE_DISABLE();
    /*Restore The Global Interrupt Status*/
    EEPROM_RESTORE_GLOBAL_INTERRUPT_STATUS(&Global_Interrupt_Status);
    return ret;
}
/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd ,uint8 *bData){
    Std_ReturnType ret=E_OK;
    if(bData==NULL){
        ret=E_NOT_OK;
    }
    else{
   /* Update The Address Registers */
    EEPROM_UPDATE_ADDRESS_REG(bAdd);
    /* Select Access Data EEPROM Memory */
    EEPROM_SELECT_ACCESS_DATA();
    /* Initiate Data EEPROM READ CYCLE */
    EEPROM_INITIATE_READ_CYCLE();
    /* NOP For 2 Cycles */
    EEPROM_NOP_2_CYCLES();
    /* Return Data */
    EEPROM_READ_DATA_REG(bData);
        }
    return ret; 
}
static void EEPROM_UPDATE_ADDRESS_REG(uint16 ADD){
    EEADRH = (uint8)((ADD>>8)&(0x03));
    EEADR = (uint8)(ADD &(0xFF)); 
}
static void EEPROM_UPDATE_DATA_REG(uint8 DATA){
    EEDATA =DATA;
}
static void EEPROM_READ_GLOBAL_INTERRUPT_STATUS(uint8*Global_Interrupt_Status){
    *Global_Interrupt_Status = INTCON_bits.GIE ;
}
static void EEPROM_RESTORE_GLOBAL_INTERRUPT_STATUS(uint8*Global_Interrupt_Status){
    INTCON_bits.GIE = *Global_Interrupt_Status;
}
static void EEPROM_READ_DATA_REG(uint8 *DATA){
    *DATA = EEDATA;
}