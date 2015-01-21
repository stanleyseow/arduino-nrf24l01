#include "MirfSpiDriver.h"

#ifndef __MIRF_HARDWARE_SPI_DRIVER
#define __MIRF_HARDWARE_SPI_DRIVER 

#include <SPI.h>

class MirfHardwareSpiDriver : public MirfSpiDriver {

	public: 
		uint8_t transfer(uint8_t data) {
			return SPI.transfer(data);
		}

		void begin() {
			SPI.begin();
			SPI.setDataMode(SPI_MODE0);
			SPI.setClockDivider(SPI_CLOCK_DIV2);
		}

		void end() {
		}
};

MirfHardwareSpiDriver MirfHardwareSpi;

#endif
