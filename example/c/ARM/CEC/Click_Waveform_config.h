#include "Click_Waveform_types.h"

const uint32_t _WAVEFORM_SPI_CFG[ 3 ] = 
{ 
	1000000,  
	_SPI_MSB_FIRST, 
	_SPI_CLK_IDLE_HIGH | 
	_SPI_SAMPLE_DATA_RISING_EDGE 
};
