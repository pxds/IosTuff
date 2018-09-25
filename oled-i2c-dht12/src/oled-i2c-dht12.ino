#include <Arduino.h>
#include <Wire.h>
#include "DHT12-lib.h"
#include "U8x8lib.h"

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 	     

DHT12 sensor;

void setup(void)
{ 
  Wire.begin();
  u8x8.begin();
  u8x8.setPowerSave(0);  
}

void loop(void)
{
  sensor.read();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Humidity Sensor");

  // input the int value into a const char *, here we use 
  // (PGM_P) and the F macro to save RAM, using flash to
  // hold the string data instead
  char strOut[8];

  #if defined(ARDUINO_AVR_UNO)
  int humidityInt = sensor.get_humidity_integer();
  int humidityDec = sensor.get_humidity_decimal();
  sprintf_P(strOut, (PGM_P)F("%d.%d%%"), humidityInt, humidityDec);
  #else
  float humidity = sensor.get_humidity();
  sprintf_P(strOut, (PGM_P)F("%f"), humidity);
  #endif

  Serial.println(strOut);

  int xPos = 3;

  u8x8.draw2x2String(xPos,5,strOut);

  delay(1000);
}