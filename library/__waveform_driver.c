/*
    __waveform_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__waveform_driver.h"
#include "__waveform_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __WAVEFORM_DRV_I2C__
static uint8_t _slaveAddress;
#endif

// Digipot 



// Waveform 

static uint8_t __dumyRecBuf[5];
static uint16_t WAVEFORM_CONTROL_REG;
const uint16_t WAVEFORM_CR_B28_BITMASK     = 1<<13;
const uint16_t WAVEFORM_CR_HLB_BITMASK     = 1<<12;
const uint16_t WAVEFORM_CR_FSELECT_BITMASK = 1<<11;
const uint16_t WAVEFORM_CR_PSELECT_BITMASK = 1<<10;
const uint16_t WAVEFORM_CR_RESET_BITMASK   = 1<<8 ;
const uint16_t WAVEFORM_CR_SLEEP1_BITMASK  = 1<<7 ;
const uint16_t WAVEFORM_CR_SLEEP12_BITMASK = 1<<6 ;
const uint16_t WAVEFORM_CR_OPBITEN_BITMASK = 1<<5 ;
const uint16_t WAVEFORM_CR_DIV2_BITMASK    = 1<<3 ;
const uint16_t WAVEFORM_CR_MODE_BITMASK    = 1<<1 ;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __WAVEFORM_DRV_SPI__

void waveform_spiDriverInit(T_WAVEFORM_P gpioObj, T_WAVEFORM_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
    hal_gpio_csSet(1);
    hal_gpio_rstSet(1);
    hal_gpio_pwmSet(1);
}

#endif

void waveform_digipotDec()
{
    uint8_t transferBuff[2];
    uint8_t tmp[2];
    transferBuff[0] = 0x1F;
    
    hal_gpio_csSet(0);
    Delay_1ms();
    hal_spiTransfer(transferBuff,tmp,1);
    Delay_1ms();
    hal_gpio_csSet(1);
}

void waveform_digipotInc()
{
    uint8_t transferBuff[2];
    uint8_t tmp[2];
    transferBuff[0] = 0x07;
    
    hal_gpio_csSet(0);
    Delay_1ms();
    hal_spiTransfer(transferBuff,tmp,1);
    Delay_1ms();
    hal_gpio_csSet(1);
}

void waveform_writeReg(uint16_t regSetting)
{
    uint8_t temp[3];

    hal_gpio_rstSet(0);
    Delay_1ms();
    temp[0] = (uint8_t)(regSetting>>8);
    temp[1] = (uint8_t)(regSetting);
    hal_spiTransfer( &temp, &__dumyRecBuf[0], 2 );
    hal_gpio_rstSet(1);
}

void waveform_writeFreqency(uint32_t f)
{
      uint32_t calc    = 0;
      uint16_t FEKREG0 = 0;
      uint16_t FEKREG1 = 0;

      FEKREG0 = f & 0x7FFF;
      FEKREG1 = (f>>14) & 0x7FFF;
     
      waveform_writeReg(0x0000);
      waveform_writeReg(0x8000|FEKREG0);

      waveform_writeReg(0x1000);
      waveform_writeReg(0x4000|FEKREG1);
}

void waveform_sineOutput(uint32_t f)
{
    waveform_writeFreqency(f);
    waveform_writeReg(0x2100);
    waveform_writeReg(0x2000);
}

void waveform_triangleOutput(uint32_t f)
{
    waveform_writeFreqency(f);
    WAVEFORM_CONTROL_REG = WAVEFORM_CR_B28_BITMASK | WAVEFORM_CR_MODE_BITMASK;
    waveform_writeReg(WAVEFORM_CONTROL_REG);
}

void waveform_squareOutput(uint32_t f)
{
    waveform_writeFreqency(f);
    WAVEFORM_CONTROL_REG = WAVEFORM_CR_B28_BITMASK | WAVEFORM_CR_DIV2_BITMASK | WAVEFORM_CR_OPBITEN_BITMASK;
    waveform_writeReg(WAVEFORM_CONTROL_REG);
}
/* ----------------------------------------------------------- IMPLEMENTATION */







/* -------------------------------------------------------------------------- */
/*
  __waveform_driver.c

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
