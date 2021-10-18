#include <Wire.h>
#include <LoRa.h>
#include "util.h"

#define BAUD_RATE 9600

void setup() {
  Serial.begin(BAUD_RATE);
  lora_init();
  setRadioFailsafe();
}

void loop() {
  getRadioInput();
  printRadioData();

}



void lora_init() {
  Serial.println("Attempting to start LoRa...");
  LoRa.setPins(SS,RST,DI0); // set correct pins for logic level converters etc
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);              // loop forever if LoRa init fails
  }
  Serial.println("LoRa started successfully!");
  Serial.println("RECEIVER init ok");
}

void getRadioInput() {
  int packetSize = LoRa.parsePacket();
  if(packetSize == PACKET_SIZE) {
    while(LoRa.available()) {
      for(int i=0; i<PACKET_SIZE; i++) {
        data_in[i] = LoRa.read();
      }
    }
  }
}
