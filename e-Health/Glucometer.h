/*******************************************************
*                                                      *
*   Criado em: Thu 12/Oct/2017,  15:19 hs              *
*   Instituicao: Universidade Federal do Ceará         *
*   Autor: Robert Cabral                               *
*   email: robertcabral@alu.ufc.br                     *
*                                                      *
********************************************************/
#ifndef MBED_GLUCOMETER_H
#define MBED_GLUCOMETER_H

#include "platform/platform.h"
#include "mbed.h"
#include <vector>
#include <Serial.h>

namespace mbed {

  struct glucoseData {
      uint8_t year;
	    uint8_t month;
	    uint8_t day;
	    uint8_t hour;
	    uint8_t minutes;
	    uint8_t glucose;
	    uint8_t meridian;
  };

  class Glucometer {
    private:
      DigitalOut enable;
      uint8_t length;
      std::vector<glucoseData> data;
      Serial serial;

    public:
      Glucometer(PinName pin);
      std::vector<glucoseData> read();
      int getLength();

  };

}
#endif
