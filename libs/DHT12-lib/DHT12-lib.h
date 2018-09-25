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
    - DATA REG 0x00 < DATA REG 0x01 < ... < DATA REG 0x04  
*/

#ifndef DHT12LIB_H
#define DHT12LIB_H

#define DHT12_ADDRESS  ((uint8_t)0x5C)

struct RegisterDht
{
	uint8_t HumidityInteger;
	uint8_t HumidityFloat;
	uint8_t TemperatureInteger;
	uint8_t TemperatureFloat;
	uint8_t Checksum;

};

enum DhtStatus
{
	SUCCESSFUL_READ,
	WIRE_LIB_ERROR,
	NO_BYTES_READ,
	INCOMPLETE_READ,
	CHECKSUM_ERROR
};

class DHT12
{
public:

	/**
	 * Default constructor
	 */
	DHT12();

	#ifdef ESP8266
	/**
	 * If using ESP8266, you have to declare which pins
	 * are going to be used for data (SDA) and clock (SCL)
	 * NOTE: they must have the PWM symbol ~ on the board
	 * Starts the I²C bus
	 * 
	 * @sda pin for data
	 * @scl pin for clock
	 */
	DHT12(uint8_t sda, uint8_t scl);
	#endif

	/**
	 * Starts the I²C bus, for most Arduinos you use
	 * pins A4 (SDA) and A5 (SCL)
	 */
	void begin();

	/**
	 * Tells the sensor to get the readings 
	 * 
	 * @return true for successful reading, false otherwise
	 */
	bool read();

	/**
	 * @return temperature value
	 */
	float get_temperature();

	/**
	 * @return temperature integer value
	 */
	int get_temperature_integer();

	/**
	 * @return temperature decimal value
	 */
	int get_temperature_decimal();

	/**
	 * @return humidity value
	 */
	float get_humidity();

	/**
	 * @return humidity integer value
	 */
	int get_humidity_integer();

	/**
	 * @return humidity decimal value
	 */
	int get_humidity_decimal();

	/**
	 * @return status of the last reading
	 */
	DhtStatus get_last_status();

private:
	/**
	 * Stores the sensor's last reading
	 */
	RegisterDht dhtData;

	DhtStatus lastReadStatus;

	/**
	 * Gets the sensor's reading using I²C
	 * @return sensor's registers data as a struct
	 */
	DhtStatus read_sensor();
};

#endif