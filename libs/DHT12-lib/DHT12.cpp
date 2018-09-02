#include <Wire.h>
#include <DHT12.h>

#ifdef ESP8266
void DHT12::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
}
#endif

void DHT12::begin()
{
  Wire.begin();
}

int8_t DHT12::read()
{

}

int DHT12::_readSensor()
{

}