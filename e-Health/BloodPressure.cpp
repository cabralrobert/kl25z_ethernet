#include "mbed.h"
#include "BloodPressure.h"
#include <vector>

namespace mbed{

BloodPressure::BloodPressure() : length(0), serial(USBTX,USBRX,19200) {
}

std::vector<bloodPressureData> BloodPressure::read(){

    unsigned char _data = ' ';
    int ia=0;


    serial.putc(0xAA);
    wait(0.000001);
    serial.putc(0x55);
    wait(0.000001);
    serial.putc(0x88);
    wait(2.5);

    serial.printf("\n");

    if(serial.readable() > 0){
        for (int i = 0; i<4; i++){ // Read four dummy data
            serial.getc();
        }

        while(_data != 0xD1){
            if (ia==0){
                _data = serial.getc();
            }

            bloodPressureDataVector[length].year = swap(_data);
            bloodPressureDataVector[length].month = swap(serial.getc());
            bloodPressureDataVector[length].day = swap(serial.getc());
            bloodPressureDataVector[length].hour = swap(serial.getc());
            bloodPressureDataVector[length].minutes = swap(serial.getc());
            bloodPressureDataVector[length].systolic = swap(serial.getc());
            bloodPressureDataVector[length].diastolic = swap(serial.getc());
            bloodPressureDataVector[length].pulse = swap(serial.getc());
            this->length++;
            ia=1;
            for (int i = 0; i<4; i++){ // CheckSum 1
                serial.getc();
            }

            _data = serial.getc();
        }
    }

    serial.putc('N');
    for (int i = 0; i<3; i++){ // CheckSum 2
        serial.getc();
    }
    return this->bloodPressureDataVector;
}

char BloodPressure::swap(char _data){
        char highBits = (_data & 0xF0) / 16;
        char lowBits =  (_data & 0x0F) * 16;
        return ~(highBits + lowBits);
}

int BloodPressure::getLength(){
    return this->length;
}

}
