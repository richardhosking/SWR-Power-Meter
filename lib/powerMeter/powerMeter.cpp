/*
Power SWR Meter calculation routines and variables

Richard Hosking VK8RH Sept 2021

*/
#include "powerMeter.h" 
#include <math.h>

   PowerSWRMeter::PowerSWRMeter(){
        // Constructor
        // Set up ADC
               
    }
   // Routine gets reading and calculates power in watts and dBm
    float PowerSWRMeter::getForward(){
        // get forward power reading integer
        forwardReading = adc.readADC(0);
        // Multiply to get volts 
        float fr;
        fr = float(forwardReading) * adcMultiplier;
        // subtract for zero offset and noise floor
        fr  = fr - ForwardNoiseFloorVolts;
        // Convert to dBm 20mV/dB
        forwardPowerdBm = fr/voltsTodBm - dBmOffset;
        return forwardPowerdBm;        
        
    }
    float PowerSWRMeter::getReverse(){
         
        reverseReading = adc.readADC(1);
        float rr;
        rr = float(reverseReading)  * adcMultiplier;
        rr = rr - ReverseNoiseFloorVolts;
        reversePowerdBm = rr/voltsTodBm - dBmOffset;
        return reversePowerdBm;        
    }
    float PowerSWRMeter::calculatePower(){
        // Average out value over a number of measurements as noise reduction 
        int i = 0;
        float total = 0.0;
        float instPower = 0.0;
            
        for (i=0; i<instReps; i++){
            instPower = getForward();
            total = total + instPower;
            }
        averagePowerdBm = (total/instReps);
        // Convert to Watts       
        averagePower = pow(10, averagePowerdBm/10);
        // Set units for display
        if(averagePower < 1) {
            // Point - Flag to indicate power units
            // set power unit to uW
            averagePower = averagePower *1000;
            point = 0; 
        }
        else if(averagePower >= 1 && averagePower < 1000.0) {
            // Set power unit to mW
            point = 1;
        }
        else if (averagePower > 1000.0) {
            // Set power unit to W
            averagePower = averagePower/1000;
            point = 2;
        }
       
        return averagePower;
    }
    
    // This routine calculates SWR from the formula 
    // SWR = (1+(Pr/Pf)^1/2)/(1-(Pr/Pf)^1/2))
        
    float PowerSWRMeter::calculateSWR(){
        //Get forward and reverse power
        double reversePower, forwardPower; 
        int i = 0;
        float total = 0.0;
        float instPower = 0.0;
         
        for (i=0; i<instReps; i++){
            instPower = getForward();
            total = total + instPower;
            }
            // Average out to reduce noise
        forwardPowerdBm = (total/instReps);
        
        i = 0;
        total = 0.0;
        instPower = 0.0;
        
        for (i=0; i<instReps; i++){
            instPower = getReverse();
            total = total + instPower;
            }
            // Average out to reduce noise
        reversePowerdBm = (total/instReps);             
 
        forwardPower = pow(10, forwardPowerdBm/10);
        reversePower = pow(10, reversePowerdBm/10);
        
        SWR = (1+sqrt(reversePower/forwardPower))/(1-sqrt(reversePower/forwardPower));
        
        return SWR;
    }
   
