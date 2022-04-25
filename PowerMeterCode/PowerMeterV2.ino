/*!
 Power SWR Meter 
 Directional coupler using coax transformers 
 1.8 to 54 MHz
 Power rating up to 2KW 
 measurement range approx -30dBm to +63dBm
 Using AD8307 log amplifier which generates a voltage 
 proportional to log(power) approx 20mV/dB
 SWR measurement comparing forward and reverse power
 
 Display Adafruit 0.96" Stemma QT OLED Monochrome display
 * (Until I get a bigger one!)
 
 Author Richard Hosking VK8RH 
 adapted from Adafruit Libraries
 Sept 2021
*/

#include <Wire.h>
#include "Display.h"
#include "PowerSWRMeter.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
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
  
// Constructor for power meter object
PowerSWRMeter meter;

void setup() {
  // No Serial port available with Pro Trinket 
  //Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.display();
  
// Set up display  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Power/SWR Meter VK8RH");
  //display.println("");  
  display.setTextSize(2);  

  display.display();
 
}

void loop() {
    
    meter.calculatePower();
    meter.calculateSWR();
    writeDisplay();
   
}
// Functions 
void writeDisplay(){
        // Print the current peak power level and SWR
        // Have to blank the old figure before rewriting - overwrite with spaces
        // Hack - invert twice - just overwriting with blanks doesnt work
        display.setCursor(0,12);
        display.setTextColor(BLACK, WHITE); // 'inverted' text
        display.print("                   ");
        display.setTextColor(WHITE,BLACK); // 'inverted' text
        display.setCursor(0,12);
        display.print("                   ");
        display.setCursor(0,12);
        display.print(meter.indicatedPower);
        // display Power unit
        if (meter.point==0){
            display.println("uW ");
            }
         
        else if(meter.point==1){
            display.println("mW ");
        }
        else{
            display.println(" W ");
        }
        display.setCursor(0,30);
        display.setTextColor(BLACK, WHITE); // 'inverted' text
        display.print("                   ");
        display.setTextColor(WHITE,BLACK); // 'inverted' text
        display.setCursor(0,30);
        display.print("                   ");
        display.setCursor(0,30);
        display.print(meter.powerdBm);
        display.println(" dBm");
            

        display.setCursor(0,48);
        display.setTextColor(BLACK, WHITE); // 'inverted' text
        display.print("      ");
        display.setTextColor(WHITE,BLACK); // 'inverted' text
        display.setCursor(0,48);
        display.print("      ");
        display.setCursor(0,48);
        display.print("SWR ");        
        if (meter.SWR>5.0){
            display.print("High");
        }
        else if (meter.SWR<1.0){
            display.print(" NA ");
        }
        else {
            display.print(meter.SWR);
        }
        display.display();
        
     }                                    
