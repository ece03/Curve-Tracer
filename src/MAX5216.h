#ifndef MAX5216_H_
#define MAX5216_H_
#define MAX_VAL 65535
#define WRITE 0x4000
#include "Arduino.h"

class MAX5216{
  public:
    MAX5216();
    MAX5216(uint8_t cs_pin, uint8_t clr_pin, int vref,int increment);
    void viewSettings();
    unsigned int getCode(unsigned int outputVoltage);
    void updateDAC(unsigned int inputCode);
  private:
    uint8_t _CS;
    uint8_t _CLR;
    int _VREF;
    int _INCREMENT;
};


#endif //MAX5216_H_
