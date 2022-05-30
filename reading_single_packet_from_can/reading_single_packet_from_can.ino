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

void setup() {
  Serial.begin(115200);
  //wait for serial to begin
  Serial.println("CAN Receiver");  
  // start the CAN bus at 500 kbps
  if (!CAN.begin(CAN_SPEED)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  //only read packets of the given id
  CAN.filter(id);
  //output pins (4 is rx, 5 is tx) refers to gpio
  CAN.setPins(4, 5);
  CAN.onReceive(onReceive);
}

//int hex2int(char ch[]){
//  for(int i = 0; i < ch.lent)
//}

void onReceive(int packetSize){
  int numBytes = CAN.available();
  byte buff[numBytes];
  for(int i =0; i < 8; i ++){
    buff[i] = CAN.read();
  }
  int tps = int(buff[offset+1] + (buff[offset]<<8));
  Serial.println(tps);
  int value = (int) tps;
  Serial.print("value: ");
  Serial.println(value);
}

void loop() {

}
