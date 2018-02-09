#include <SPI.h>
#include "MAX5216.h"

MAX5216::MAX5216(){
  _CS = 10;
  _CLR = 7;
  _VREF = 2500;//mV
  _INCREMENT = 10;
}
MAX5216::MAX5216(uint8_t cs_pin,uint8_t clr_pin,int vref,int increment){
	_CS = cs_pin;
	_CLR = clr_pin;
	_VREF = vref;
  _INCREMENT = increment;
}

void MAX5216::viewSettings(){
  Serial.println(_CS);
  Serial.println(_CLR);
  Serial.println(_VREF);
  Serial.println(_INCREMENT);
}

unsigned int MAX5216::getCode(unsigned int outputVoltage){
  outputVoltage = (outputVoltage) % (_VREF+_INCREMENT);
  unsigned int code = ((float)outputVoltage/_VREF) * MAX_VAL;
  return code;
}

void MAX5216::updateDAC(unsigned int inputCode)
{
  unsigned int first14 = inputCode & 0xFFFC;
  unsigned int last2 = inputCode & 0x0003;
  unsigned int word16 = (first14 >> 2)  | WRITE;
  uint8_t word8 = (last2 << 6);
  byte byte1 = (word16 & ~(0x00FF)) >> 8;
  byte byte2 = (word16 & ~(0xFF00));
  byte byte3 = word8;
  
  digitalWrite(_CS,LOW); //D10 low
  SPI.transfer(byte1);
  SPI.transfer(byte2);
  SPI.transfer(byte3);

//Serial.println("start");
//Serial.println(word16,BIN);
//Serial.println(word8,BIN);
//Serial.println("end");
//Serial.println(byte1,BIN);
//Serial.println(byte2,BIN);
//Serial.println(byte3,BIN);
  digitalWrite(_CS,HIGH);
  delayMicroseconds(100);
}

