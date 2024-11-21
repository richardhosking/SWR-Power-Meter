/*
Power SWR Meter calculation routines and variables

Richard Hosking VK8RH Sept 2021

*/
#include "Arduino.h"
// Custom Library to drive ADS1015 ADC
#include "ADS1X15.h"

//ADS1115 ADC object with I2C address 0x48
;

class PowerSWRMeter{
    public:
    PowerSWRMeter();
    // Read the forward power from Directional Coupler - return power in dBm
    float getForward();
    // Read reverse power 
    float getReverse();
    // Calculate power in Watts or mW, depending on level 
    float calculatePower();
    // Calculate SWR
    float calculateSWR();
    
    // Class variables 
    double averagePower = 0.0, forwardPowerdBm = 0.0, reversePowerdBm = 0.0, averagePowerdBm = 0.0, SWR = 5.00;
    
    // Flag to indicate which power unit to display
    int point = 2;
    // number of repetitions to get peak power over
    // Use average as a noise reduction technique
    int instReps = 5;
    int forwardReading = 0;
    int reverseReading = 0;
    ADS1115 adc;    
    private:
    // Offset for noise floor in volts found experimentally
    float ForwardNoiseFloorVolts = 0.288;
    float ReverseNoiseFloorVolts = 0.333;
    // ADC input values 
    int16_t val_0;  
    int16_t val_1;
    // scale ADC input values to volts 
    double adcMultiplier = 0.0001875;
    float voltsTodBm = 0.025;
    float dBmOffset = 30.0;
    
};