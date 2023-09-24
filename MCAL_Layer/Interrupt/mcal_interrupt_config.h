/* 
 * File:   mcal_interrupt_config.h
 * Author: Mohamed Osama
 *
 * Created on September 12, 2023, 12:34 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : Includes */
#include "../mcal_std_types.h"
#include "../my_pic18f4620.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"


/* Section : Macros Declaration */
#define INTERRUPT_ENABLE 1
#define INTERRUPT_DISABLE 0
#define INTERRUPT_OCCUR 1
#define INTERRUPT_NOT_OCCUR 0
#define INTERRUPT_PRIORITY_ENABLE 1
#define INTERRUPT_PRIORITY_DISABLE 0
#define INTERRUPT_PRIORITY_HIGH 1
#define INTERRUPT_PRIORITY_LOW 0

/* Section : Macro Functions Declaration */

#if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE) 

/* This macro will enable priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsEnable() (RCON_bits.IPEN=1)
/* This macro will disable priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsDisable() (RCON_bits.IPEN=0)
/* This macro will enable high priority global interrupts. */
#define INTERRUPT_GlobalInterruputHighEnable() (INTCON_bits.GIEH = 1)
/* This macro will disable high priority global interrupts. */
#define INTERRUPT_GlobalInterruputHighDisable() (INTCON_bits.GIEH = 0)
/* This macro will enable low priority global interrupts. */
#define INTERRUPT_GlobalInterruputLowEnable() (INTCON_bits.GIEL = 1)
/* This macro will disable low priority global interrupts. */
#define INTERRUPT_GlobalInterruputLowDisable() (INTCON_bits.GIEL = 0)

#else
/* This macro will enable global interrupts. */
#define INTERRUPT_GlobalInterruputEnable() (INTCON_bits.GIE = 1)
/* This macro will disable global interrupts. */
#define INTERRUPT_GlobalInterruputDisable() (INTCON_bits.GIE = 0)
/* This macro will enable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruputEnable() (INTCON_bits.PEIE = 1)
/* This macro will disable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruputDisable() (INTCON_bits.PEIE = 0)


#endif

/* Section : Data Types Declaration */
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0 ,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;

/* Section : Functions Declaration */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

