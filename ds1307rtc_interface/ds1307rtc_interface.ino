#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22);   // ESP32 I2C

  if (!rtc.begin()) {
    Serial.println("RTC NOT FOUND");
    while (1);
  }

  Serial.println("RTC FOUND");

  // ⚠️ Run this ONCE to set time, then comment it out
  if (!rtc.isrunning()) {
    Serial.println("RTC not running, setting time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  Serial.printf(
    "Time: %02d:%02d:%02d  Date: %02d/%02d/%04d\n",
    now.hour(),
    now.minute(),
    now.second(),
    now.day(),
    now.month(),
    now.year()
  );

  delay(1000);
}
