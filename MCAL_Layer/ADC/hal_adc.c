#include <pic18f4620.h>

#include"hal_adc.h"

#if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
InterruptHandler ADC_InterruptHandler = NULL;
#endif
static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_conf_t *_adc);
static inline void configure_voltage_reference(const adc_conf_t *_adc);

/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC
 *              This routine must be called before any other ADC routine is called
 *              This routine should only be called once during system initialization
 * @Preconditions None
 * @param _adc Pointer to the ADC Configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc){
      Std_ReturnType ret=E_OK;
    if(_adc==NULL){
        ret=E_NOT_OK;
    }
    else{
        /* Disable The ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the acquisition time */
        ADC_ACQUISITION_TIME_CONFIG = _adc->acquisition_time;
        /* Configure the conversion clock */
        ADC_CONVERSION_CLOCK_CONFIG = _adc->conversion_clock;
        /* Configure the default Channel  */
        ADC_CHANNEL_SELECT_CONFIG =_adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        /* Configure the Interrupt        */
        #if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
            ADC_InterruptHandler = _adc->ADC_InterruptHandler;
             #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE )
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif
            ADC_InterruptEnable();
            ADC_InterruptFlagClear();
            #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE )
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _adc->priority){
                    ADC_HighPrioritySet();
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else if (INTERRUPT_LOW_PRIORITY == _adc->priority){
                    ADC_LowPrioritySet();
                    INTERRUPT_GlobalInterruptHighEnable();
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else {/* Nothing */}
            #endif
        #endif
        /* Configure The Result Format    */
        select_result_format(_adc);
        /* Configure The Voltage Reference */
        configure_voltage_reference(_adc);
        /* Enable The ADC                  */
        ADC_CONVERTER_ENABLE();
        }
    return ret;
}
/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC Configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc){
    Std_ReturnType ret=E_OK;
    if(_adc==NULL){
        ret=E_NOT_OK;
    }
    else{
        /* Disable The ADC */
        ADC_CONVERTER_DISABLE();
         /* Configure the Interrupt        */
        #if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
            ADC_InterruptDisable();
        #endif
        }
    return ret;
}
/**
 * @Summary Allow Selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion
 * @Preconditions ADC_Init() function should have been called before calling this function
 * @param _adc Pointer to the ADC Configurations
 * @param channel defines the channel available for conversion
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel){
     Std_ReturnType ret=E_OK;
    if(_adc==NULL){
        ret=E_NOT_OK;
    }
    else{
         ADC_CHANNEL_SELECT_CONFIG =channel;
        adc_input_channel_port_configure(channel);
        }
    return ret;
}
/**
 * @Summary Starts Conversion
 * @Description This routine is used to start conversion of desired channel
 * @Preconditions ADC_Init() function should have been called before calling this function
 * @param _adc Pointer to the ADC Configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc){
    Std_ReturnType ret=E_OK;
    if(_adc==NULL){
        ret=E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
        }
    return ret;
}
/**
 * @Summary Returns True when conversion is completed otherwise false
 * @Description This routine is used to determine if conversion is completed
 *              when conversion is completed routine returns true. it returns false otherwise
 * @Preconditions ADC_Init() function should have been called before calling this function
 *                ADC_StartConversion() function should have been called before calling this function
 * @param _adc Pointer to the ADC Configurations
 * @param conversion_status The Conversion status
 *          true  ~ If conversion is complete
 *          false ~ If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status){
     Std_ReturnType ret=E_OK;
     if((_adc==NULL)||(conversion_status==NULL)){
        ret=E_NOT_OK;
    }
    else{
        *conversion_status = !(ADC_CONVERSION_STATUS());
        }
    return ret;
}
/**
 * @Summary Returns the ADC conversion value
 * @Description This routine is used to get the analog to digital converted value
 *              this routine gets the converted value from the desired channel
 * @Preconditions This routine returns the conversion value only after the conversion is completed
 *                completion status can be checked using ADC_IsConversionDone() routine
 * @param _adc Pointer to the ADC Configurations
 * @param conversion_result the converted value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, adc_result_t *conversion_result){
    Std_ReturnType ret=E_OK;
     if((_adc==NULL)||(conversion_result==NULL)){
        ret=E_NOT_OK;
    }
    else{
        switch (_adc->result_format){
            case ADC_RESULT_LEFT : *conversion_result=(adc_result_t)(((ADRESH<<8) +ADRESL)>>6);break;
            case ADC_RESULT_RIGHT : *conversion_result=(adc_result_t)((ADRESH<<8) +ADRESL);break;
            default: *conversion_result=(adc_result_t)((ADRESH<<8) +ADRESL);break;
    }
        }
    return ret;
}
/**
 * @Summary Returns the ADC conversion value , Also allows select of desired channel for conversion
 * @Description This routine is used to get the analog to digital converted value
 *              this routine is used to select the desired channel for conversion
 * @Preconditions ADC_Init() function should have been called before calling this function
 * @param _adc Pointer to the ADC Configurations
 * @param channel defines the channel available for conversion
 * @param conversion_result the converted value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel ,adc_result_t *conversion_result ){
    Std_ReturnType ret=E_OK;
     if((_adc==NULL)||(conversion_result==NULL)){
        ret=E_NOT_OK;
    }
    else{
         /* Select ADC Channel */
         ret = ADC_SelectChannel(_adc ,channel);
         /* Start The Conversion */
         ret&= ADC_StartConversion(_adc);
         /* Block until conversion completed */
         BLOCK_UNTIL_CONVERSION_COMPLETED();
         /* Get the Conversion Result */
         ret&= ADC_GetConversionResult(_adc,conversion_result);
        }
    return ret;
}
/**
 * @Summary Start the ADC conversion using Interrupt , Also allows select of desired channel for conversion
 * @Description This routine is used to start Analog to digital conversion using Interrupt
 *              this routine is used to select the desired channel for conversion
 * @Preconditions ADC_Init() function should have been called before calling this function
 * @param _adc Pointer to the ADC Configurations
 * @param channel defines the channel available for conversion
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret=E_OK;
     if(_adc==NULL){
        ret=E_NOT_OK;
    }
    else{
         /* Select ADC Channel */
         ret = ADC_SelectChannel(_adc ,channel);
         /* Start The Conversion */
         ret&= ADC_StartConversion(_adc);
        }
    return ret;
}
static inline void adc_input_channel_port_configure(adc_channel_select_t channel){
      switch(channel){
          case ADC_CHANNEL_AN0: SET_BIT(TRISA,RA0);break;
          case ADC_CHANNEL_AN1: SET_BIT(TRISA,RA1);break;
          case ADC_CHANNEL_AN2: SET_BIT(TRISA,RA2);break;
          case ADC_CHANNEL_AN3: SET_BIT(TRISA,RA3);break;
          case ADC_CHANNEL_AN4: SET_BIT(TRISA,RA5);break;
          case ADC_CHANNEL_AN5: SET_BIT(TRISE,RE0);break; 
          case ADC_CHANNEL_AN6: SET_BIT(TRISE,RE1);break;   
          case ADC_CHANNEL_AN7: SET_BIT(TRISE,RE2);break;   
          case ADC_CHANNEL_AN8: SET_BIT(TRISB,RB2);break;  
          case ADC_CHANNEL_AN9: SET_BIT(TRISB,RB3);break;
          case ADC_CHANNEL_AN10: SET_BIT(TRISB,RB1);break;   
          case ADC_CHANNEL_AN11: SET_BIT(TRISB,RB4);break;
          case ADC_CHANNEL_AN12: SET_BIT(TRISB,RB0);break;
          default: break;
      }
}
static inline void select_result_format(const adc_conf_t *_adc){
    switch (_adc->result_format){
        case ADC_RESULT_LEFT : ADC_RESULT_LEFT_FORMAT();break;
        case ADC_RESULT_RIGHT : ADC_RESULT_RIGHT_FORMAT();break;
        default: ADC_RESULT_RIGHT_FORMAT();break;
    }
}
static inline void configure_voltage_reference(const adc_conf_t *_adc){
    switch (_adc->voltage_reference){
        case ADC_VOLTAGE_REFERENCE_ENABLED : ADC_ENABLE_VOLTAGE_REFERENCE();break;
        case ADC_VOLTAGE_REFERENCE_DISABLED: ADC_DISABLE_VOLTAGE_REFERENCE();break;
        default: ADC_DISABLE_VOLTAGE_REFERENCE();break;
    }
}