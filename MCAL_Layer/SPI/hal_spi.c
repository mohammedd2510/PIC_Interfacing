#include"hal_spi.h"
static void SPI_Pins_Direction_Initialize(spi_config_t* spi_config);

#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
InterruptHandler SPI_InterruptHandler = NULL;
static void SPI_Interrupt_Init(spi_config_t* spi_config);
#endif
uint8 SPI_Slave_Receive_Status =ZERO_INIT;
Std_ReturnType SPI_Init(spi_config_t* spi_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == spi_config)
    {
      ret = E_NOT_OK;   
    }
    else
    {
        SPI_MODULE_DISABLE();
        SPI_POLARITY_CONFIG(spi_config->spi_polarity_cfg);
        SPI_TRANSMIT_PHASE_CONFIG(spi_config->spi_transmit_phase_cfg);
        SPI_SAMPLE_TIME_CONFIG(spi_config->spi_sample_time_cfg);
        SPI_Pins_Direction_Initialize(spi_config);
        SPI_CLK_MODE_CONFIG(spi_config->spi_clk_mode);
#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
        SPI_Interrupt_Init(spi_config);
#endif
        SPI_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType SPI_Deinit(spi_config_t* spi_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == spi_config)
    {
      ret = E_NOT_OK;   
    }
    else
    {
#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )        
        MSSP_InterruptDisable();
#endif
        SPI_MODULE_DISABLE();
    }
    return ret;
}
Std_ReturnType SPI_Master_Transcieve_Blocking(uint8 data_to_transmit , uint8* received_data , pin_config_t* slave_select_gpio_pin)
{
    Std_ReturnType ret = E_OK;
    if( (NULL == received_data))
    {
      ret = E_NOT_OK;   
    }
    else
    {
        gpio_pin_write_logic(slave_select_gpio_pin,LOW);
        SSPBUF = data_to_transmit;
        while (SPI_BUFFER_FULL != SPI_BUFFER_STATUS);
        *received_data = SSPBUF;
        gpio_pin_write_logic(slave_select_gpio_pin,HIGH);
    }
    return ret;
}
Std_ReturnType SPI_Master_Transmit_Blocking(uint8 data_to_transmit , pin_config_t* slave_select_gpio_pin)
{
    Std_ReturnType ret = E_OK;
    uint8 dummy_buffer=0; 
    gpio_pin_write_logic(slave_select_gpio_pin,LOW);
    SSPBUF = data_to_transmit;
    while (SPI_BUFFER_FULL != SPI_BUFFER_STATUS);
    dummy_buffer = SSPBUF;
    gpio_pin_write_logic(slave_select_gpio_pin,HIGH);
    return ret;
}
Std_ReturnType SPI_Master_Receive_Blocking(uint8* received_data , pin_config_t* slave_select_gpio_pin)
{
    Std_ReturnType ret = E_OK;
    uint8 dummy_data =0x00;
    if( (NULL == received_data) )
    {
      ret = E_NOT_OK;   
    }
    else
    {
        gpio_pin_write_logic(slave_select_gpio_pin,LOW);
        SSPBUF = dummy_data;
        while (SPI_BUFFER_FULL != SPI_BUFFER_STATUS);
        *received_data = SSPBUF;
        gpio_pin_write_logic(slave_select_gpio_pin,HIGH);
    }
    return ret;
}
Std_ReturnType SPI_Slave_Receive_Blocking(uint8* received_data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == received_data)
    {
      ret = E_NOT_OK;   
    }
    else
    {
        while (SPI_BUFFER_FULL != SPI_BUFFER_STATUS);
        *received_data = SSPBUF;
    }
    return ret;
}
Std_ReturnType SPI_Slave_Receive_Non_Blocking(uint8* received_data)
{
    Std_ReturnType ret = E_OK;
    if( (NULL == received_data) )
    {
      ret = E_NOT_OK;   
    }
    else
    {
        SPI_Slave_Receive_Status= SPI_SLAVE_STATUS_RECEIEVD_DATA;
        *received_data = SSPBUF;
    }
    return ret;
}

static void SPI_Pins_Direction_Initialize(spi_config_t* spi_config)
{
    SPI_SDO_PIN_OUTPUT();
    if (SPI_MASTER_MODE==spi_config->spi_mode )
    {
        SPI_SCK_PIN_OUTPUT();
    }
    else if (SPI_SLAVE_MODE==spi_config->spi_mode )
    {
        SPI_SCK_PIN_INPUT();
        SPI_SS_PIN_INPUT();
    }
    else{ /* Nothing */ }
}

#if(MSSP_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE )
static void SPI_Interrupt_Init(spi_config_t* spi_config)
{
    MSSP_InterruptFlagClear();
    SPI_InterruptHandler = spi_config->SPI_InterruptHandler;
    MSSP_InterruptEnable();
#if(INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
    INTERRUPT_PriorityLevelsEnable();
    if(spi_config->priority == INTERRUPT_HIGH_PRIORITY)
    {
        MSSP_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(spi_config->priority == INTERRUPT_LOW_PRIORITY)
    {
        MSSP_LowPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();   
    } 
#endif 
}
#endif