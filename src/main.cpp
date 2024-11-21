/**************************************************
 * Power Meter Code Oct 2024
 * Richard Hosking VK8RH Nov 2022
 * 
 * Using Adafruit Pro Trinket 3.3V 
 * 
 * Custom Directional coupler/Log amplifier/SWR detector board
 *   
 * OLED Display MCOB128064JX-YM 
 * This uses an SSD1309 driver
 * but appears to work with the SSD1305 Adafruit Library
 *   
 *************************************************/

#include <Wire.h>
#include <SPI.h>

// Display 
#include "display.h"

// Custom Library to drive Diectional Coupler Board
#include "powerMeter.h"

// Custom Library to drive ADS1015 ADC
//#include "ADS1X15.h"

// And setup display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     9 // Reset pin # (or -1 if sharing Arduino reset pin)
#define DISPLAY_ADDRESS 0x3C // Set by grounding Pin 16 on display SA0 LOW
#define SPEED_BEFORE     100000 // I2C setup speed 100KHz is a safe option
#define SPEED_AFTER      100000 // I2C data speed - safe option 
// Display object
Display display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, SPEED_BEFORE, SPEED_AFTER);

// Declare power meter object
PowerSWRMeter meter;

void setup() {
  
  // If we can get the display to work can use it for debugging
  // (No FTDI/serial to USB interface on Pro Trinket)
  // Clear the buffer
  display.begin(DISPLAY_ADDRESS, true);
  display.clearDisplay();
  display.display();
  
// Set up display  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Power Meter VK3BFX");
  display.display();
  delay(1000);
  if(!meter.adc.begin()) {
    display.println(F("adc setup failed - check connections"));
    for(;;); // Don't proceed, loop forever
  }     
  delay(1000);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,10);
  display.print("Power: ");
  display.print(meter.calculatePower());
  // display Power unit
  if (meter.point==0){
    display.println(" uW ");
    }
  else if(meter.point==1){
    display.println(" mW ");
    }
  else{
    display.println(" W ");
    }
  // dBm
  display.print("       ");
  display.print(meter.getForward());
  display.println(" dBm");
  display.println("  ");

  // and SWR
  display.setTextSize(2);
  display.print("SWR: ");
  display.println(meter.calculateSWR());
  display.display();
  // Repeat every half second or so 
  delay(500);  
}

// End of code
                        
