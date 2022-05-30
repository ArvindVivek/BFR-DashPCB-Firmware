#include <Adafruit_NeoPixel.h>

#define PIN 32

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(17, PIN, NEO_GRB + NEO_KHZ800);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t orange = pixels.Color(255, 140, 0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t white = pixels.Color(255, 255, 255);

void setup() {
  pixels.begin();
  //pixels.setBrightness(50);
  pixels.fill(0);
  pixels.show();
  delay(200);
  for (int i = 0; i <= 8; i++) {
    //pixels.fill(0,0,0);
    if (i < 4) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Green
      pixels.setPixelColor(16 - i, pixels.Color(0, 255, 0));
    } else if (i < 7) { 
      pixels.setPixelColor(i, pixels.Color(255, 140, 0)); // Orange
      pixels.setPixelColor(16 - i, pixels.Color(255, 140, 0));
    } else {
       pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Red
       pixels.setPixelColor(16 - i, pixels.Color(255, 0, 0));
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(200 - i*20);
  }
  delay(400);
  for (int i = 8; i >= 0; i--) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.setPixelColor(16 - i, pixels.Color(0, 0, 0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(200 - i*20);
  }
  pixels.fill(0);
  pixels.show();
  delay(200);
}

void loop() {
    for (int i = 0; i < 17; i++){
    if (i < 3){
      pixels.setPixelColor(i, red);
      pixels.show();
    } else if (i < 6){
      pixels.setPixelColor(i, orange);
      pixels.show();
    } else {
      pixels.setPixelColor(i, green);
      pixels.show();
    }
  }
}
