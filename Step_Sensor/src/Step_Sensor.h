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
#include "String.h"
#include "Arduino.h"
#include "Pir.h"

class Step_Sensor{
    public:

    Pir pir_sensors[2];             //Store Pir objects
    volatile int order_Arr[2];      //Used to stored the order in which 
    volatile int oAIndex;

    bool isStep();                  //Return value of step.
    void setStep(bool);
    String getDirection();          //Return the last step direction
    void Step_direction();          //the PIR Sensors are triggered
    Step_Sensor(int,int);
    void both_triggered(Pir sensor);    

    private:
    bool step = false;              //Has someone stepped across the sensors? 
    String lastStep;

    
};
#endif
