/* 
 * File:   hal_usart.h
 * Author: Mohamed Osama
 *
 * Created on January 28, 2024, 6:02 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section : Includes */
#include "hal_usart_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/my_pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"


/* Section : Macros Declaration */

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE 1
#define EUSART_ASYNCHRONOUS_MODE 0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED 1
#define EUSART_ASYNCHRONOUS_LOW_SPEED 0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN 1
#define EUSART_08BIT_BAUDRATE_GEN 0
/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE 1
#define EUSART_ASYNCHRONOUS_TX_DISABLE 0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE 1
#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE 0
/* EUSART 9-bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE 1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE 0
/* EUSART Receive Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE 1
#define EUSART_ASYNCHRONOUS_RX_DISABLE 0
/* EUSART Receive Interrupt Enable */
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE 1
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE 0
/* EUSART 9-bit Receive Enable */
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE 1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE 0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0
/* EUSART TSR State */
#define EUSART_TSR_EMPTY    1U
#define EUSART_TSR_FULL     0U
/* EUSART Receiever_Buffer State */
#define EUSART_RCREG_EMPTY    0U
#define EUSART_RCREG_FULL     1U
/* Section : Macro Functions Declaration */
#define EUSART_MODULE_ENABLE() (RCSTA_bits.SPEN = 1)
#define EUSART_MODULE_DISABLE() (RCSTA_bits.SPEN = 0)

/* Section : Data Types Declaration */
typedef enum {
    BAUDRATE_ASYNC_8BIT_LOW_SPEED,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
    BAUDRATE_SYNC_8BIT,
    BAUDRATE_SYNC_16BIT        
}baudrate_gen_t;

typedef struct{
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9bit_enable : 1;
    interrupt_priority_cfg usart_tx_int_priority;
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9bit_enable : 1;
    interrupt_priority_cfg usart_rx_int_priority ;
}usart_rx_cfg_t;

typedef union {
    struct {
        uint8 usart_reserved :6;
        uint8 usart_ferr : 1;
        uint8 usart_oerr : 1; 
    };
    uint8 status ;
}usart_error_status_t;

typedef struct 
{
    uint32 BaudRate ;
    baudrate_gen_t baudrate_gen_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;
    void(*EUSART_TxDefaultInterruptHandler)(void);
    void(*EUSART_RxDefaultInterruptHandler)(void);
    void(*EUSART_FramingErrorHandler)(void);
    void(*EUSART_OverrunErrorHandler)(void);
}usart_t;

/* Section : Functions Declaration */
Std_ReturnType EUSART_ASYNC_Init(const usart_t * _eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t * _eusart);
Std_ReturnType EUSART_ASYNC_RX_Restart(void);
Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 data);
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8* data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8* data);
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *data);

#endif	/* HAL_USART_H */

