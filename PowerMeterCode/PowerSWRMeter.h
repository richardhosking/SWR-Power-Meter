/*
Power SWR Meter calculation routines and variables

Richard Hosking VK8RH Sept 2021

*/
#include "Arduino.h"


class PowerSWRMeter{
    public:
    // Constructor/Destructor are implicit 

    // Read the forward power from Directional Coupler - return power in dBm
    float getForward();
    
    // Read reverse power 
    float getReverse();
    
    // Calculate power in Watts or mW, depending on level 
    float calculatePower();
    
    // Calculate SWR
    float calculateSWR();
    
    // Class variables 
    double indicatedPower = 0.0, peakPower = 0.0, powerdBm = 0.0, reversePowerdBm = 0.0, SWR = 1.00;
    // Flag to indicate which power unit to display
    int point = 2;
    // number of repetitions to get peak power over
    int instReps = 5, averageReps = 4;
    int forwardReading = 0;
    int reverseReading = 0;
        
    private:
    // Analogue inputs
    int forwardSensor = 15;
    int reverseSensor  = 14;
    
    // Noise floor threshold (approx -dBm)
    int threshold = 40;
    
    // Zero offset forward and reverse
    int forwardZeroOffset = -20;
    int reverseZeroOffset = -20;
    
    // approx 20mV/dB output from AD8307
    // Adjust multiplier depending on analogue input of processor
    // Analog input has about 10 bits resolution
    
    float forwardMultiplier = 7.8;
    float reverseMultiplier = 7.8;
 
};
