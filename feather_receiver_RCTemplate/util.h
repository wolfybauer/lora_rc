#ifndef UTIL_H
#define UTIL_H


// BSFrance LoRa32u4 v1.1 / Adafruit feather 32u4
#define SCK     15   // GPIO5  -- SX1278's SCK
#define MISO    14   // GPIO19 -- SX1278's MISO
#define MOSI    16   // GPIO27 -- SX1278's MOSI
#define SS      8    // GPIO18 -- SX1278's CS
#define RST     4    // GPIO14 -- SX1278's RESET
#define DI0     7    // GPIO26 -- SX1278's IRQ(Interrupt Request)

// MISC defines
#define BAND      915E6     // radio frequency band USA= 915E6


// array to hold control data values
#define PACKET_SIZE 11
enum CONTROL_SIGNAL {
       L_xpos,    // left stick x
       L_ypos,    // left stick y
       L_click,   // left stick button
       R_xpos,    // right stick x
       R_ypos,    // right stick y
       R_click,   // right stick button
       P_pos,     // slider (pot) postion
       S_click,   // select button
       B_click,   // back button
       U_click,   // up button
       D_click    // down button
     };
byte data_in[PACKET_SIZE], data_translated[PACKET_SIZE];

// function to set all control data to defaults
void setRadioFailsafe() {
  // set all data to initial defaults
  data_in[L_xpos] = 127;
  data_in[L_ypos] = 127;
  data_in[L_click] = 0;
  data_in[R_xpos] = 127;
  data_in[R_ypos] = 127;
  data_in[R_click] = 0;
  data_in[P_pos] = 0;
  data_in[S_click] = 0;
  data_in[B_click] = 0;
  data_in[U_click] = 0;
  data_in[D_click] = 0;
}

void printRadioData() {
  Serial.print("LX:");
  Serial.print(data_in[L_xpos]);
  Serial.print(" ");
  Serial.print("LY:");
  Serial.print(data_in[L_ypos]);
  Serial.print(" ");
  Serial.print("LB:");
  Serial.print(data_in[L_click]);
  Serial.print(" ");
  Serial.print("RX:");
  Serial.print(data_in[R_xpos]);
  Serial.print(" ");
  Serial.print("RY:");
  Serial.print(data_in[R_ypos]);
  Serial.print(" ");
  Serial.print("RB:");
  Serial.print(data_in[R_click]);
  Serial.print(" ");
  Serial.print("P:");
  Serial.print(data_in[P_pos]);
  Serial.print(" ");
  Serial.print("S:");
  Serial.print(data_in[S_click]);
  Serial.print(" ");
  Serial.print("B:");
  Serial.print(data_in[B_click]);
  Serial.print(" ");
  Serial.print("U:");
  Serial.print(data_in[U_click]);
  Serial.print(" ");
  Serial.print("D:");
  Serial.println(data_in[D_click]);
}


#endif
