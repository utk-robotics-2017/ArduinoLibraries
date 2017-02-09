

//WIP
#include "ElectronicComponentDetector.h"


ElectronicComponentDetector::ElectronicComponentDetector() {
    //Constructor code here
    Calibration_Voltage = 0.0;    //Calibration voltage in mV
    Maximum_Voltage = 0.0;        //Max/open circuit voltage in mV
    Current_Source = 0.0;
}


void ElectronicComponentDetector::init() {
    //setup from the prototype ino code
    //Setup pin direction
    pinMode(SW_CONTROL_A_4,OUTPUT);pinMode(SW_CONTROL_A_3,OUTPUT);pinMode(SW_CONTROL_A_2,OUTPUT);pinMode(SW_CONTROL_A_1,OUTPUT);

    pinMode(SW_CONTROL_B_4,OUTPUT);pinMode(SW_CONTROL_B_3,OUTPUT);pinMode(SW_CONTROL_B_2,OUTPUT);pinMode(SW_CONTROL_B_1,OUTPUT);

    pinMode(MUX_CONTROL4,OUTPUT);pinMode(MUX_CONTROL3,OUTPUT);pinMode(MUX_CONTROL2,OUTPUT);

    pinMode(IND_DETECTED,INPUT);pinMode(CAP_DETECTED,INPUT);
    pinMode(ADC_IN,INPUT);pinMode(PEAK_ADC,INPUT);

    disableSwitches();

    //ADC Setup
    analogReference(DEFAULT); //Normal 5V Reference

    //Run calibration voltage for 1k resistor
    digitalWrite(MUX_CONTROL2,HIGH);
    digitalWrite(MUX_CONTROL3,HIGH);
    digitalWrite(MUX_CONTROL4,HIGH);
    digitalWrite(SW_CONTROL_B_1,LOW);
    digitalWrite(SW_CONTROL_A_1,HIGH);
    digitalWrite(SW_CONTROL_A_2,HIGH);
    Calibration_Voltage = analogRead(ADC_IN) * 4.88; //Calibration Voltage in mV
    Current_Source = Calibration_Voltage * (1000.0 / 1025.0); //Calculate the current in uA (Lower value of the divider is the calibration resistor)

    //Find max/open circuit voltage
    digitalWrite(SW_CONTROL_B_1,HIGH);
    Maximum_Voltage = analogRead(ADC_IN) * 4.88; //Max Voltage in mV
}

void ElectronicComponentDetector::disableSwitches() {
    digitalWrite(SW_CONTROL_A_1,LOW);digitalWrite(SW_CONTROL_A_2,LOW);digitalWrite(SW_CONTROL_A_3,LOW);digitalWrite(SW_CONTROL_A_4,LOW);
    digitalWrite(SW_CONTROL_B_1,HIGH);digitalWrite(SW_CONTROL_B_2,HIGH);digitalWrite(SW_CONTROL_B_3,HIGH);digitalWrite(SW_CONTROL_B_4,HIGH);
    digitalWrite(MUX_CONTROL2,HIGH);digitalWrite(MUX_CONTROL3,HIGH);digitalWrite(MUX_CONTROL4,HIGH);
}

void ElectronicComponentDetector::decode(char pad, char* code, char debug) {
    char all_pads = 0;
    float temp_dc_read;
    float temp_transient_read[5];
    unsigned long temp_transient_read_timepoints[5];
    unsigned long start_timepoint;
    float dvdt;

    disableSwitches();

    switch(pad) {
        case 9: //If all pads are selected, set the all pads flag
            all_pads = 1;

        case 0:
            pad = 0; //Set the current pad number & change the mux to connect to the current pad
            digitalWrite(MUX_CONTROL2,LOW);digitalWrite(MUX_CONTROL3,LOW);digitalWrite(MUX_CONTROL4,LOW);

            //Discharge (If the mystery component is precharged)
            digitalWrite(SW_CONTROL_B_1,LOW);

            delay(5);

            //Disconnect the discharge resistor
            digitalWrite(SW_CONTROL_B_1,HIGH);

            //Connect the ADC & the current source
            digitalWrite(SW_CONTROL_A_1,HIGH);digitalWrite(SW_CONTROL_A_2,HIGH);

            //Set the start time for transient analysis
            start_timepoint = micros();

            //Do transient analysis first:
            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read_timepoints[x] = micros();
                temp_transient_read[x] = analogRead(ADC_IN);
                delayMicroseconds(10);
            }

            //Disconnect the current source
            digitalWrite(SW_CONTROL_A_1,LOW);

            //Do some integer/float math to convert the datapoints into mV
            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read[x] *= 4.88;
                temp_transient_read_timepoints[x] -= start_timepoint;
            }

            //Calculate dV/dt for debug & decoding
            dvdt = (temp_transient_read[4] - temp_transient_read[0]) / (temp_transient_read_timepoints[4] - temp_transient_read_timepoints[0]);

            //Display debug data
            if(debug) {
                Serial.print("Pad: "); Serial.print((int)pad); Serial.println(" Transient Analysis:");
                for(char x = 0 ; x < 5 ; x++) {
                    Serial.print("Voltage Datapoint "); Serial.print((int)x); Serial.print(": "); Serial.print(temp_transient_read[x]); Serial.print(" mV @ time: ");
                    Serial.print(temp_transient_read_timepoints[x]); Serial.println(" uS");
                }
                Serial.print("dV/dt: "); Serial.print(dvdt); Serial.println(" mV/uS");
                Serial.println("");
            }

            if(dvdt > 0.2) {
                code[pad] = 3;
            } else if(dvdt < -0.2) {
                code[pad] = 4;
            } else {
                digitalWrite(SW_CONTROL_A_1,HIGH);

                temp_dc_read = analogRead(ADC_IN) * 4.88;

                if(temp_dc_read <= 5.0) {
                    code[pad] = 1;
                } else if((temp_dc_read <= 1100.0) && (temp_dc_read >= 950.0)) {
                    code[pad] = 2;
                } else if((((temp_dc_read <= 600.0) && (temp_dc_read >= 400.0))) || ((temp_dc_read >= (Maximum_Voltage - 300.0)) && (temp_dc_read <= (Maximum_Voltage + 300.0)))) {
                    code[pad] = 5;
                } else {
                    code[pad] = 0;
                }

                if(debug) {
                    Serial.print("Pad: "); Serial.print((int)pad); Serial.print(" Voltage: "); Serial.print(temp_dc_read); Serial.println(" mV");
                    Serial.println("");
                }

            }

            if(!all_pads) {
                break;
            }

        case 1:
            pad = 1;
            digitalWrite(MUX_CONTROL2,HIGH);digitalWrite(MUX_CONTROL3,LOW);digitalWrite(MUX_CONTROL4,LOW);

            //Discharge
            digitalWrite(SW_CONTROL_B_1,LOW);

            delay(5);

            digitalWrite(SW_CONTROL_B_1,HIGH);


            digitalWrite(SW_CONTROL_A_1,HIGH);digitalWrite(SW_CONTROL_A_2,HIGH);

            start_timepoint = micros();

            //Do transient analysis first:
            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read_timepoints[x] = micros();
                temp_transient_read[x] = analogRead(ADC_IN);
                delayMicroseconds(10);
            }

            digitalWrite(SW_CONTROL_A_1,LOW);

            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read[x] *= 4.88;
                temp_transient_read_timepoints[x] -= start_timepoint;
            }

            dvdt = (temp_transient_read[4] - temp_transient_read[0]) / (temp_transient_read_timepoints[4] - temp_transient_read_timepoints[0]);

            if(debug == 1) {
                Serial.print("Pad: "); Serial.print((int)pad); Serial.println(" Transient Analysis:");
                for(char x = 0 ; x < 5 ; x++) {
                    Serial.print("Voltage Datapoint "); Serial.print((int)x); Serial.print(": "); Serial.print(temp_transient_read[x]); Serial.print(" mV @ time: ");
                    Serial.print(temp_transient_read_timepoints[x]); Serial.println(" uS");
                }
                Serial.print("dV/dt: "); Serial.print(dvdt); Serial.println(" mV/uS");
                Serial.println("");
            }

            if(dvdt > 0.2) {
                code[pad] = 3;
            } else if(dvdt < -0.2) {
                code[pad] = 4;
            } else {
                digitalWrite(SW_CONTROL_A_1,HIGH);

                temp_dc_read = analogRead(ADC_IN) * 4.88;

                if(temp_dc_read <= 5.0) {
                    code[pad] = 1;
                } else if((temp_dc_read <= 1100.0) && (temp_dc_read >= 950.0)) {
                    code[pad] = 2;
                } else if((((temp_dc_read <= 600.0) && (temp_dc_read >= 400.0))) || ((temp_dc_read >= (Maximum_Voltage - 300.0)) && (temp_dc_read <= (Maximum_Voltage + 300.0)))) {
                    code[pad] = 5;
                } else {
                    code[pad] = 0;
                }

                if(debug) {
                    Serial.print("Pad: "); Serial.print((int)pad); Serial.print(" Voltage: "); Serial.print(temp_dc_read); Serial.println(" mV");
                    Serial.println("");
                }

            }

            if(!all_pads) {
                break;
            }

        case 2:
            pad = 2;
            digitalWrite(MUX_CONTROL2,LOW);digitalWrite(MUX_CONTROL3,HIGH);digitalWrite(MUX_CONTROL4,LOW);

            //Discharge
            digitalWrite(SW_CONTROL_B_1,LOW);

            delay(5);

            digitalWrite(SW_CONTROL_B_1,HIGH);

            digitalWrite(SW_CONTROL_A_1,HIGH);digitalWrite(SW_CONTROL_A_2,HIGH);

            start_timepoint = micros();

            //Do transient analysis first:
            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read_timepoints[x] = micros();
                temp_transient_read[x] = analogRead(ADC_IN);
                delayMicroseconds(10);
            }

            digitalWrite(SW_CONTROL_A_1,LOW);

            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read[x] *= 4.88;
                temp_transient_read_timepoints[x] -= start_timepoint;
            }

            dvdt = (temp_transient_read[4] - temp_transient_read[0]) / (temp_transient_read_timepoints[4] - temp_transient_read_timepoints[0]);

            if(debug == 1) {
                Serial.print("Pad: "); Serial.print((int)pad); Serial.println(" Transient Analysis:");
                for(char x = 0 ; x < 5 ; x++) {
                    Serial.print("Voltage Datapoint "); Serial.print((int)x); Serial.print(": "); Serial.print(temp_transient_read[x]); Serial.print(" mV @ time: ");
                    Serial.print(temp_transient_read_timepoints[x]); Serial.println(" uS");
                }
                Serial.print("dV/dt: "); Serial.print(dvdt); Serial.println(" mV/uS");
                Serial.println("");
            }

            if(dvdt > 0.2) {
                code[pad] = 3;
            } else if(dvdt < -0.2) {
                code[pad] = 4;
            } else {
                digitalWrite(SW_CONTROL_A_1,HIGH);

                temp_dc_read = analogRead(ADC_IN) * 4.88;

                if(temp_dc_read <= 5.0) {
                    code[pad] = 1;
                } else if((temp_dc_read <= 1100.0) && (temp_dc_read >= 950.0)) {
                    code[pad] = 2;
                } else if((((temp_dc_read <= 600.0) && (temp_dc_read >= 400.0))) || ((temp_dc_read >= (Maximum_Voltage - 300.0)) && (temp_dc_read <= (Maximum_Voltage + 300.0)))) {
                    code[pad] = 5;
                } else {
                    code[pad] = 0;
                }

                if(debug) {
                    Serial.print("Pad: "); Serial.print((int)pad); Serial.print(" Voltage: "); Serial.print(temp_dc_read); Serial.println(" mV");
                    Serial.println("");
                }

            }

            if(!all_pads) {
                break;
            }

        case 3:
            pad = 3;
            digitalWrite(MUX_CONTROL2,HIGH);digitalWrite(MUX_CONTROL3,HIGH);digitalWrite(MUX_CONTROL4,LOW);

            //Discharge
            digitalWrite(SW_CONTROL_B_1,LOW);

            delay(5);

            digitalWrite(SW_CONTROL_B_1,HIGH);

            digitalWrite(SW_CONTROL_A_1,HIGH);digitalWrite(SW_CONTROL_A_2,HIGH);

            start_timepoint = micros();

            //Do transient analysis first:
            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read_timepoints[x] = micros();
                temp_transient_read[x] = analogRead(ADC_IN);
                delayMicroseconds(10);
            }

            digitalWrite(SW_CONTROL_A_1,LOW);

            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read[x] *= 4.88;
                temp_transient_read_timepoints[x] -= start_timepoint;
            }

            dvdt = (temp_transient_read[4] - temp_transient_read[0]) / (temp_transient_read_timepoints[4] - temp_transient_read_timepoints[0]);

            if(debug == 1) {
                Serial.print("Pad: "); Serial.print((int)pad); Serial.println(" Transient Analysis:");
                for(char x = 0 ; x < 5 ; x++) {
                    Serial.print("Voltage Datapoint "); Serial.print((int)x); Serial.print(": "); Serial.print(temp_transient_read[x]); Serial.print(" mV @ time: ");
                    Serial.print(temp_transient_read_timepoints[x]); Serial.println(" uS");
                }
                Serial.print("dV/dt: "); Serial.print(dvdt); Serial.println(" mV/uS");
                Serial.println("");
            }

            if(dvdt > 0.2) {
                code[pad] = 3;
            } else if(dvdt < -0.2) {
                code[pad] = 4;
            } else {
                digitalWrite(SW_CONTROL_A_1,HIGH);

                temp_dc_read = analogRead(ADC_IN) * 4.88;

                if(temp_dc_read <= 5.0) {
                    code[pad] = 1;
                } else if((temp_dc_read <= 1100.0) && (temp_dc_read >= 950.0)) {
                    code[pad] = 2;
                } else if((((temp_dc_read <= 600.0) && (temp_dc_read >= 400.0))) || ((temp_dc_read >= (Maximum_Voltage - 300.0)) && (temp_dc_read <= (Maximum_Voltage + 300.0)))) {
                    code[pad] = 5;
                } else {
                    code[pad] = 0;
                }

                if(debug) {
                    Serial.print("Pad: "); Serial.print((int)pad); Serial.print(" Voltage: "); Serial.print(temp_dc_read); Serial.println(" mV");
                    Serial.println("");
                }

            }

            if(!all_pads) {
                break;
            }

        case 4:
            pad = 4;
            digitalWrite(MUX_CONTROL2,LOW);digitalWrite(MUX_CONTROL3,LOW);digitalWrite(MUX_CONTROL4,HIGH);

            //Discharge
            digitalWrite(SW_CONTROL_B_1,LOW);

            delay(5);

            digitalWrite(SW_CONTROL_B_1,HIGH);

            digitalWrite(SW_CONTROL_A_1,HIGH);digitalWrite(SW_CONTROL_A_2,HIGH);

            start_timepoint = micros();

            //Do transient analysis first:
            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read_timepoints[x] = micros();
                temp_transient_read[x] = analogRead(ADC_IN);
                delayMicroseconds(10);
            }

            digitalWrite(SW_CONTROL_A_1,LOW);

            for(char x = 0 ; x < 5 ; x++) {
                temp_transient_read[x] *= 4.88;
                temp_transient_read_timepoints[x] -= start_timepoint;
            }

            dvdt = (temp_transient_read[4] - temp_transient_read[0]) / (temp_transient_read_timepoints[4] - temp_transient_read_timepoints[0]);

            if(debug == 1) {
                Serial.print("Pad: "); Serial.print((int)pad); Serial.println(" Transient Analysis:");
                for(char x = 0 ; x < 5 ; x++) {
                    Serial.print("Voltage Datapoint "); Serial.print((int)x); Serial.print(": "); Serial.print(temp_transient_read[x]); Serial.print(" mV @ time: ");
                    Serial.print(temp_transient_read_timepoints[x]); Serial.println(" uS");
                }
                Serial.print("dV/dt: "); Serial.print(dvdt); Serial.println(" mV/uS");
                Serial.println("");
            }

            if(dvdt > 0.2) {
                code[pad] = 3;
            } else if(dvdt < -0.2) {
                code[pad] = 4;
            } else {
                digitalWrite(SW_CONTROL_A_1,HIGH);

                temp_dc_read = analogRead(ADC_IN) * 4.88;

                if(temp_dc_read <= 5.0) {
                    code[pad] = 1;
                } else if((temp_dc_read <= 1100.0) && (temp_dc_read >= 950.0)) {
                    code[pad] = 2;
                } else if((((temp_dc_read <= 600.0) && (temp_dc_read >= 400.0))) || ((temp_dc_read >= (Maximum_Voltage - 300.0)) && (temp_dc_read <= (Maximum_Voltage + 300.0)))) {
                    code[pad] = 5;
                } else {
                    code[pad] = 0;
                }

                if(debug) {
                    Serial.print("Pad: "); Serial.print((int)pad); Serial.print(" Voltage: "); Serial.print(temp_dc_read); Serial.println(" mV");
                    Serial.println("");
                }
            }

            if(!all_pads) {
                break;
            }
    }

    disableSwitches();
    if(debug) {
        for(char i = 0;i<5;i++) {
            Serial.print(code[i]);
            if(i<4) {Serial.print(",");}
        }
        Serial.println("");
    }
}
