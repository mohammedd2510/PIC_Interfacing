#include"mcal_layer_init.h"
#include "Timer1/hal_timer1.h"
/* Global Variables Definitions */
Std_ReturnType ret=E_NOT_OK;
/*timer2_t timer2_obj;
timer1_t timer1_obj;
timer3_t timer3_obj;
ccp_t ccp2_obj;
ccp_t ccp1_obj;*/
usart_t usart_obj;
/* Functions Definitions*/
void USART_ASYNC_9600_BAUDRATE_INIT(void);
void mcal_layer_initialize(void)
{
    USART_ASYNC_9600_BAUDRATE_INIT();
}
/*
void Timer2_Timer_Init(void){
    timer2_obj.timer2_preload_value = 0;
    timer2_obj.postscaler_value =TIMER2_POSTSCALER_DIV_BY_1;
    timer2_obj.prescaler_value = TIMER2_PRESCALER_DIV_BY_16;
    ret=Timer2_Init(&timer2_obj);
}


void CCP2_COMPARE_50HZ_75Duty_INIT(void)
{
    ccp2_obj.ccp_inst =CCP2_INST;
    ccp2_obj.ccp_mode =CCP_COMPARE_MODE_SELECTED;
    ccp2_obj.ccp_mode_variant = CCP_COMPARE_MODE_SET_PIN_LOW;
    ccp2_obj.ccp_pin.direction=OUTPUT;
    ccp2_obj.ccp_pin.port=PORTC_INDEX;
    ccp2_obj.ccp_pin.pin=PIN1;
    CCP_Compare_Mode_Set_Value(&ccp2_obj,14800);
    CCP_Init(&ccp2_obj);
    
}
void Timer3_Timer_Init(void){
    timer3_obj.timer3_preload_value = 0;
    timer3_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer3_obj.timer3_reg_wr_mode = TIMER3_RW_REG_8BIT_MODE;
    timer3_obj.prescaler_value = TIMER3_PRESCALER_DIV_BY_4;
    ret=Timer3_Init(&timer3_obj);
}

void CCP1_Capture_Mode_Init(void)
{
    ccp1_obj.ccp_capt_comp_timer = CCP1_TIMER1_CCP2_TIMER3;
    ccp1_obj.ccp_inst =CCP1_INST;
    ccp1_obj.ccp_mode =CCP_CAPTURE_MODE_SELECTED;
    ccp1_obj.ccp_mode_variant = CCP_CAPTURE_MODE_1_RISING_EDGE;
    ccp1_obj.ccp_pin.direction=INPUT;
    ccp1_obj.ccp_pin.port=PORTC_INDEX;
    ccp1_obj.ccp_pin.pin=PIN2;
    
    CCP_Init(&ccp1_obj);
}
void Timer1_Timer_Init(void){
    timer1_obj.timer1_preload_value = 0;
    timer1_obj.timer1_mode = TIMER1_TIMER_MODE;
    timer1_obj.timer1_reg_wr_mode = TIMER1_RW_REG_8BIT_MODE;
    timer1_obj.prescaler_value = TIMER1_PRESCALER_DIV_BY_1;
    ret=Timer1_Init(&timer1_obj);
}
*/
void USART_ASYNC_9600_BAUDRATE_INIT(void){
    usart_obj.BaudRate=9600;
    usart_obj.EUSART_RxDefaultInterruptHandler=USART_RX_INT;
    usart_obj.EUSART_TxDefaultInterruptHandler=USART_TX_INT;
    usart_obj.baudrate_gen_config = BAUDRATE_ASYNC_16BIT_HIGH_SPEED;
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable =EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_enable =EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE;
    EUSART_ASYNC_Init(&usart_obj);
}