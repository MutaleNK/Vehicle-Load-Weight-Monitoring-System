/*
Step_Sensor.h - Library to represent a step sensor.
will be used in the field to determine the direction in 
which a step is taken by the passenger.
@Author : Nkumbula Mutale II 
@Date : 06/10/2018
Released into public domain
*/
#ifndef Step_Sensor_h
#define Step_Sensor_h
#include "Arduino.h"
#include "Pir.h"

class Step_Sensor{
    public:

    Pir pir_sensors[2];             //Store Pir objects
    int order_Arr[2];               //Used to stored the order in which 
    int Step_direction(Pir sensor); //the PIR Sensors are triggered
    int oAIndex;            
    Step_Sensor(int,int);

    private:
    void pir_01_is_Triggered_ISR();
    void pir_02_is_Triggered_ISR();
    void both_triggered(Pir sensor);
    
};
#endif