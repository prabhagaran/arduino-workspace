#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2   // DS18B20 data pin

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();

  Serial.println("DS18B20 Smoke Test Started...");
}

void loop() {
  sensors.requestTemperatures();  // Ask sensor to measure

  float tempC = sensors.getTempCByIndex(0);

  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: DS18B20 not detected!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" °C");
  }

  delay(1000);
}
