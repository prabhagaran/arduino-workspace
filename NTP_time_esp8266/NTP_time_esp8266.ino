#include <ESP8266WiFi.h>
#include <time.h>

// WiFi
const char* ssid = "ST - LAB";
const char* password = "simtestlab";

// NTP
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;   // IST
const int daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");

  // Start NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Waiting for NTP time...");

  // Wait until time is set
  time_t now = time(nullptr);
  while (now < 100000) {   // time not set yet
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }

  Serial.println("\nTime synchronized!");
}

void loop() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  char buf[30];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);

  Serial.print("Current Time: ");
  Serial.println(buf);

  delay(1000);
}
