#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);   // ESP32 I2C pins

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED init failed");
    while (1);
  }

  display.clearDisplay();

  // ---- Header (Yellow zone) ----
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("EGG INCUBATOR");

  display.drawLine(0, 15, 127, 15, SSD1306_WHITE);

  // ---- Body (Blue zone) ----
  display.setCursor(0, 20);
  display.println("System Booting...");
  display.println("OLED OK");

  display.display();
}

void loop() {
  // nothing yet
}
