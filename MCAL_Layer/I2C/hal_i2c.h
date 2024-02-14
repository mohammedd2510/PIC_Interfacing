/* 
 * File:   hal_i2c.h
 * Author: Mohamed Osama
 *
 * Created on February 12, 2024, 4:59 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/my_pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macros Declaration */

/* Slew Rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE 0X01U
#define I2C_SLEW_RATE_ENABLE 0X00U
/* SMBus Enable/Disable */
#define I2C_SMBUS_DISABLE 0X00U
#define I2C_SMBUS_ENABLE 0X01U
/* Slave Mode Data/Address Indication */
#define I2C_LAST_BYTE_DATA 0X01U
#define I2C_LAST_BYTE_ADDRESS 0X00U
/* Stop Condition Indication */
#define STOP_BIT_DETECTED 0X01U
#define STOP_BIT_NOT_DETECTED 0X00U
/* Start Condition indication */
#define START_BIT_DETECTED 0X01U
#define START_BIT_NOT_DETECTED 0X00U
/* I2C : Master or Slave Mode */
#define MSSP_I2C_MASTER_MODE 0X01U
#define MSSP_I2C_SLAVE_MODE 0X00U
/* Master Synchronous Serial Port Mode Select */
#define I2C_SLAVE_MODE_7BIT_ADDRESS 0X06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS 0X07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE 0X0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE 0X0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK 0X08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED 0X0BU
/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE 0X01U
#define I2C_GENERAL_CALL_DISABLE 0X00U
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE   0X01U
#define I2C_MASTER_RECEIVE_DISABLE  0X00U
/* Acknowledge Status bit (Master Transmit mode only) */
#define I2C_ACK_RECEIVED_FROM_SLAVE 0X00U 
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE 0X01U
/* Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK 0X00U
#define I2C_MASTER_SEND_NACK 0X01U

/* Section : Macro Functions Declaration */

/* Slew Rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE_CFG() (SSPSTAT_bits.SMP=0X01U)
#define I2C_SLEW_RATE_ENABLE_CFG() (SSPSTAT_bits.SMP=0X00U)
/* SMBus Enable/Disable */
#define I2C_SMBUS_DISABLE_CFG() (SSPSTAT_bits.CKE=0X00U)
#define I2C_SMBUS_ENABLE_CFG() (SSPSTAT_bits.CKE=0X01U)
/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE_CFG() (SSPCON2_bits.GCEN=0X01U)
#define I2C_GENERAL_CALL_DISABLE_CFG() (SSPCON2_bits.GCEN=0X00U)
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE_CFG()   (SSPCON2_bits.RCEN=0X01U)
#define I2C_MASTER_RECEIVE_DISABLE_CFG()  (SSPCON2_bits.RCEN=0X00U)
/* Master Synchronous Serial Port Enable */
#define MSSP_MODULE_ENABLE_CFG() (SSPCON1_bits.SSPEN=1)
#define MSSP_MODULE_DISABLE_CFG() (SSPCON1_bits.SSPEN=0)
/* I2C Clock Stretch Disable */
#define I2C_CLOCK_STRETCH_DISABLE() (SSPCON1_bits.CKP = 1)
#define I2C_CLOCK_STRETCH_ENABLE() (SSPCON1_bits.CKP = 0)
/* I2C Slave Received Status */
#define I2C_SLAVE_RECEIVED_ADDRESS_WRITE_OPERATION() ((SSPSTAT_bits.RW == 0)&&(SSPSTAT_bits.DA == 0))
#define I2C_SLAVE_RECEIVED_ADDRESS_READ_OPERATION() ((SSPSTAT_bits.RW == 1)&&(SSPSTAT_bits.DA == 0))
#define I2C_SLAVE_RECEIVED_DATA_WRITE_OPERATION() ((SSPSTAT_bits.RW == 0)&&(SSPSTAT_bits.DA == 1))
#define I2C_SLAVE_RECEIVED_DATA_READ_OPERATION() ((SSPSTAT_bits.RW == 1)&&(SSPSTAT_bits.DA == 1))
/* Wait for Buffer to be Full */
#define WAIT_FOR_MSSP_BUFFER_TO_BE_FULL()   while(SSPSTAT_bits.BF==0) 

/* Section : Data Types Declaration */
typedef struct
{
    uint8 i2c_mode_cfg;
    uint8 i2c_slave_address;
    uint8 i2c_mode : 1;
    uint8 i2c_slew_rate : 1;
    uint8 i2c_SMBus_control : 1;
    uint8 i2c_general_call : 1;
    uint8 i2c_reserved : 4;
}i2c_configs_t;

typedef struct
{
    uint32 i2c_clock;
#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
    InterruptHandler I2C_Report_Write_Collision;
    InterruptHandler I2C_Report_Receieve_Overflow;
    InterruptHandler I2C_DefaultInterruptHandler;
    #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE )
    interrupt_priority_cfg mssp_i2c_priority;
    interrupt_priority_cfg mssp_i2c_bc_priority;
    #endif
#endif
    i2c_configs_t i2c_cfg;
    
}mssp_i2c_t;

/* Section : Functions Declaration */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *ack);
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8* i2c_data);
void MSSP_I2C_Clear_Buffer(void);
void MSSP_I2C_Write_To_Buffer(uint8 Data);
uint8 MSSP_I2C_Read_From_Buffer(void);
#endif	/* HAL_I2C_H */

