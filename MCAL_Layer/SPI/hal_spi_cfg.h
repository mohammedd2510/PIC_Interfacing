/* 
 * File:   hal_spi_cfg.h
 * Author: Mohamed Osama
 *
 * Created on February 6, 2024, 8:57 PM
 */

#ifndef HAL_SPI_CFG_H
#define	HAL_SPI_CFG_H

/* Section : Includes */


/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */
#define SPI_SDO_PIN_OUTPUT() TRISC&=(~(1<<5))
#define SPI_SCK_PIN_OUTPUT() TRISC&=(~(1<<3))
#define SPI_SCK_PIN_INPUT() TRISC|=(1<<3)
#define SPI_SS_PIN_INPUT()  TRISA|=(1<<5)
/* Section : Data Types Declaration */


/* Section : Functions Declaration */

#endif	/* HAL_SPI_CFG_H */

