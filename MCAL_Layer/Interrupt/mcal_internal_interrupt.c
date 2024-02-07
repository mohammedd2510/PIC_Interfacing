#include "mcal_internal_interrupt.h"

void ADC_ISR(void){
  #if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
       ADC_InterruptFlagClear();
      if(ADC_InterruptHandler){
       ADC_InterruptHandler();
    }
     else{ }
   #endif  
}
void MSSP_ISR(void){
#if(MSSP_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    MSSP_InterruptFlagClear();
    if(SPI_InterruptHandler)
    {
     SPI_InterruptHandler();   
    }
#endif    
}