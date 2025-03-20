#include <PicoGamepad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmap2.h"
#include "cheeksmap.h"  // Include the bitmap array

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1  // Reset pin (not used for I2C)
#define SCREEN_ADDRESS 0x3C  // Change to 0x3D if needed

PicoGamepad gamepad;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 16 bit integer for holding input values
int val;
int tit;
int cheeks;

void setup() {  
  //Serial.begin(115200);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();


  pinMode(LED_BUILTIN, OUTPUT);
  // X Potentiometer on pin 26
  pinMode(26, INPUT);
  // Y Potentiometer on pin 27
  //pinMode(27, INPUT);
  // Button on pin 
  //pinMode(28, INPUT_PULLUP);
}

void loop() {
  display.clearDisplay();
  // Get input value from Pico analog pin
  val = analogRead(26);
  // if(val >= 50) {
  //   digitalWrite(LED_BUILTIN, LOW);
  // } else {
  //   digitalWrite(LED_BUILTIN, HIGH);
  // }

  tit = map(val, 0, 1030, 0, 95);
  display.drawBitmap((SCREEN_WIDTH - 111) / 2, 0, epd_bitmap_allArray[tit], 128, 32, WHITE);
  //cheeks = map(val, 0, 1030, 0, 224);
  //display.drawBitmap((SCREEN_WIDTH - 111) / 2, 0, cheeksmapallArray[cheeks], 128, 32, WHITE);
  display.display();
  // Map analog 0-1023 value from pin to max HID range -32767 - 32767
  val = map(val, 0, 1023, -32767, 32767);




  // Send value to HID object
  gamepad.SetX(val);

  // Repeat with Y pin
  //val = analogRead(27);
  //val = map(val, 0, 1023, -32767, 32767);
  //gamepad.SetY(val);
  
//  gamepad.SetZ(val);
//  gamepad.SetRx(val);
//  gamepad.SetRy(val);
//  gamepad.SetRz(val);
//  gamepad.SetS0(val);
//  gamepad.SetS1(val);

  // Set button 0 of 128 by reading button on digital pin 28
  //gamepad.SetButton(0, !digitalRead(28));
  // Send all inputs via HID 
  // Nothing is send to your computer until this is called.
  gamepad.send_update();

  // Flash the LED just for fun
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  delay(20);
}

