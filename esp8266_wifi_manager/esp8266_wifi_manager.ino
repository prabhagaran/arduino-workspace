#include <ESP8266WiFi.h>
#include <WiFiManager.h>

void setup() {
  Serial.begin(115200);

  WiFiManager wm;

  // Optional: reset saved WiFi (for testing)
  // wm.resetSettings();

  bool res = wm.autoConnect("EggIncubator_Setup");

  if (!res) {
    Serial.println("Failed to connect");
    ESP.restart();
  }

  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
