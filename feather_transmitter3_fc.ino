//#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce2.h>

#include "util.h"

// button logic bools
bool   L_tog = false; // left stick button
bool   R_tog = false; // right stick button
bool   S_tog = false; // start button
bool   B_tog = false; // back button
bool   U_tog = false; // up button
bool   D_tog = false; // down button

Bounce L_button;
Bounce R_button;
Bounce S_button;
Bounce B_button;
Bounce U_button;
Bounce D_button;

// build screen instance, default: "display"
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // Serial connection init
  Serial.begin(BAUD_RATE);
  Serial.println();
  Serial.println("Serial connection established...");
  
  // LoRa init
  Serial.println("Attempting to start LoRa...");
  LoRa.setPins(SS,RST,DI0); // set correct pins for logic level converters etc
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);              // loop forever if LoRa init fails
  }
  Serial.println("LoRa started successfully!");

  // OLED init
  Serial.println("Attempting to start OLED...");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay(); // clear out adafruit splash

  // wolf logo splash screen
  display.drawBitmap(47, 15, WOLF_BMP, 32, 32, 1);
  display.display();
  delay(2500);
  display.clearDisplay();

  // screen text stuff
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setTextWrap(false);

  // initialize button pins
  L_button.attach(L_B_PIN, INPUT_PULLUP);
  R_button.attach(R_B_PIN, INPUT_PULLUP);
  S_button.attach(SEL_PIN, INPUT_PULLUP);
  B_button.attach(BACK_PIN, INPUT_PULLUP);
  U_button.attach(UP_PIN, INPUT_PULLUP);
  D_button.attach(DOWN_PIN, INPUT_PULLUP);

  L_button.interval(1);
  R_button.interval(1);
  S_button.interval(1);
  B_button.interval(1);
  U_button.interval(1);
  D_button.interval(1);

  // set all data to initial defaults
  data_out[L_xpos] = 127;
  data_out[L_ypos] = 127;
  data_out[L_click] = 0;
  data_out[R_xpos] = 127;
  data_out[R_ypos] = 127;
  data_out[R_click] = 0;
  data_out[P_pos] = 127;
  data_out[S_click] = 0;
  data_out[B_click] = 0;
  data_out[U_click] = 0;
  data_out[D_click] = 0;
}

void loop() {

  
  
  // update the timers
  curr_data_time = micros();
  curr_draw_time = micros();

  //getPotData();
  //getButtonData();
  sendData(data_out);
  
  // data loop, set by DATA_CYCLE_TIME
  if(curr_data_time - prev_data_time >= DATA_CYCLE_TIME) {
    getPotData();
    getButtonData();
    //sendData(data_out);
    printSerialData();
    prev_data_time = curr_data_time;
  }

  // draw loop, set by DRAW_CYCLE_TIME
  if(curr_draw_time - prev_draw_time >= DRAW_CYCLE_TIME) {
    display.clearDisplay();
    screenStuff();
    display.display();
    prev_draw_time = curr_draw_time;
  }
}

void getPotData() {
  
  // get, map, update all potentiometer data
  // (subtract from 255 to reverse direction)
  data_out[L_xpos] = 255 - map(analogRead(L_X_PIN), 0, 1023, 0, 255);
  data_out[L_ypos] = map(analogRead(L_Y_PIN), 0, 1023, 0, 255);
  data_out[R_xpos] = map(analogRead(R_X_PIN), 0, 1023, 0, 255);
  data_out[R_ypos] = 255 - map(analogRead(R_Y_PIN), 0, 1023, 0, 255);
  data_out[P_pos]  = 255 - map(analogRead(POT_PIN), 0, 1023, 0, 255);

  
}

void sendData(byte pk[]) {
  
  LoRa.beginPacket();
  LoRa.write(pk, PACKET_SIZE);
  LoRa.endPacket();
}

          

void screenStuff() {

  // ALL TEXT STUFF
  
  display.setTextSize(1);             
  display.setTextColor(WHITE);
    
  display.setCursor(20, 0);             
  display.print("LX:");
  display.print(data_out[L_xpos]);
  display.setCursor(20, 16);             
  display.print("LY:");
  display.print(data_out[L_ypos]);

  display.setCursor(61, 0);             
  display.print("RX:");
  display.print(data_out[R_xpos]);
  display.setCursor(61, 16);             
  display.print("RY:");
  display.print(data_out[R_ypos]);

  /*display.setCursor(20, 32);
  display.print("LB:");
  display.print(data_out[L_click]);
  display.setCursor(61, 32);
  display.print("RB:");
  display.print(data_out[R_click]);*/

  // SLIDER + BUTTONS GRAPHICS

  if(!L_tog) display.drawCircle(38, 45, 10, WHITE);
  else display.fillCircle(38, 45, 10, WHITE);

  if(!R_tog) display.drawCircle(79, 45,  10, WHITE);
  else display.fillCircle(79, 45, 10, WHITE);

  int slider_gfx_ypos = map(data_out[P_pos], 0, 255, 60, 0);

  display.drawLine(5, 0, 5, 63, WHITE);
  display.fillRect(0, slider_gfx_ypos, 10, 4, WHITE);

  if(S_tog) display.fillRect(104, 40, 11, 11, WHITE);
  else display.drawRect(104, 40, 11, 11, WHITE);

  if(B_tog) display.fillRect(104, 52, 11, 11, WHITE);
  else display.drawRect(104, 52, 11, 11, WHITE);

  if(U_tog) display.fillRect(116, 40, 11, 11, WHITE);
  else display.drawRect(116, 40, 11, 11, WHITE);

  if(D_tog) display.fillRect(116, 52, 11, 11, WHITE);
  else display.drawRect(116, 52, 11, 11, WHITE);
}

void printSerialData() {
  Serial.print("LX:");
  Serial.print(data_out[L_xpos]);
  Serial.print(" ");
  Serial.print("LY:");
  Serial.print(data_out[L_ypos]);
  Serial.print(" ");
  Serial.print("LB:");
  Serial.print(data_out[L_click]);
  Serial.print(" ");
  Serial.print("RX:");
  Serial.print(data_out[R_xpos]);
  Serial.print(" ");
  Serial.print("RY:");
  Serial.print(data_out[R_ypos]);
  Serial.print(" ");
  Serial.print("RB:");
  Serial.print(data_out[R_click]);
  Serial.print(" ");
  Serial.print("P:");
  Serial.print(data_out[P_pos]);
  Serial.print(" ");
  Serial.print("S:");
  Serial.print(data_out[S_click]);
  Serial.print(" ");
  Serial.print("B:");
  Serial.print(data_out[B_click]);
  Serial.print(" ");
  Serial.print("U:");
  Serial.print(data_out[U_click]);
  Serial.print(" ");
  Serial.print("D:");
  Serial.println(data_out[D_click]);
}

void getButtonData() {
  // get all button data, update bools
  L_button.update();
  R_button.update();
  S_button.update();
  B_button.update();
  U_button.update();
  D_button.update();

  if(L_button.fell()) L_tog = !L_tog;
  if(R_button.fell()) R_tog = !R_tog;
  if(S_button.fell()) S_tog = !S_tog;
  if(B_button.fell()) B_tog = !B_tog;
  if(U_button.fell()) U_tog = !U_tog;
  if(D_button.fell()) D_tog = !D_tog;

  // update packet data from bools
  data_out[L_click] = L_tog;
  data_out[R_click] = R_tog;
  data_out[S_click] = S_tog;
  data_out[B_click] = B_tog;
  data_out[U_click] = U_tog;
  data_out[D_click] = D_tog;
}
