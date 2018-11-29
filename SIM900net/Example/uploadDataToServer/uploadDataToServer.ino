#include <SIM900net.h>
#include <SoftwareSerial.h>


SoftwareSerial softSerial(2,3);
SIM900net GSM(&softSerial);

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  GSM.begin(4800);
  delay(3000);
  Serial.println("READY");
  
  GSM.attachGPRS();
  delay(3000);
  GSM.initialiseHTTP();
  delay(3000);
  GSM.httpPOST("temp=570","tempsensor.azurewebsites.net/getTemp.php");
}

void loop() {
  // put your main code here, to run repeatedly:
    serialhwRead();
  while(softSerial.available() > 0){
      Serial.println(softSerial.readString());
   }

}
void readSoftSerial(){
  while(!softSerial.available()>0){}
  while(softSerial.available() > 0 ){
    Serial.println(softSerial.readString());
  }
}
void serialhwRead(){
  String inSerial;
  if(Serial.available() > 0){
      while(Serial.available() > 0){
          inSerial = Serial.readString();
          delay(10);
      }
      softSerial.println(inSerial);
      //return inSerial;
   }
}
