![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Waveform Click

- **CIC Prefix**  : WAVEFORM
- **Author**      : Dusan Poluga
- **Verison**     : 1.0.0
- **Date**        : apr 2018.

---


### Software Support

We provide a library for the Waveform Click on our [LibStock](https://libstock.mikroe.com/projects/view/2614/waveform-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library contains generic functions for controlling the waveform and frequency
output of the click board.

Key functions :

- ```void waveform_sineOutput(uint32_t f)``` - Function for setting the sine wave output.
- ```void waveform_triangleOutput(uint32_t f)``` - Function for setting the triangle wave output.
- ```void waveform_squareOutput(uint32_t f)``` - Function for setting the square wave output.

**Examples Description**

Description :

The application is composed of three sections :

- System Initialization - Initialize the GPIO and communication structures.
- Application Initialization - Initialize the communication interface and
                               configure the click board.
- Application Task - Predefined characters are inputed from the serial port.
  Depending on the character sent the signal frequency, waveform or amplitude 
  will be changed.

```.c
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
```

Additional Functions :

- uint32_t waveform_aproxFreqcalculation(float freqency) - This function is used
  to calculate the aproximate value that will be written to the frequency set
  register.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2614/waveform-click) page.

Other mikroE Libraries used in the example:

- SPI library
- UART library
- Conversions library
- C_Sring library

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
