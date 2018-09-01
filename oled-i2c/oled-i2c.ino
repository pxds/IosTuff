#include <Arduino.h>
#include <..\libs\U8g2_ID942\src\U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 	     

void setup(void)
{ 
  u8x8.begin();
  u8x8.setPowerSave(0);  
}

void loop(void)
{
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Hello World!");
  delay(2000);
}