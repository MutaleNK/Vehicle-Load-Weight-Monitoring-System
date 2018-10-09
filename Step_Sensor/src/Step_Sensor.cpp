#include "Step_Sensor.h"

//Constructor
Step_sensor::Step_sensor(int pir_01, int pir_02){
    
    //Create Pir Objects to represent actual PIR sensors
    this -> pir_sensors[0] {pir_01,1};
    this -> pir_sensors[1] {pir_02,2};

    //setup Arduino pins for input
    pinMode(pir_sensors[0].pin,INPUT);
    pinMode(pir_sensors[1].pin,INPUT);   

    attachInterrupt(digitalPinToInterrupt(pir_sensors[0].pin),pir_01_is_Triggered_ISR,RISING);
    attachInterrupt(digitalPinToInterrupt(pir_sensors[1].pin),pir_02_is_Triggered_ISR,RISING);


    oAIndex = 0;
}
string Step_sensor::Step_direction(){
       if(order_Arr[0] - order_Arr[1] == 1)
             return "Forward";
       else if(order_Arr[0] - order_Arr[1] == -1)
             return "Backward";
}
void pir_01_is_Triggered_ISR();{
    both_triggered(this.pir_sensors[0].value);
}
void pir_02_is_Triggered_ISR();{
    both_triggered(this.pir_sensors[1].value);
}
//This Methods ensures that actions are only taken if and 
//when both sensors are triggered. After a sensor is triggered
//it's value is added to  the order_Arr[], if the array does 
//not already contain the value of the other sensor, a 1000 millisecond 
//time limit is appled to it as a wait time for the second sensor to 
//be triggered, if the time limit elapses and only one value is contained in 
//the array it is reset. If order_Arr contains both values Step_direction()
//is called to check the direction.Whether or not order_Arr[] contains
//both values is determined by the position of the oAIndex value. if the 
//value is 1, it means a sensor was triggered and it's value occupies [0]
//and if the value is 0, then no sensors have been triggered yet.
void both_triggered(pir sensor){
    switch(oAIndex){
        case 0:
            order_Arr[oAIndex++] = sensor.get_value();
            int timeLimit = millis() + 1000;
            if(millis() >= timeLimit && oAIndex == 1){
                order_Arr[--oAIndex] = 0;
            }
            break;
        case 1:
            order_Arr[oAIndex] = sensor.get_value();
            oAIndex = 0;
            Step_direction();
            break;
    }
}
