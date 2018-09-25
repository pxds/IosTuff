#include <Arduino.h>
#include "U8x8lib.h"

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 	     

int count = 0;

void setup(void)
{ 
  u8x8.begin();
  u8x8.setPowerSave(0);  
}

void loop(void)
{
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Hello World!");
  u8x8.drawString(0,2,"Counter: ");

  // input the int value into a const char *, here we use 
  // (PGM_P) and the F macro to save RAM, using flash to
  // hold the string data instead
  char strOut[8];
  sprintf_P(strOut, (PGM_P)F("%d"), count);

  // lets try to center the counter
  int countDigits = CountDigits(count);

  // the display is 16px wide
  int xPos = 7 - countDigits;

  u8x8.draw2x2String(xPos,5,strOut);
  
  count++;
  digitalWrite(13, 1);
  delay(500);
  digitalWrite(13, 0);
  delay(500);
}

int CountDigits(int number)
{
	int numDigits = 0;

	while ( number /= 10 )
   		numDigits++;

	return numDigits;
}