/*
	DHT12 I²C Driver Library

	Based on https://github.com/RobTillaart/Arduino.git
*/

#ifndef DHT12LIB_H
#define DHT12LIB_H

#define DHT12_ADDRESS  ((uint8_t)0x5C)

class DHT12
{
public:

  #ifdef ESP8266
  void begin(uint8_t sda, uint8_t scl);
  #endif

  void begin();
  int8_t read();

private:
  float humidity;
  float temperature;

  int _readSensor();
};

#endif