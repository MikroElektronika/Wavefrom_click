/*
    __waveform_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __waveform_driver.h
@brief    Waveform Driver
@mainpage Waveform Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   WAVEFORM
@brief      Waveform Click Driver
@{

| Global Library Prefix | **WAVEFORM** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **apr 2018.**      |
| Developer             | **Dusan Poluga**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _WAVEFORM_H_
#define _WAVEFORM_H_

/** 
 * @macro T_WAVEFORM_P
 * @brief Driver Abstract type 
 */
#define T_WAVEFORM_P    const uint8_t*

/** @defgroup WAVEFORM_COMPILE Compilation Config */              /** @{ */

   #define   __WAVEFORM_DRV_SPI__                            /**<     @macro __WAVEFORM_DRV_SPI__  @brief SPI driver selector */
//  #define   __WAVEFORM_DRV_I2C__                            /**<     @macro __WAVEFORM_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __WAVEFORM_DRV_UART__                           /**<     @macro __WAVEFORM_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup WAVEFORM_VAR Variables */                           /** @{ */

extern const uint16_t WAVEFORM_CR_B28_BITMASK     ;
extern const uint16_t WAVEFORM_CR_HLB_BITMASK     ;
extern const uint16_t WAVEFORM_CR_FSELECT_BITMASK ;
extern const uint16_t WAVEFORM_CR_PSELECT_BITMASK ;
extern const uint16_t WAVEFORM_CR_RESET_BITMASK   ;
extern const uint16_t WAVEFORM_CR_SLEEP1_BITMASK  ;
extern const uint16_t WAVEFORM_CR_SLEEP12_BITMASK ;
extern const uint16_t WAVEFORM_CR_OPBITEN_BITMASK ;
extern const uint16_t WAVEFORM_CR_DIV2_BITMASK    ;
extern const uint16_t WAVEFORM_CR_MODE_BITMASK    ;


                                                                       /** @} */
/** @defgroup WAVEFORM_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup WAVEFORM_INIT Driver Initialization */              /** @{ */

#ifdef   __WAVEFORM_DRV_SPI__
void waveform_spiDriverInit(T_WAVEFORM_P gpioObj, T_WAVEFORM_P spiObj);
#endif
                                                                       /** @} */
/** @defgroup WAVEFORM_FUNC Driver Functions */                   /** @{ */

/**
 * Generic SPI function for writing 16bit values
 * to the waveform generating chip.
 */
void waveform_writeReg(uint16_t regSetting);

/**
 * Function for incrementing the amplitude by 1.
 */
void waveform_digipotInc();

/**
 * Function for decrementing the amplitude by 1.
 */
void waveform_digipotDec();

/**
 * Output a triangle wave and set the frequency
 * by passing the raw 24bit value.
 */
void waveform_triangleOutput(uint32_t f);

/**
 * Output a square wave and set the frequency
 * by passing the raw 24bit value.
 */
void waveform_squareOutput(uint32_t f);

/**
 * Output a sine wave and set the frequency
 * by passing the raw 24bit value.
 */
void waveform_sineOutput(uint32_t f);

                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Waveform_STM.c
    @example Click_Waveform_TIVA.c
    @example Click_Waveform_CEC.c
    @example Click_Waveform_KINETIS.c
    @example Click_Waveform_MSP.c
    @example Click_Waveform_PIC.c
    @example Click_Waveform_PIC32.c
    @example Click_Waveform_DSPIC.c
    @example Click_Waveform_AVR.c
    @example Click_Waveform_FT90x.c
    @example Click_Waveform_STM.mbas
    @example Click_Waveform_TIVA.mbas
    @example Click_Waveform_CEC.mbas
    @example Click_Waveform_KINETIS.mbas
    @example Click_Waveform_MSP.mbas
    @example Click_Waveform_PIC.mbas
    @example Click_Waveform_PIC32.mbas
    @example Click_Waveform_DSPIC.mbas
    @example Click_Waveform_AVR.mbas
    @example Click_Waveform_FT90x.mbas
    @example Click_Waveform_STM.mpas
    @example Click_Waveform_TIVA.mpas
    @example Click_Waveform_CEC.mpas
    @example Click_Waveform_KINETIS.mpas
    @example Click_Waveform_MSP.mpas
    @example Click_Waveform_PIC.mpas
    @example Click_Waveform_PIC32.mpas
    @example Click_Waveform_DSPIC.mpas
    @example Click_Waveform_AVR.mpas
    @example Click_Waveform_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __waveform_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */
