#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROW][ECU_KEYPAD_COLUMNS]={
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'#','0','=','+'}
};

/**
 * 
 * @param keypad_obj
 * @return 
 */
Std_ReturnType keypad_initialize(const keypad_t * keypad_obj){
     Std_ReturnType ret=E_OK;
     uint8 rows_counter=ZERO_INIT , columns_counter=ZERO_INIT; 
    if(keypad_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        for(rows_counter=ZERO_INIT;rows_counter<ECU_KEYPAD_ROW;rows_counter++){
             ret=gpio_pin_initialize(&(keypad_obj->keypad_row_pins[rows_counter]));
        } 
        for(columns_counter=ZERO_INIT;columns_counter<ECU_KEYPAD_COLUMNS;columns_counter++){
             ret=gpio_pin_direction_initialize(&(keypad_obj->keypad_columns_pins[columns_counter]));
        }
        }
    return ret;
}
/**
 * 
 * @param keypad_obj
 * @param value
 * @return 
 */
Std_ReturnType keypad_get_value(const keypad_t * keypad_obj , uint8 * value){
     Std_ReturnType ret=E_OK;
      uint8 l_rows_counter=ZERO_INIT , l_columns_counter=ZERO_INIT ,l_counter=ZERO_INIT;
      uint8 column_logic=ZERO_INIT;
    if((keypad_obj==NULL)||(value==NULL)){
        ret=E_NOT_OK;
    }
    else{
           for(l_rows_counter=ZERO_INIT;l_rows_counter<ECU_KEYPAD_ROW;l_rows_counter++){
               for(l_counter=ZERO_INIT;l_counter<ECU_KEYPAD_ROW;l_counter++){
                   ret=gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[l_counter]),LOW);
               }
             ret=gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[l_rows_counter]),HIGH);
             __delay_ms(10);
        for(l_columns_counter=ZERO_INIT;l_columns_counter<ECU_KEYPAD_COLUMNS;l_columns_counter++){
            ret=gpio_pin_read_logic(&(keypad_obj->keypad_columns_pins[l_columns_counter]),&column_logic);
            if(column_logic==HIGH){*value=btn_values[l_rows_counter][l_columns_counter];}
        }
           }
        }
    return ret;
}
