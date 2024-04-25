#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] = { 0b00000000, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000011, 0b11100000,
                                                  0b11110011, 0b11100000,
                                                  0b11111110, 0b11111000,
                                                  0b01111110, 0b11111111,
                                                  0b00110011, 0b10011111,
                                                  0b00011111, 0b11111100,
                                                  0b00001101, 0b01110000,
                                                  0b00011011, 0b10100000,
                                                  0b00111111, 0b11100000,
                                                  0b00111111, 0b11110000,
                                                  0b01111100, 0b11110000,
                                                  0b01110000, 0b01110000,
                                                  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}
int x = 0;
int y = 0;
bool x_bool = false;
bool y_bool = false;
bool _x_bool = false;
bool _y_bool = false;
bool ecke = false;

int reset = 0;

void loop() {
  display.drawPixel(y, x, SSD1306_WHITE);
  handel_X(0, 31);
  handel_Y(0, 127);
  display.display();
  Serial.println(y);
  Serial.println(x);
  if (x == 31 && y == 127) {
    ecke = true;
  } else {
    ecke = false;
  }
  if (ecke) {
    x = 0;
    y = 0;
    display.clearDisplay();
  }
}

void handel_X(int min_x, int max_x) {
  if (x == max_x) {
    x_bool = true;
    _x_bool = false;
  }
  if (x == min_x) {
    x_bool = false;
    _x_bool = true;
  }
  if (x_bool) {
    x -= 1;
  }
  if (_x_bool) {
    x += 1;
  }
}
void handel_Y(int min_y, int max_y) {
  if (y == max_y) {
    y_bool = true;
    _y_bool = false;
  }
  if (y == min_y) {
    y_bool = false;
    _y_bool = true;
  }
  if (y_bool) {
    y -= 1;
  }
  if (_y_bool) {
    y += 1;
  }
}
