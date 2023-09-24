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


/***********************************************/

typedef union {
  struct {  
   uint8 RBIF   :1;
   uint8 INT0IF :1;
   uint8 TMR0IF :1;
   uint8 RBIE   :1;
   uint8 INT0IE :1;
   uint8 TMR0IE :1;
   uint8 PEIE :1;
   uint8 GIE :1; 
};
  struct {
   uint8      :6;
   uint8 GIEL :1;
   uint8 GIEH :1; 
};
}INTCON_t;

#define INTCON_bits (*((volatile INTCON_t *)(0xFF2)))
#define INTCON (*((volatile uint8 *)(0xFF2)))

typedef struct {
   uint8 RBIP   :1;
   uint8        :1;
   uint8 TMR0IP:1;
   uint8        :1;
   uint8 INTEDG2 :1;
   uint8 INTEDG1:1;
   uint8 INTEDG0 :1;
   uint8 RBPU :1;         
}INTCON2_t;
  
#define INTCON2_bits (*((volatile INTCON2_t *)(0xFF1)))
#define INTCON2 (*((volatile uint8 *)(0xFF1)))

typedef struct {
   uint8 INT1IF :1;
   uint8 INT2IF :1;
   uint8        :1;
   uint8 INT1IE  :1;
   uint8 INT2IE :1;
   uint8        :1;
   uint8 INT1IP :1;
   uint8 INT2IP :1;        
}INTCON3_t;
  
#define INTCON3_bits (*((volatile INTCON3_t *)(0xFF0)))
#define INTCON3 (*((volatile uint8 *)(0xFF0)))

typedef struct {
  uint8  TMR1IF :1;
  uint8  TMR2IF :1;
  uint8  CCP1IF :1;
  uint8  SSPIF :1;
  uint8  TXIF  :1;
  uint8  RCIF  :1;
  uint8  ADIF  :1;
  uint8  PSPIF :1;
}PIR1_t;
  
#define PIR1_bits (*((volatile PIR1_t *)(0xF9E)))
#define PIR1 (*((volatile uint8 *)(0xF9E)))

typedef struct {
  uint8  CCP2IF :1;
  uint8  TMR3IF :1;
  uint8  HLVDIF :1;
  uint8  BCLIF :1;
  uint8  EEIF  :1;
  uint8        :1;
  uint8  CMIF  :1;
  uint8  OSCFIF :1;  
}PIR2_t;
  
#define PIR2_bits (*((volatile PIR2_t *)(0xFA1)))
#define PIR2 (*((volatile uint8 *)(0xFA1)))


typedef struct {
  uint8  TMR1IE :1;
  uint8  TMR2IE :1;
  uint8  CCP1IE :1;
  uint8  SSPIE :1;
  uint8  TXIE  :1;
  uint8  RCIE  :1;
  uint8  ADIE  :1;
  uint8  PSPIE :1;
}PIE1_t;
  
#define PIE1_bits (*((volatile PIE1_t *)(0xF9D)))
#define PIE1 (*((volatile uint8 *)(0xF9D)))

typedef struct {
  uint8  CCP2IE :1;
  uint8  TMR3IE :1;
  uint8  HLVDIE :1;
  uint8  BCLIE  :1;
  uint8  EEIE   :1;
  uint8         :1;
  uint8  CMIE   :1;
  uint8  OSCFIE :1;
}PIE2_t;
  
#define PIE2_bits (*((volatile PIE2_t *)(0xFA0)))
#define PIE2 (*((volatile uint8 *)(0xFA0)))

typedef struct {
  uint8  TMR1IP :1;
  uint8  TMR2IP :1;
  uint8  CCP1IP :1;
  uint8  SSPIP  :1;
  uint8  TXIP  :1;
  uint8  RCIP  :1;
  uint8  ADIP  :1;
  uint8  PSPIP :1; 
}IPR1_t;
  
#define IPR1_bits (*((volatile IPR1_t *)(0xF9F)))
#define IPR1 (*((volatile uint8 *)(0xF9F)))

typedef struct {
  uint8  CCP2IP :1;
  uint8  TMR3IP :1;
  uint8  HLVDIP :1;
  uint8  BCLIP  :1;
  uint8  EEIP   :1;
  uint8         :1;
  uint8  CMIP   :1;
  uint8  OSCFIP :1; 
}IPR2_t;
  
#define IPR2_bits (*((volatile IPR2_t *)(0xFA2)))
#define IPR2 (*((volatile uint8 *)(0xFA2)))

typedef struct {
  uint8  BOR :1;
  uint8  POR :1;
  uint8  PD  :1;
  uint8  TO  :1;
  uint8  RI  :1;
  uint8      :1;
  uint8  SBOREN    :1;
  uint8  IPEN :1; 
}RCON_t;
  
#define RCON_bits (*((volatile RCON_t *)(0xFD0)))
#define RCON (*((volatile uint8 *)(0xFD0)))



#endif	/* MY_PIC18F4620_H */

