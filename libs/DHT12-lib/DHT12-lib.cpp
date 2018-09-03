#include <Wire.h>
#include <DHT12-lib.h>

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

bool DHT12::read()
{
  return 0;
}

RegisterDht DHT12::read_sensor()
{

  RegisterDht placeholder;
  return placeholder;
}

float DHT12::get_temperature()
{
  return 0;
}

float DHT12::get_humidity()
{
  return 0;
}
