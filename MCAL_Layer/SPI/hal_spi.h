/* 
 * File:   hal_spi.h
 * Author: Mohamed Osama
 *
 * Created on February 5, 2024, 11:30 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/my_pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include"hal_spi_cfg.h"
/* Section : Macros Declaration */

/* SPI Transmit Phase Config */
#define SPI_TRANSMIT_ON_LEADING_EDGE 0x00U
#define SPI_TRANSMIT_ON_TRAILING_EDGE 0x01U

/* SPI Sample Time */
#define SPI_SAMPLE_AT_MIDDLE_OF_DATA_OUTPUT 0x00U
#define SPI_SAMPLE_AT_END_OF_DATA_OUTPUT 0x01U

/* SPI Clock Polarity Config */
#define SPI_POLARITY_LOW_LEVEL  0x00U
#define SPI_POLARITY_HIGH_LEVEL 0x01U

/* SPI MODE */
#define SPI_MASTER_MODE 0X00U
#define SPI_SLAVE_MODE 0X01U

#define SPI_BUFFER_FULL 0x01
#define SPI_BUFFER_STATUS (SSPSTAT_bits.BF)

#define SPI_SLAVE_STATUS_RECEIEVD_DATA 0x01
#define SPI_SLAVE_STATUS_RESET 0X00

/* Section : Macro Functions Declaration */

/* SPI Enable */
#define SPI_MODULE_ENABLE() (SSPCON1_bits.SSPEN=1)
#define SPI_MODULE_DISABLE() (SSPCON1_bits.SSPEN=0)
/* SPI Transmit Phase Config */
#define SPI_TRANSMIT_PHASE_CONFIG(_CONFIG)  (SSPSTAT_bits.CKE = _CONFIG)
/* SPI Sample Time */
#define SPI_SAMPLE_TIME_CONFIG(_CONFIG)  (SSPSTAT_bits.SMP = _CONFIG)
/* SPI Clock Polarity Config */
#define SPI_POLARITY_CONFIG(_CONFIG)  (SSPCON1_bits.CKP = _CONFIG)
/* SPI Clock Mode Config */
#define SPI_CLK_MODE_CONFIG(_CONFIG) (SSPCON1_bits.SSPM = _CONFIG)

/* Section : Data Types Declaration */
typedef enum
{
    SPI_MASTER_MODE_CLK_FOSC_DIV_4 = 0 ,
    SPI_MASTER_MODE_CLK_FOSC_DIV_16,
    SPI_MASTER_MODE_CLK_FOSC_DIV_64,  
    SPI_MASTER_MODE_CLK_TMR2_OUTPUT_DIV_2 , 
    SPI_SLAVE_MODE_SS_PIN_CONTROL_ENABLED, 
    SPI_SLAVE_MODE_SS_PIN_CONTROL_DISABLED,
}spi_clk_mode_t;

typedef struct
{
    uint8 spi_transmit_phase_cfg :1;
    uint8 spi_sample_time_cfg    :1;
    uint8 spi_polarity_cfg       :1;
    uint8 spi_mode :1;
    uint8 spi_reserved :4;
    spi_clk_mode_t spi_clk_mode;
#if (MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
    InterruptHandler SPI_InterruptHandler ;
    #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE )
    interrupt_priority_cfg priority ;
    #endif
#endif    
}spi_config_t;

extern uint8 SPI_Slave_Receive_Status;
/* Section : Functions Declaration */

Std_ReturnType SPI_Init(spi_config_t* spi_config);
Std_ReturnType SPI_Deinit(spi_config_t* spi_config);
Std_ReturnType SPI_Master_Transcieve_Blocking(uint8 data_to_transmit , uint8* received_data , pin_config_t* slave_select_gpio_pin);
Std_ReturnType SPI_Master_Transmit_Blocking(uint8 data_to_transmit , pin_config_t* slave_select_gpio_pin);
Std_ReturnType SPI_Master_Receive_Blocking(uint8* received_data , pin_config_t* slave_select_gpio_pin);
Std_ReturnType SPI_Slave_Receive_Blocking(uint8* received_data);
Std_ReturnType SPI_Slave_Receive_Non_Blocking(uint8* received_data);



#endif	/* HAL_SPI_H */

