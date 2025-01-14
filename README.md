# SWR-Power-Meter
High Performance HF Power meter using Arduino and a Directional Coupler
This device can measure power over a wide dynamic range from 10uW to 1 KW and will derive SWR for a 50 Ohm load 
The front end uses broadband Ferrite transformers in a Directional Coupler configuration 
AD8307 Logarithmic amplifiers derive power in a forward and reverse direction 
These drive an ADS1115 ADC for better resolution than the Arduino ADC can provide 
An Arduino Adafruit Trinket Pro 3V board performs calculations and drives a display
The display is an OLED - widely available but I2C is poorly docmented - see seprate README for details 
The KICAD PCB files are at https://github.com/richardhosking/PowerMeterKICAD
