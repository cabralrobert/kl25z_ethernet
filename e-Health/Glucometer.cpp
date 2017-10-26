#include "mbed.h"
#include "Glucometer.h"
#include <vector>

namespace mbed{

Glucometer::Glucometer(PinName pin = D5) : enable(pin), serial(USBTX,USBRX,1200) {
}

std::vector<glucoseData> Glucometer::read(){
  wait(0.1);
  this->enable.write(1);
  wait(0.01);

  serial.putc('U');
//  serial.printf("U");
  wait(1);

  serial.printf("\n");
  if(serial.readable() > 0){
    this->length = serial.getc();
    serial.getc();

    for(int i = 0; i < length; i++){
      this->data[i].year     = serial.getc();
      this->data[i].month    = serial.getc();
      this->data[i].day      = serial.getc();
      this->data[i].hour     = serial.getc();
      this->data[i].minutes  = serial.getc();

      serial.getc();

      this->data[i].glucose  = serial.getc();
      this->data[i].meridian = serial.getc();

      serial.getc();
      serial.getc();
    }

    this->enable.write(0);
    return this->data;
  }

  serial.putc('N');
  this->enable.write(0);
  return this->data;
}

int Glucometer::getLength(){
  return this->length;
}

}
