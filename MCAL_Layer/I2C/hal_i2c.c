#include"hal_i2c.h"
static inline void MSSP_I2C_Mode_GPIO_CFG(void);
static inline void I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t *i2c_obj);
static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t *i2c_obj);
#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
InterruptHandler I2C_DefaultInterruptHandler = NULL;
InterruptHandler I2C_Report_Write_Collision_InterruptHandler = NULL;
InterruptHandler I2C_Report_Receive_Overflow_InterruptHandler = NULL;
static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t *i2c_obj);
#endif
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        /* MSSP I2C Select Mode */
        if(MSSP_I2C_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode) /* MSSP I2C Master Mode Configurations */
        {
            /* I2C Master Mode Clock Configurations */
            I2C_Master_Mode_Clock_Configurations(i2c_obj);            
        }
        else if (MSSP_I2C_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode)
        {
            /* I2C Slave Mode General Call Configurations */
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else{/* Nothing */}
            /* Clear the Write Collision Detect */
            SSPCON1_bits.WCOL =0; /* No Collision */
            /* Clear the Receive Overflow Indicator */
            SSPCON1_bits.SSPOV=0; /* No Overflow */
            /* Release The Clock */
            SSPCON1_bits.CKP=1;
         //   SSPCON2_bits.SEN=1;
            /* Assign The I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
            /* I2C Slave Mode Configurations */
            I2C_Slave_Mode_Configurations(i2c_obj);
        }
        else {/* Nothing*/}
        /* I2C GPIO Configurations */
        MSSP_I2C_Mode_GPIO_CFG();
        /* MSSP I2C Slew Rate Control */
        if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else{/* Nothing */}
        /* MSSP I2C SMBus Control */
        if(I2C_SMBUS_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control)
        {
            I2C_SMBUS_ENABLE_CFG();
        }
        else if(I2C_SMBUS_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_control)
        {
            I2C_SMBUS_DISABLE_CFG();
        }
        else{/* Nothing */}
        /* Interrupt Configurations */
#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
        MSSP_I2C_Interrupt_Configurations(i2c_obj);
#endif
        /* Enable MSSP I2C Module */
        MSSP_MODULE_ENABLE_CFG();
    }
    return ret;
}
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable MSSP I2C Module*/
        MSSP_MODULE_DISABLE_CFG();
       /* Interrupt Configurations */
#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
        MSSP_InterruptDisable();
        MSSP_BUS_COL_InterruptDisable();
#endif        
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Initiates Start Condition on SDA and SCL Pins */
        SSPCON2_bits.SEN = 1; /* Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware. */
        /* Wait for the Completion of Start Condition*/
        while(SSPCON2_bits.SEN);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1_bits.SSPIF =0;
        /* Report The Start Condition Detection */
        if(START_BIT_DETECTED == SSPSTAT_bits.S){
            ret = E_OK;
        }
        else if(START_BIT_NOT_DETECTED == SSPSTAT_bits.S){
            ret = E_NOT_OK;
        }
        else{/* Nothing */}
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Initiates Repeated Start Condition on SDA and SCL Pins */
        SSPCON2_bits.RSEN = 1; /* Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware. */
        /* Wait for the Completion of Repeated Start Condition*/
        while(SSPCON2_bits.RSEN);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1_bits.SSPIF =0;
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Initiates Stop Condition on SDA and SCL Pins */
        SSPCON2_bits.PEN = 1; /* Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware. */
        /* Wait for the Completion of Stop Condition*/
        while(SSPCON2_bits.PEN);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1_bits.SSPIF =0;
        /* Report The Stop Condition Detection */
        if(STOP_BIT_DETECTED == SSPSTAT_bits.P){
            ret = E_OK;
        }
        else if(STOP_BIT_NOT_DETECTED == SSPSTAT_bits.P){
            ret = E_NOT_OK;
        }
        else{/* Nothing */}
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *ack)
{
    Std_ReturnType ret = E_OK;
    if( (NULL == i2c_obj) || (NULL==ack) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Write Data to the Data Register */
        SSPBUF = i2c_data;
        /* Wait the Transmission to be Completed */
        while(!PIR1_bits.SSPIF);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1_bits.SSPIF =0;
        /* Report the Acknowledge Received From the Slave */
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2_bits.ACKSTAT)
        {
            *ack =I2C_ACK_RECEIVED_FROM_SLAVE;
        }
        else if(I2C_ACK_NOT_RECEIVED_FROM_SLAVE == SSPCON2_bits.ACKSTAT)
        {
            *ack=I2C_ACK_NOT_RECEIVED_FROM_SLAVE ;
        }
        else{/* Nothing */}
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8* i2c_data)
{
    Std_ReturnType ret = E_OK;
    if( (NULL == i2c_obj) || (NULL == i2c_data) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /* Wait for Buffer Full Flag : A Complete Byte Received */
        while(!SSPSTAT_bits.BF);
        /* Copy The Data Register to Buffer Variable */
        *i2c_data=SSPBUF;
        /* Send ACK or NACK After Read */
        if(I2C_MASTER_SEND_ACK == ack)
        {
            SSPCON2_bits.ACKDT = I2C_MASTER_SEND_ACK; /* Acknowledge*/
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit.*/
            SSPCON2_bits.ACKEN =1;
        }
        else if(I2C_MASTER_SEND_NACK == ack)
        {
           SSPCON2_bits.ACKDT = I2C_MASTER_SEND_NACK;/* Not Acknowledge*/
           /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit.*/
           SSPCON2_bits.ACKEN =1; 
        }
        else{/*Nothing*/}
    }
    return ret;
}
void MSSP_I2C_Clear_Buffer(void){
    uint8 Dummy_Data =0;
    Dummy_Data = SSPBUF;
}
void MSSP_I2C_Write_To_Buffer(uint8 Data)
{
    SSPBUF = Data;
}
uint8 MSSP_I2C_Read_From_Buffer(void){
    uint8 Temp_Data=0;
    Temp_Data = SSPBUF;
    return Temp_Data;
}
static inline void MSSP_I2C_Mode_GPIO_CFG(void)
{
    TRISC |=(1<<RC3); /* Serial Clock (SCL) is Input */
    TRISC |=(1<<RC4); /* Serial Data (SDA) is Input */
}
static inline void I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t *i2c_obj)
{
    SSPCON1_bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
    SSPADD =(uint8)(((_XTAL_FREQ/4.0)/i2c_obj->i2c_clock)-1);
}
static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t *i2c_obj)
{
    SSPCON1_bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
}
#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t *i2c_obj)
{
    MSSP_InterruptFlagClear();
    MSSP_BUS_COL_InterruptFlagClear();
    I2C_DefaultInterruptHandler = i2c_obj->I2C_DefaultInterruptHandler;
    I2C_Report_Write_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
    I2C_Report_Receive_Overflow_InterruptHandler = i2c_obj->I2C_Report_Receieve_Overflow;
    MSSP_InterruptEnable();
    MSSP_BUS_COL_InterruptEnable();
#if(INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
    INTERRUPT_PriorityLevelsEnable();
    if( i2c_obj->mssp_i2c_priority== INTERRUPT_HIGH_PRIORITY)
    {
        MSSP_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(i2c_obj->mssp_i2c_priority == INTERRUPT_LOW_PRIORITY)
    {
        MSSP_LowPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();   
    } 
    if( i2c_obj->mssp_i2c_bc_priority== INTERRUPT_HIGH_PRIORITY)
    {
        MSSP_BUS_COL_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(i2c_obj->mssp_i2c_bc_priority == INTERRUPT_LOW_PRIORITY)
    {
        MSSP_BUS_COL_LowPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();   
    } 
#endif 
}
#endif