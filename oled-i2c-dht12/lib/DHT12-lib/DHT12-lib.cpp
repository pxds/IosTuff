/*
  DHT12 I²C Driver Library
  Based on https://github.com/RobTillaart/Arduino.git

  @author Victor Praxedes
  @version 0.1 2/9/18
  
  # DHT12 Internal Data Registers
   It has 5 internal 1 byte registers that holds the sensor's information
      ADDR  R/W  DESCRIPTION
    - 0x00   R   Humidity Integer                     
    - 0x01   R   Humidity Float Decimals 
    - 0x02   R   Temperature Integer                  
    - 0x03   R   Temperature Float Decimals                   
    - 0x04   R   Checksum                 
   
  # DHT12 I²C Communication
   DHT12 expects the following byte sequence on the I²C bus
    - DEVICE ADDRESS > REGISTER ADDRESS
          (0x5C)        (0x00 - 0x04)

   It will then output the on the I²C bus the data inside its internal
   registers starting on the address provided on the last transaction
    - DATA REG 0x00 < DATA REG 0x02 < ... < DATA REG 0x04  
*/

#include <Wire.h>
#include <DHT12-lib.h>
#include <Arduino.h>


DHT12::DHT12()
{
  Wire.begin();

  this->dhtData.HumidityInteger = 0;   
  this->dhtData.HumidityFloat = 0;   
  this->dhtData.TemperatureInteger = 0;   
  this->dhtData.TemperatureFloat = 0;   
  this->dhtData.Checksum = 0;

  this->lastReadStatus = DhtStatus::NO_BYTES_READ;
}

#ifdef ESP8266
DHT12(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);

  this->dhtData.HumidityInteger = 0;   
  this->dhtData.HumidityFloat = 0;   
  this->dhtData.TemperatureInteger = 0;   
  this->dhtData.TemperatureFloat = 0;   
  this->dhtData.Checksum = 0;

  this->lastReadStatus = DhtStatus::NO_BYTES_READ;
}
#endif

bool DHT12::read()
{
  this->lastReadStatus = DhtStatus::NO_BYTES_READ;

  lastReadStatus = read_sensor();

  if(lastReadStatus != DhtStatus::SUCCESSFUL_READ)
    return false;    

  return true;
}

DhtStatus DHT12::read_sensor()
{
  Wire.beginTransmission(DHT12_ADDRESS);
  // address of the first register
  Wire.write(0x00);
  if (Wire.endTransmission() != 0) 
    return  DhtStatus::WIRE_LIB_ERROR;

  const uint8_t numRequestedBytes = 5;

  // requests ```numRequestedBytes``` bytes from the dht12
  int numAvailableBytes = Wire.requestFrom(DHT12_ADDRESS, numRequestedBytes);

  if (numAvailableBytes == 0) 
    return DhtStatus::NO_BYTES_READ;
  if (numAvailableBytes < numRequestedBytes)
    return DhtStatus::INCOMPLETE_READ;

  // read every byte available on the I²C
  uint8_t dhtRegister[numAvailableBytes];
  for (int i = 0; i < numAvailableBytes; i++)
    dhtRegister[i] = Wire.read();

  uint8_t checksum = dhtRegister[0] + dhtRegister[1] + dhtRegister[2] + dhtRegister[3];
  if (dhtRegister[4] != checksum)
    return DhtStatus::CHECKSUM_ERROR;

  this->dhtData.HumidityInteger = dhtRegister[0];   
  this->dhtData.HumidityFloat = dhtRegister[1];   
  this->dhtData.TemperatureInteger = dhtRegister[2];   
  this->dhtData.TemperatureFloat = dhtRegister[3];   
  this->dhtData.Checksum = dhtRegister[4];

  return DhtStatus::SUCCESSFUL_READ;
}

float DHT12::get_temperature()
{
  int intTemperature = this->dhtData.TemperatureInteger;
  int floatTemperature = this->dhtData.TemperatureFloat & 0x7F;

  return ((float)(intTemperature) + (float)(floatTemperature)*0.1);
}

float DHT12::get_humidity()
{
  int intHumidity = this->dhtData.HumidityInteger;
  int floatHumidity = this->dhtData.HumidityFloat;

  return ((float)(intHumidity) + (float)(floatHumidity)*0.1);
}

DhtStatus DHT12::get_last_status()
{
  return this->lastReadStatus;
}