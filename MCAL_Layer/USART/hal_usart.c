#include"hal_usart.h"

#if ( EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
InterruptHandler EUSART_TX_InterruptHandler = NULL;
#endif
#if ( EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
InterruptHandler EUSART_RX_InterruptHandler = NULL;
InterruptHandler EUSART_FramingErrorHandler = NULL;
InterruptHandler EUSART_OverrunErrorHandler = NULL;
#endif
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);

static void EUSART_Baud_Rate_Calcualtion(const usart_t* _eusart);
static void EUSART_ASYNC_TX_Init(const usart_t* _eusart);
static void EUSART_ASYNC_RX_Init(const usart_t* _eusart);

Std_ReturnType EUSART_ASYNC_Init(const usart_t * _eusart)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart )
    {
        ret = E_NOT_OK;
    }
    else
    {
        EUSART_MODULE_DISABLE();
        TRISC |= (1<<RC6);
        TRISC |= (1<<RC7);
        EUSART_Baud_Rate_Calcualtion(_eusart);
        EUSART_ASYNC_TX_Init(_eusart);
        EUSART_ASYNC_RX_Init(_eusart);
        EUSART_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t * _eusart)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart )
    {
        ret = E_NOT_OK;
    }
    else
    {
        EUSART_MODULE_DISABLE();
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_RX_Restart(void)
{
     Std_ReturnType ret = E_OK;
     RCSTA_bits.CREN = EUSART_ASYNCHRONOUS_RX_DISABLE;
     RCSTA_bits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
     return ret;
}
Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 data)
{
    Std_ReturnType ret = E_OK;
    while(EUSART_TSR_FULL==TXSTA_bits.TRMT);   
    TXREG = data;
#if(EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    EUSART_TX_InterruptEnable();
#endif     
    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(EUSART_TSR_EMPTY==TXSTA_bits.TRMT)
    {
    TXREG = data;
#if(EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    EUSART_TX_InterruptEnable();
#endif     
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8*data){
    Std_ReturnType ret = E_OK;
    if(NULL == data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(NULL != *data )
        {
            EUSART_ASYNC_WriteByteBlocking(*data++);
        }
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8*data){
    Std_ReturnType ret = E_OK;
    static uint16 Counter =0;
    if(NULL == data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(NULL != data[Counter] )
        {
            if(EUSART_TSR_EMPTY==TXSTA_bits.TRMT)
            {   
                TXREG = data;
#if(EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
                EUSART_TX_InterruptEnable();
#endif
                Counter++;
            }
        }
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while (EUSART_RCREG_EMPTY==PIR1_bits.RCIF );
        *data =RCREG;
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *data){
    Std_ReturnType ret = E_OK;
    if(NULL == data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(EUSART_RCREG_FULL==PIR1_bits.RCIF ){
        *data =RCREG;
        }
        else{/*Nothing*/}
    }
return ret;    
}
static void EUSART_Baud_Rate_Calcualtion(const usart_t* _eusart)
{
    float Baud_Rate_Temp =0;
    switch (_eusart->baudrate_gen_config)
    {
        case BAUDRATE_ASYNC_8BIT_LOW_SPEED:
            TXSTA_bits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTA_bits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCON_bits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)_eusart->BaudRate)/64)-1;
            break;
        case BAUDRATE_ASYNC_8BIT_HIGH_SPEED:
            TXSTA_bits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTA_bits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCON_bits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)_eusart->BaudRate)/16)-1;
            break;
        case BAUDRATE_ASYNC_16BIT_LOW_SPEED:
            TXSTA_bits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTA_bits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCON_bits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)_eusart->BaudRate)/16)-1;
            break;
        case BAUDRATE_ASYNC_16BIT_HIGH_SPEED:
            TXSTA_bits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTA_bits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCON_bits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)_eusart->BaudRate)/4)-1;
            break;
        case BAUDRATE_SYNC_8BIT:
            TXSTA_bits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCON_bits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)_eusart->BaudRate)/4)-1;
            break;
        case BAUDRATE_SYNC_16BIT:
            TXSTA_bits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCON_bits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)_eusart->BaudRate)/4)-1;
            break;  
        default: ;    
    }
    SPBRG =(uint8)((uint32)Baud_Rate_Temp);
    SPBRGH =(uint8)(((uint32)Baud_Rate_Temp)>>8);
}

static void EUSART_ASYNC_TX_Init(const usart_t* _eusart)
{
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable)
    {
        /* EUSART TX Enable */
        TXSTA_bits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        /* EUSART TX Interrupt Config*/
        if(EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable)
        {
            PIE1_bits.TXIE = EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE;
        }
        else if (EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable)
        {
            PIE1_bits.TXIE = EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE;
        }
#if (INTERRUPT_FEATURE_ENABLE == EUSART_TX_INTERRUPT_FEATURE_ENABLE)
      EUSART_TX_InterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
        /*   Interrupt  Priority Configurations   */   
#if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PriorityLevelsEnable();
            if(_eusart->usart_tx_cfg.usart_tx_int_priority == INTERRUPT_HIGH_PRIORITY){
                EUSART_TX_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_eusart->usart_tx_cfg.usart_tx_int_priority == INTERRUPT_LOW_PRIORITY)
            {
             EUSART_TX_LowPrioritySet();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();   
            } 
    #endif 
#endif
        /* EUSART TX 9BIT CONFIG */
        if(EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable)
        {
            TXSTA_bits.TX9 =EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE;
        }
        else if (EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable)
        {
            TXSTA_bits.TX9 =EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
        }
    }
    else {/* Nothing */}
}
static void EUSART_ASYNC_RX_Init(const usart_t* _eusart)
{
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable)
    {
        /* EUSART RX Enable */
        RCSTA_bits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        /* EUSART RX Interrupt Config*/
        if(EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable)
        {
            PIE1_bits.RCIE =EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE;
        }
        else if (EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable)
        {
            PIE1_bits.RCIE =EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE;
        }
#if (INTERRUPT_FEATURE_ENABLE == EUSART_TX_INTERRUPT_FEATURE_ENABLE)
        EUSART_RX_InterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
        EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
        /*   Interrupt  Priority Configurations   */   
#if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PriorityLevelsEnable();
            if(_eusart->usart_rx_cfg.usart_rx_int_priority == INTERRUPT_HIGH_PRIORITY){
                EUSART_RX_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_eusart->usart_rx_cfg.usart_rx_int_priority == INTERRUPT_LOW_PRIORITY)
            {
             EUSART_RX_LowPrioritySet();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();   
            } 
    #endif 
#endif
        /* EUSART RX 9BIT CONFIG */
        if(EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable)
        {
            
            RCSTA_bits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE;  
        }
        else if (EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable)
        {
            RCSTA_bits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;   
        }
    }
    else {/* Nothing */}
}

void EUSART_TX_ISR(void)
{
    EUSART_TX_InterruptDisable();
#if(EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    if(EUSART_TX_InterruptHandler){
        EUSART_TX_InterruptHandler();
    }
    else{/* Nothing */}
#endif    
}
                        
void EUSART_RX_ISR(void)
{
#if(EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    if(EUSART_RX_InterruptHandler){
        EUSART_RX_InterruptHandler();
    }
    else{/* Nothing */}
    if(EUSART_FramingErrorHandler){
       EUSART_FramingErrorHandler();
    }
    else{/* Nothing */}
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }
    else{/* Nothing */}
#endif  
}

