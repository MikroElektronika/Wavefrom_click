/*
Example for Waveform Click

    Date          : apr 2018.
    Author        : Dusan Poluga

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initialize the GPIO and communication structures.
- Application Initialization - Initialize the communication interface and
                               configure the click board.
- Application Task - Predefined characters are inputed from the serial port.
  Depending on the character sent the signal frequency, waveform or amplitude 
  will be changed.

Additional Functions :

- uint32_t waveform_aproxFreqcalculation(float freqency) - This function is used
  to calculate the aproximate value that will be written to the frequency set
  register.

*/

#include "Click_Waveform_types.h"
#include "Click_Waveform_config.h"

uint32_t freq;
const uint8_t waveform_cmd[9] = { '+','-','S','s','T','t','Q','q' };

uint32_t waveform_aproxFreqcalculation(float freqency)
{
        uint32_t calculation;
        float WAVEFORM_OSC_FREQ = 25000000.0;
        float WVVEFORM_CONSTANT = 268435456.0; // 2^28
        
        calculation = freqency * ( WVVEFORM_CONSTANT / WAVEFORM_OSC_FREQ );
        
        return calculation;
}

void systemInit()
{
     mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_OUTPUT );
     mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN,  _GPIO_OUTPUT );
     mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
     
     mikrobus_spiInit( _MIKROBUS1, &_WAVEFORM_SPI_CFG[0] );
     mikrobus_logInit( _LOG_USBUART_A, 57600 );
     Delay_ms( 100 );
}

void applicationInit()
{
     waveform_spiDriverInit( (T_WAVEFORM_P)&_MIKROBUS1_GPIO, (T_WAVEFORM_P)&_MIKROBUS1_SPI );
     mikrobus_logWrite("System initialized",_LOG_LINE);
     Delay_ms( 100 );
     
     freq = waveform_aproxFreqcalculation(5000);
     waveform_squareOutput(freq);
     freq=0;
}

void applicationTask()
{
    char rxDat;
    uint32_t freqTmp;
 
    if(UART_Rdy_Ptr())
    {
       rxDat = UART_Rd_Ptr();
       mikrobus_logWrite(&rxDat,_LOG_BYTE);
    }
    if(rxDat>0)
    {
       switch(rxDat)
       {
           case waveform_cmd[0]: {
                                     waveform_digipotInc();
                                     rxDat = 0;
                                     break;
                                 }
           case waveform_cmd[1]: {
                                     waveform_digipotDec();
                                     rxDat = 0;
                                     break;
                                 }
           case waveform_cmd[2]: {
                                     freq += 1;
                                     freqTmp = freq << 14;
                                     waveform_sineOutput(freqTmp);
                                     rxDat = 0;
                                     break;
                                 }
           case waveform_cmd[3]: {
                                     freq -= 1;
                                     freqTmp = freq << 14;
                                     waveform_sineOutput(freqTmp);
                                     rxDat = 0;
                                     break;
                                 }
           case waveform_cmd[4]: {
                                     freq += 1;
                                     freqTmp = freq << 14;
                                     waveform_triangleOutput(freqTmp);
                                     rxDat = 0;
                                     break;
                                 }
           case waveform_cmd[5]: {
                                     freq -= 1;
                                     freqTmp = freq << 14;
                                     waveform_triangleOutput(freqTmp);
                                     rxDat = 0;
                                     break;
                                 }
           case waveform_cmd[6]: {
                                     freq += 1;
                                     freqTmp = freq << 14;
                                     waveform_squareOutput(freqTmp);
                                     rxDat = 0;
                                     break;
                                 }
           case waveform_cmd[7]: {
                                     freq -= 1;
                                     freqTmp = freq << 14;
                                     waveform_squareOutput(freqTmp);
                                     rxDat = 0;
                                     break;
                                 }
           default : {
                         break;
                     }
       }
    }
     rxDat = 0;
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}
