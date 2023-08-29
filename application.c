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
segment_t seg1={
    .segment_pins[0].pin=PIN0,
    .segment_pins[0].port=PORTC_INDEX,
    .segment_pins[0].direction=OUTPUT,
    .segment_pins[0].logic=LOW,
    .segment_pins[1].pin=PIN1,
    .segment_pins[1].port=PORTC_INDEX,
    .segment_pins[1].direction=OUTPUT,
    .segment_pins[1].logic=LOW,
    .segment_pins[2].pin=PIN2,
    .segment_pins[2].port=PORTC_INDEX,
    .segment_pins[2].direction=OUTPUT,
    .segment_pins[2].logic=LOW,
    .segment_pins[3].pin=PIN3,
    .segment_pins[3].port=PORTC_INDEX,
    .segment_pins[3].direction=OUTPUT,
    .segment_pins[3].logic=LOW,
    .segment_type=SEGMENT_COMMON_ANODE
};

Std_ReturnType ret=E_NOT_OK;
int main() {
    application_initialize();
    uint8 cnt=0;
    while(1){
        for(cnt=0;cnt<=9;cnt++){
            seven_segment_write_number(&seg1,cnt);
            __delay_ms(500);
        }
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    ret=seven_segment_initialize(&seg1);
}     
