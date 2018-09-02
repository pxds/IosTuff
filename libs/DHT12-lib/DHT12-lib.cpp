
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
  // READ SENSOR
  int status = _readSensor();
  if (status < 0) return status;

  // CONVERT AND STORE
  humidity = bits[0] + bits[1] * 0.1;
  temperature = bits[2] + (bits[3] & 0x7F) * 0.1;
  if (bits[3] & 0x80)
  {
    temperature = -temperature;
  }

  // TEST CHECKSUM
  uint8_t checksum = bits[0] + bits[1] + bits[2] + bits[3];
  if (bits[4] != checksum)
  {
    return DHT12_ERROR_CHECKSUM;
  }

  return DHT12_OK;
}

int DHT12::_readSensor()
{
  /* DHT12 I²C Communication
  It has 5 internal registers that holds the sensor's information
  ADDR  R/W  DESCRIPTION
  0x00   R   Humidity Integer                     
  0x01   R   Humidity Float Decimals 
  0x02   R   Temperature Integer                  
  0x03   R   Temperature Float Decimals                   
  0x04   R   Checksum                 

  */
  Wire.beginTransmission(DHT12_ADDRESS);
  Wire.write(0);
  int rv = Wire.endTransmission();
  if (rv < 0) return rv;

  // GET DATA
  const uint8_t length = 5;
  int bytes = Wire.requestFrom(DHT12_ADDRESS, length);
  if (bytes == 0) return DHT12_ERROR_CONNECT;
  if (bytes < length) return DHT12_MISSING_BYTES;

  for (int i = 0; i < bytes; i++)
  {
    bits[i] = Wire.read();
  }

  return bytes;
}