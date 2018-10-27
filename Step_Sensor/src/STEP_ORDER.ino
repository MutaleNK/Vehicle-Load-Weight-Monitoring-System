#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>


#include <Pir.h>
#include <Step_Sensor.h>

Step_Sensor tracker(2,3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(tracker.pir_sensors[0].pin),pir_01_is_Triggered_ISR,HIGH);
  attachInterrupt(digitalPinToInterrupt(tracker.pir_sensors[1].pin),pir_02_is_Triggered_ISR,HIGH);  
  Serial.println("hey");
}

void loop() {
  
  if(tracker.isStep()){
    char dir[10];
    tracker.getDirection().toCharArray(dir,8);
    Serial.print("True :: ");
    Serial.print(dir);
    tracker.setStep(false);
    Serial.println();    
  }
 // Serial.println(tracker.isStep());
}
void pir_01_is_Triggered_ISR(){
  sei();
  tracker.both_triggered(tracker.pir_sensors[0]);
}
void pir_02_is_Triggered_ISR(){
  sei();
  tracker.both_triggered(tracker.pir_sensors[1]);
}
