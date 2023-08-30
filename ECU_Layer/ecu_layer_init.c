#include "ecu_layer_init.h"

keypad_t keypad1={
    .keypad_row_pins[0].pin=PIN0,
    .keypad_row_pins[0].port=PORTC_INDEX,
    .keypad_row_pins[0].direction=OUTPUT,
    .keypad_row_pins[0].logic=LOW,
    .keypad_row_pins[1].pin=PIN1,
    .keypad_row_pins[1].port=PORTC_INDEX,
    .keypad_row_pins[1].direction=OUTPUT,
    .keypad_row_pins[1].logic=LOW,
    .keypad_row_pins[2].pin=PIN2,
    .keypad_row_pins[2].port=PORTC_INDEX,
    .keypad_row_pins[2].direction=OUTPUT,
    .keypad_row_pins[2].logic=LOW,
    .keypad_row_pins[3].pin=PIN3,
    .keypad_row_pins[3].port=PORTC_INDEX,
    .keypad_row_pins[3].direction=OUTPUT,
    .keypad_row_pins[3].logic=LOW,
    .keypad_columns_pins[0].pin=PIN4,
    .keypad_columns_pins[0].port=PORTC_INDEX,
    .keypad_columns_pins[0].direction=INPUT,
    .keypad_columns_pins[0].logic=LOW,
    .keypad_columns_pins[1].pin=PIN5,
    .keypad_columns_pins[1].port=PORTC_INDEX,
    .keypad_columns_pins[1].direction=INPUT,
    .keypad_columns_pins[1].logic=LOW,
    .keypad_columns_pins[2].pin=PIN6,
    .keypad_columns_pins[2].port=PORTC_INDEX,
    .keypad_columns_pins[2].direction=INPUT,
    .keypad_columns_pins[2].logic=LOW,
    .keypad_columns_pins[3].pin=PIN7,
    .keypad_columns_pins[3].port=PORTC_INDEX,
    .keypad_columns_pins[3].direction=INPUT,
    .keypad_columns_pins[3].logic=LOW
};

led_t led1 = {
    .port_name=PORTD_INDEX,
    .pin=PIN0,
    .led_status=LOW
};
void ecu_layer_initialize(void){
     Std_ReturnType ret=E_NOT_OK;
    ret=keypad_initialize(&keypad1);
    ret=led_initialize(&led1);
}
