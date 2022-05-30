#include <Adafruit_NeoPixel.h>
#include <CAN.h>

//speed of the can network
int CAN_SPEED = 1E6;
//id we want
int id = 0x640;
//can offset
int offset = 6;
//scaling factor
float scaling = 0.1;
//length of important bytes
int len = 3;

volatile int pwm_value = 0;
volatile int prev_time = 0;
int max_cycle_shifting = 100;
int max_cycle_bb = 100;
int num_shifting = 17;
int num_bb = 11;
int bb_value;
int max_rpm = 1000;
int pot_pin = 27;
int shifting_lights_pin = 32;
int bb_lights_pin = 33;
int rx_pin = 4;
int tx_pin = 5;
Adafruit_NeoPixel shifting_lights = Adafruit_NeoPixel(17, shifting_lights_pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bb_lights = Adafruit_NeoPixel(11, bb_lights_pin, NEO_GRB + NEO_KHZ800);
uint32_t red = shifting_lights.Color(255, 0, 0);
uint32_t orange = shifting_lights.Color(255, 140, 0);
uint32_t green = shifting_lights.Color(0, 255, 0);
uint32_t white = shifting_lights.Color(255, 255, 255);
uint32_t purple = bb_lights.Color(148, 0, 211);
int shift_value;

void setup() {
  Serial.begin(115200);
  // start the CAN bus at 500 kbps
  if (!CAN.begin(CAN_SPEED)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  shifting_lights.begin();
  shifting_lights.setBrightness(50);
  bb_lights.begin();
  bb_lights.setBrightness(50);
  pinMode(pot_pin, INPUT);
  //only read packets of the given id
  CAN.filter(id);
  //output pins (4 is rx, 5 is tx) refers to gpio
  CAN.setPins(rx_pin, tx_pin);
  CAN.onReceive(onReceive);
  //pinMode(16, INPUT);
  startUp();
}

void onReceive(int packetSize){
  int numBytes = CAN.available();
  byte buff[numBytes];
  for(int i =0; i < 8; i ++){
    buff[i] = CAN.read();
  }
  int tps = int(buff[offset+1] + (buff[offset]<<8));
  shift_value = tps;
}

void loop() {

  bb_value = analogRead(pot_pin);
  shifting_lights.fill(0);
  shifting_lights.show();
  /*
  for (int j = 0; j < num_bb; j++) {
    bb_lights.setPixelColor(j, bb_lights.Color(148, 0, 211));
    bb_lights.show();
  }*/

  int lights = (shift_value * num_shifting) / max_rpm;
 
  for (int i = num_shifting - 1; i >= num_shifting - lights; i--) {
    if (i < 3) {
      shifting_lights.setPixelColor(i, red);
      shifting_lights.show();
    } else if (i < 6) {
      shifting_lights.setPixelColor(i, orange);
      shifting_lights.show();
    } else {
      shifting_lights.setPixelColor(i, green);
      shifting_lights.show();
    }
  }
  
}

void startUp() {
  shifting_lights.setBrightness(50);
  shifting_lights.fill(0);
  shifting_lights.show();
  delay(200);
  for (int i = 0; i <= 8; i++) {
    //pixels.fill(0,0,0);
    if (i < 4) {
      shifting_lights.setPixelColor(i, shifting_lights.Color(0, 255, 0)); // Green
      shifting_lights.setPixelColor(16 - i, shifting_lights.Color(0, 255, 0));
    } else if (i < 7) {
      shifting_lights.setPixelColor(i, shifting_lights.Color(255, 140, 0)); // Orange
      shifting_lights.setPixelColor(16 - i, shifting_lights.Color(255, 140, 0));
    } else {
      shifting_lights.setPixelColor(i, shifting_lights.Color(255, 0, 0)); // Red
      shifting_lights.setPixelColor(16 - i, shifting_lights.Color(255, 0, 0));
    }
    shifting_lights.show(); // This sends the updated pixel color to the hardware.
    delay(200 - i * 20);
  }
  delay(400);
  for (int i = 8; i >= 0; i--) {
    shifting_lights.setPixelColor(i, shifting_lights.Color(0, 0, 0));
    shifting_lights.setPixelColor(16 - i, shifting_lights.Color(0, 0, 0));
    shifting_lights.show(); // This sends the updated pixel color to the hardware.
    delay(200 - i * 20);
  }
  shifting_lights.fill(0);
  shifting_lights.show();
  delay(200);
}
