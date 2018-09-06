#include "../libs/DHT12-lib/DHT12-lib.h"
#include <Wire.h>

DHT12 sensor;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  delay(2000);

  Serial.println("Status,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  sensor.read();
  Serial.print(sensor.get_last_status());
  Serial.print(",\t");
  Serial.print(sensor.get_humidity(), 1);
  Serial.print("%,\t");
  Serial.println(sensor.get_temperature(), 1);

  delay(2000);
}