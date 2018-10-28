#include "Step_Sensor.h"

//Constructor
Step_Sensor::Step_Sensor(int pir_01, int pir_02){
    
    //Create Pir Objects to represent actual PIR sensors
    this -> pir_sensors[0].pin = pir_01;
    this -> pir_sensors[0].set_value(2);
    this -> pir_sensors[1].pin = pir_02;
    this -> pir_sensors[1].set_value(1);

    //setup Arduino pins for input
    pinMode(pir_sensors[0].pin,INPUT);
    pinMode(pir_sensors[1].pin,INPUT);   
    
    oAIndex = 0;
}
void Step_Sensor::Step_direction(){
    int timeLimit = millis() + 1000;
       if(order_Arr[0] - order_Arr[1] == 1){
             step = true;
             lastStep =  "Forward";
             //if(millis() >= timeLimit){step = false;}
       }else if(order_Arr[0] - order_Arr[1] == -1){
             step = true;
             lastStep =  "Backward";
             //if(millis() >= timeLimit){step = false;}
       }
}
//This Methods ensures that actions are only taken if and 
//when both sensors are triggered. After a sensor is triggered
//it's value is added to  the order_Arr[], if the array does 
//not already contain the value of the other sensor, a 1000 millisecond 
//time limit is appled to it as a wait time for the second sensor to 
//be triggered(through an interrupt triggered at that pin) , 
//if the time limit elapses and only one value is contained in 
//the array it is reset. If order_Arr contains both values Step_direction()
//is called to check the direction.Whether or not order_Arr[] contains
//both values is determined by the position of the oAIndex value. if the 
//value is 1, it means a sensor was triggered and it's value occupies [0]
//and if the value is 0, then no sensors have been triggered yet.
void Step_Sensor::both_triggered(Pir sensor){
    switch(oAIndex){
        case 0:
            {
                order_Arr[oAIndex++] = sensor.get_value();
                int timeLimit = millis() + 1000;
                while(millis() <= timeLimit && oAIndex == 1){}  //Wait for Second Trigger

                //Once Time Limit elapses reset order_Arr   
                if(oAIndex == 1){
                    order_Arr[--oAIndex] = 0;
                    step = false; 
                }
                               
            }
            break;
           
        case 1:
            order_Arr[oAIndex] = sensor.get_value();
            oAIndex = 0;
            Step_direction();
            break;
    }
}
void clear_Arr(){
    order_Arr[0] = 0;
    order_Arr[1] = 0;
}
bool Step_Sensor::isStep(){
    return step;
}
String Step_Sensor::getDirection(){
    return lastStep;
}
void Step_Sensor::setStep(bool s){
    this->step = s;
}