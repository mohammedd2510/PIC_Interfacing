#include "ecu_button.h"
/**
 * 
 * @param btn
 * @return 
 */
Std_ReturnType button_initialize(const button_t *btn){
     Std_ReturnType ret=E_OK;
    if(btn==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_direction_initialize(&btn->button_pin);
        }
    return ret;
}
/**
 * 
 * @param btn
 * @param btn_state
 * @return 
 */
Std_ReturnType button_read_state(const button_t *btn,button_state_t *btn_state){
     Std_ReturnType ret=E_OK;
     logic_t logic_status=LOW;
    if((btn==NULL)||(btn_state==NULL)){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_read_logic(&btn->button_pin,&logic_status);
        if(btn->button_connection==BUTTON_ACTIVE_HIGH){
            if(logic_status==HIGH){
                *btn_state=BUTTON_PRESSED;
            }
            else *btn_state=BUTTON_RELEASED;
        }
        else if (btn->button_connection==BUTTON_ACTIVE_LOW){
             if(logic_status==LOW){
                *btn_state=BUTTON_PRESSED;
            }
            else *btn_state=BUTTON_RELEASED;
        }
        else {/*nothing*/}
        }
    return ret;
}
