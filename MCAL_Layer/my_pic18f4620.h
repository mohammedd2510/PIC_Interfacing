/* 
 * File:   my_pic18f4620.h
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 2:42 PM
 */

#ifndef MY_PIC18F4620_H
#define	MY_PIC18F4620_H

/* Platform Abstraction */
#define PLATFORM REG8
#if PLATFORM == REG8
    /* 8-bit register access method*/
    #define HWREG(_x) (*((volatile uint8*)(_x)))
#elif PLATFORM == REG16
     /* 16-bit register access method*/
    #define HWREG(_x) (*((volatile uint16 *)(_x)))
#elif PLATFORM == REG32
     /* 32-bit register access method*/
    #define HWREG(_x) (*((volatile uint32 *)(_x)))
#else
    #error "platform is not supported"
#endif 
/***************Register Definitions************************/
#define LATA_ADD 0xF89
#define LATA HWREG(LATA_ADD)
#define LATB_ADD 0xF8A
#define LATB HWREG(LATB_ADD)
#define LATC_ADD 0xF8B
#define LATC HWREG(LATC_ADD)
#define LATD_ADD 0xF8C
#define LATD HWREG(LATD_ADD)
#define LATE_ADD 0xF8D
#define LATE HWREG(LATE_ADD)

#define TRISA_ADD 0xF92
#define TRISA HWREG(TRISA_ADD)
#define TRISB_ADD 0xF93
#define TRISB HWREG(TRISB_ADD)
#define TRISC_ADD 0xF94
#define TRISC HWREG(TRISC_ADD)
#define TRISD_ADD 0xF95
#define TRISD HWREG(TRISD_ADD)
#define TRISE_ADD 0xF96
#define TRISE HWREG(TRISE_ADD)

#define PORTA_ADD 0xF80
#define PORTA HWREG(PORTA_ADD)
#define PORTB_ADD 0xF81
#define PORTB HWREG(PORTB_ADD)
#define PORTC_ADD 0xF82
#define PORTC HWREG(PORTC_ADD)
#define PORTD_ADD 0xF83
#define PORTD HWREG(PORTD_ADD)
#define PORTE_ADD 0xF84
#define PORTE HWREG(PORTE_ADD)


#endif	/* MY_PIC18F4620_H */

