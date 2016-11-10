#ifndef ELECTRONICCOMPONENTDETECTOR_h
#define ELECTRONICCOMPONENTDETECTOR_h


#include "Arduino.h"

class ElectronicComponentDetector {
public:
    ElectronicComponentDetector();
    
    void init();
    
    void disableSwitches();
    void move(char dir);
    void decode(char pad, char* code, char debug);
    
private:
    //Globals
    float Calibration_Voltage;    //Calibration voltage in mV
    float Maximum_Voltage;        //Max/open circuit voltage in mV
    float Current_Source;         //Current Source measured current in uA
    char Code[5];
    //End Globals
    
    
    //Pin Definitions
    const char ADC_IN = A3;
    const char PEAK_ADC = A2;
    
    const char IND_DETECTED = A1;
    const char CAP_DETECTED = A0;

    const char MUX_CONTROL4 = 2;  //C
    const char MUX_CONTROL3 = 3;  //B
    const char MUX_CONTROL2 = 4;  //A
    //MUX_CONTROL1 is tied to ground as it's the enable pin, IGNORE

    //***WARNING*** SW_CONTROL_B (DG411 Chip) HAS ALL ITS INPUTS INVERTED (EX: LOGIC HIGH OPEN THE SWITCHES, LOGIC LOW CLOSES THE SWITCHES)
    const char SW_CONTROL_B_4 = 6; //Sensor_Tap to Ref_Ind, Connects the ref Inductor to the sensor tap
    const char SW_CONTROL_B_3 = 7; //Sensor_Tap to Ref_Cap, Connects the ref Cap to the sensor tap
    const char SW_CONTROL_B_2 = 8; //Sensor_Tap to Pre_Tone, Connects the sensor tap to the Tone Detector Op Amp
    const char SW_CONTROL_B_1 = 9; //Sensor_Tap to 1K Resistor Load, Calibration load

    const char SW_CONTROL_A_4 = 10; //Peak Cap Discharge, Discharges the peak detector capacitor
    const char SW_CONTROL_A_3 = 11; //Sensor_Tap to Pre_Peak, Connects the sensor tap to the Peak Detector Op Amp
    const char SW_CONTROL_A_2 = 12; //Sensor_Tap to Pre_ADC, Connects the sensor tap to the ADC Op Amp
    const char SW_CONTROL_A_1 = 13; //VSource to Sensor_Tap, Controls The Current Source
    //End Pin Definitions

};
#endif
