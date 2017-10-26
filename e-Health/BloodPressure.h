/*******************************************************
*                                                      *
*   Criado em: Thu 20/Oct/2017,  09:16 hs              *
*   Instituicao: Universidade Federal do Ceará         *
*   Autor: Robert Cabral                               *
*   email: robertcabral@alu.ufc.br                     *
*                                                      *
********************************************************/
#ifndef MBED_BLOODPRESSURE_H
#define MBED_BLOODPRESSURE_H

#include "platform/platform.h"
#include "mbed.h"
#include <vector>
#include <Serial.h>

namespace mbed {

  struct bloodPressureData {
	uint8_t year; 
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minutes;
	uint8_t systolic;
	uint8_t diastolic;
	uint8_t pulse;
  };

  class BloodPressure {
    private:
      uint8_t length;     
      std::vector<bloodPressureData> bloodPressureDataVector;
      char swap(char _data);
      Serial serial;

    public:
      BloodPressure();
      std::vector<bloodPressureData> read();
      int getLength();

  };

}
#endif
