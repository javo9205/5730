#include <Wire.h> 
#include <Adafruit_ADS1X15.h> 
Adafruit_ADS1115 ads; /* Use this for the 16-bit version */ 
int iTime_ave_msec = 100;  //averaging time per point 
long iTime_stop_msec; 
int iCounter1 = 0;  //used in counting number of points 
float V_diff_mV;    
//used for diff voltage 
float V_SE_mV;      
void setup(void) { 
// used for SE measurement 
Serial.begin(2000000); 
//    ADS1015  ADS1115 
//    -------  ------- 
 
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default) 
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV 
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV 
  ads.setGain(GAIN_FOUR);  // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV 
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV 
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV 
  ads.begin();  //with the ADR pin set to gnd. 
 
  ads.setDataRate(RATE_ADS1115_860SPS); 
 
} 
 
void loop(void) { 
 
  V_diff_mV = 0.0; 
  V_SE_mV = 0.0; 
  iCounter1 = 0; 
 
  iTime_stop_msec = micros() / 1000 + iTime_ave_msec; 
  while (micros() / 1000 <= iTime_stop_msec) { 
    V_diff_mV = V_diff_mV + ads.readADC_Differential_0_1() * 0.0312; 
    V_SE_mV = V_SE_mV + ads.readADC_SingleEnded(0) * 0.0312; 
    iCounter1++; 
  } 
  V_diff_mV = V_diff_mV / iCounter1; 
  V_SE_mV = V_SE_mV / iCounter1; 
 
  Serial.print(720); 
  Serial.print(", "); 
  Serial.print(760); 
  Serial.print(", "); 
  Serial.print(V_diff_mV); 
  Serial.print(", "); 
  Serial.println(V_SE_mV); 
} 