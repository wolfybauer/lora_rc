// BSFrance LoRa32u4 v1.1 / Adafruit feather 32u4
#define SCK     15   // GPIO5  -- SX1278's SCK
#define MISO    14   // GPIO19 -- SX1278's MISO
#define MOSI    16   // GPIO27 -- SX1278's MOSI
#define SS      8    // GPIO18 -- SX1278's CS
#define RST     4    // GPIO14 -- SX1278's RESET
#define DI0     7    // GPIO26 -- SX1278's IRQ(Interrupt Request)

// MISC defines
#define BAND      915E6     // radio frequency band USA= 915E6
#define BAUD_RATE 9600      // Serial connection baud rate, for debugging etc

// SCREEN STUFF
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// joysticks
#define L_X_PIN A3 // x
#define L_Y_PIN A2 // y
#define L_B_PIN 5  // button

#define R_X_PIN A1 // x
#define R_Y_PIN A0 // y
#define R_B_PIN 6  // button

// slider + menu buttons
#define POT_PIN  A4
#define SEL_PIN  11
#define BACK_PIN 9
#define UP_PIN   12
#define DOWN_PIN 10


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
byte data_out[PACKET_SIZE];


// Timer stuff
#define DATA_CYCLE_TIME 60000 // in micros
#define DRAW_CYCLE_TIME 100000 // in micros
unsigned long prev_data_time = 0;
unsigned long prev_draw_time = 0;
unsigned long curr_data_time;
unsigned long curr_draw_time;

static const unsigned char PROGMEM WOLF_BMP[] =
{ B00110000, B00000000, B00000000, B01100000,
  B00101100, B00000000, B00000001, B10100000,
  B00100011, B00000000, B00000110, B00100000,
  B00100000, B11000000, B00001000, B00100000,
  B00100000, B00101111, B11101000, B00100000,
  B00100000, B00010000, B00010000, B00100000,
  B00010000, B00000000, B00000000, B00111000,
  B00011000, B00000000, B00000000, B00000100,
  B00001000, B00100010, B00000000, B00000010,
  B00001000, B00010100, B00010001, B00111111,
  B00010000, B00001000, B00001010, B00010000,
  B00100000, B00010100, B00000100, B00001000,
  B01100000, B00100010, B00001010, B00000100,
  B00011000, B00000000, B00010001, B00111110,
  B00000100, B00000000, B00000000, B00100000,
  B00001000, B00000000, B00000000, B00100000,
  B00010000, B00000000, B00000000, B00100000,
  B00100000, B00000000, B00000000, B00100000,
  B01111100, B00000000, B00000000, B00010000,
  B00000011, B10000000, B00000000, B00010000,
  B00000100, B01100000, B00000000, B00010000,
  B00000100, B00010000, B00000000, B00001000,
  B00001000, B00101000, B00000000, B00001000,
  B00001000, B01000110, B00000000, B00001100,
  B00001000, B01000001, B00000000, B00000100,
  B00001000, B01000000, B10000000, B00000010,
  B00001000, B01000000, B01100000, B00000111,
  B00000100, B00100000, B00010000, B00001111,
  B00000100, B00100000, B00001100, B00011111,
  B00000010, B00100000, B00000011, B10111110,
  B00000001, B11000000, B00000000, B01111100,
  B00000000, B00000000, B00000000, B00011000 };
