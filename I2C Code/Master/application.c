/* 
 * File:   application.c
 * Author: Mohamed Osama
 * Description: 
 * Created on January 8, 2024, 1:34 PM
 */

#include "application.h"
#define SLAVE_1 0X18
#define SLAVE_2 0X62
#define SLAVE_2_READ 0X63
uint8 Master_Received_Data =0;
void I2C_SLAVE_ISR(void)
{
    
}
void I2C_Master_Init(void);
void I2C_Slave_1_Init(void);
void I2C_Slave_2_Init(void);
void I2C_Send_1_byte(uint8 add , uint8 Data);
void I2C_Recieve_1_byte(uint8 add , uint8* Data );
mssp_i2c_t i2c_obj;
int main() 
{
    I2C_Master_Init();
    ecu_layer_initialize();
    
    while(1)
    {
        I2C_Send_1_byte(SLAVE_1,'a');
        __delay_ms(1000);
        I2C_Recieve_1_byte(SLAVE_2_READ,&Master_Received_Data);
        if(Master_Received_Data == 'b'){
            led_turn_on(&led1);
        }
        __delay_ms(1000);
         I2C_Send_1_byte(SLAVE_2,'B');
        __delay_ms(1000);
         I2C_Send_1_byte(SLAVE_1,'c');
        __delay_ms(1000);
        I2C_Recieve_1_byte(SLAVE_2_READ,&Master_Received_Data);
        if(Master_Received_Data == 'd'){
            led_turn_off(&led1);
        }
        __delay_ms(1000);
        I2C_Send_1_byte(SLAVE_2,'D');
        __delay_ms(1000);
    }
    return (0);
}
void I2C_Master_Init(void)
{
    i2c_obj.i2c_clock = 100000;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBUS_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_MASTER_MODE;
    i2c_obj.i2c_cfg.i2c_slew_rate=I2C_SLEW_RATE_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_MASTER_MODE_DEFINED_CLOCK;
    MSSP_I2C_Init(&i2c_obj);
}
void I2C_Slave_1_Init(void)
{
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBUS_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_slew_rate=I2C_SLEW_RATE_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS;
    i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE;
 //   i2c_obj.I2C_DefaultInterruptHandler =I2C_SLAVE_ISR;
    i2c_obj.i2c_cfg.i2c_slave_address = 0x60;
    MSSP_I2C_Init(&i2c_obj); 
}
void I2C_Slave_2_Init(void)
{
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBUS_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_slew_rate=I2C_SLEW_RATE_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS;
    i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE;
 //   i2c_obj.I2C_DefaultInterruptHandler =I2C_SLAVE_ISR;
    i2c_obj.i2c_cfg.i2c_slave_address = 0x62;
    MSSP_I2C_Init(&i2c_obj); 
}
void I2C_Send_1_byte(uint8 add , uint8 Data)
{
    uint8 ack =0;
    MSSP_I2C_Master_Send_Start(&i2c_obj);
    MSSP_I2C_Master_Write_Blocking(&i2c_obj,add,&ack);
    MSSP_I2C_Master_Write_Blocking(&i2c_obj,Data,&ack);
    MSSP_I2C_Master_Send_Stop(&i2c_obj);
}
void I2C_Recieve_1_byte(uint8 add , uint8* Data )
{
    uint8 ack =0;
    MSSP_I2C_Master_Send_Start(&i2c_obj);
    MSSP_I2C_Master_Write_Blocking(&i2c_obj,add,&ack);
    MSSP_I2C_Master_Read_Blocking(&i2c_obj,I2C_MASTER_SEND_NACK,Data);
    MSSP_I2C_Master_Send_Stop(&i2c_obj);
}