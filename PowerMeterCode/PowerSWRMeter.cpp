/*
Power SWR Meter calculation routines and variables

Richard Hosking VK8RH Sept 2021

*/
#include "PowerSWRMeter.h" 
#include <math.h>

   
   // Routine gets reading and calculates power in watts and dBm
    float PowerSWRMeter::getForward(){
        forwardReading = analogRead(forwardSensor);
        float fr;
        fr = float(forwardReading);
        powerdBm = ((fr - forwardZeroOffset)/forwardMultiplier) - threshold;
        return powerdBm;        
        
    }
    float PowerSWRMeter::getReverse(){
        reverseReading = analogRead(reverseSensor);
        float rr;
        rr = float(reverseReading);
        reversePowerdBm = ((rr - reverseZeroOffset)/reverseMultiplier) - threshold;
        return reversePowerdBm;        
    }
    float PowerSWRMeter::calculatePower(){
        // Average out value over a number of measurements as noise reduction 
        int i,j = 0;
        float peak = -40.0;
        float instPower = 0.0;
        float total = 0.0;
        for (i; i<instReps; i++){
            for(j; j<averageReps; j++){
                instPower = getForward();
                total = total + instPower;
            }
            // Capture peak value
            peak = total/averageReps;
            if (peak > powerdBm){
                powerdBm = peak;
            }
        }
        
        peakPower = pow(10, powerdBm/10);
     
        if(peakPower < 1) {
 
            // Point - Flag to indicate power units
            // set power unit to uW
            peakPower = peakPower *1000;
            point = 0; 
        }
        else if(peakPower >= 1 && peakPower < 1000.0) {
            // Set power unit to mW
            point = 1;
        }
        else if (peakPower > 1000.0) {
            // Set power unit to W
            peakPower = peakPower/1000;
            point = 2;
        }
        indicatedPower = peakPower;

        return peakPower;
    }
    
    // This routine calculates SWR from the formula 
    // SWR = (1+(Pr/Pf)^1/2)/(1-(Pr/Pf)^1/2))
        
    float PowerSWRMeter::calculateSWR(){
        //Get forward and reverse power
        double reversePower, forwardPower;      
        powerdBm = getForward();
        reversePowerdBm = getReverse();
        forwardPower = pow(10, powerdBm/10);
        reversePower = pow(10, reversePowerdBm/10);
        
        SWR = (1+sqrt(reversePower/forwardPower))/(1-sqrt(reversePower/forwardPower));
        
        return SWR;
    }
   
