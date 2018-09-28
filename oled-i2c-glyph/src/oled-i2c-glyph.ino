#include "U8g2lib.h"     
#include "DHT12-lib.h"
#include <Wire.h>
#include <XBM_Repo.h>

#define FONT_HEIGHT 10
#define NUM_SAMPLES 50

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
DHT12 sensor;

int test = 95;

void setup(void) 
{
 	u8g2.begin();
 	Wire.begin();
 	pinMode(A0, INPUT);
}

void loop(void) 
{
	int x = 0;
	int y = 0;
	int w = 127;
	int h = 63;

	float humidity = 0.0;
	float temperature = 0.0;
	int lux = 0;

	char humidityStr[6];
	char temperatureStr[6];
	char luxStr[8];

	u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_profont17_tf); 
 	u8g2.drawStr(12,17,"DESK STATUS");
    
    x = 23;
    y = 40;
    for(int i=0; i<2; i++)
    {
	    u8g2.drawCircle(x, y, 17-i, U8G2_DRAW_ALL);
	    u8g2.drawCircle(x+40, y, 17-i, U8G2_DRAW_ALL);
	    u8g2.drawCircle(x+80, y, 17-i, U8G2_DRAW_ALL);
    }
    u8g2.setFont(u8g2_font_open_iconic_thing_1x_t);
    u8g2.drawGlyph(x-3,y-2,0x48);
    u8g2.drawGlyph(x+40-3,y-2,0x4E);
    u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t);
    u8g2.drawGlyph(x+80-3,y-2,0x4D);


    for(int i=0; i<NUM_SAMPLES; i++)
    {
    	if(sensor.read())
	    {
			humidity += sensor.get_humidity();
			temperature += sensor.get_temperature();
		}
		lux += analogRead(A0)*2;

		delay(1000/NUM_SAMPLES);
    }

    humidity /= NUM_SAMPLES;
    temperature /= NUM_SAMPLES;
    lux /= NUM_SAMPLES;

    int humidityInt = (int)(humidity);
    int humidityDec = (int)(10.0*(humidity - (float)humidityInt));
    int temperatureInt = (int)(temperature);
    int temperatureDec = (int)(10.0*(temperature - (float)temperatureInt));

	sprintf_P(humidityStr, (PGM_P)F("%d.%d%%"), humidityInt, humidityDec);
	sprintf_P(temperatureStr, (PGM_P)F("%d.%d"), temperatureInt, temperatureDec);
	sprintf_P(luxStr, (PGM_P)F("%d lx"), lux);

    u8g2.setFont(u8g2_font_baby_tf);    
	u8g2.drawStr(13,49,humidityStr);
    u8g2.drawStr(52,49,temperatureStr);
    u8g2.drawCircle(69, 43, 1, U8G2_DRAW_ALL);
    u8g2.drawStr(71,49,"C");

	int luxNumDigits = CountDigits(lux);
    u8g2.drawStr(91+4/luxNumDigits,49,luxStr);

    u8g2.sendBuffer();
}

int CountDigits(int number)
{
	int numDigits = 0;

	while ( number /= 10 )
   		numDigits++;

	return numDigits;
}