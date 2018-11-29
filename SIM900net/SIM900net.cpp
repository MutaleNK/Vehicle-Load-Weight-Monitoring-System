#include "SIM900net.h"

//Constructor
SIM900net::SIM900net(SoftwareSerial *ss){
    softSerial = ss;
}
void SIM900net::begin(int baud){softSerial->begin(baud);}
void SIM900net::justReadSoftSerial(){

  while(!softSerial->available()>0){/*Ensures the Arduino waits for a response*/}
  while(softSerial->available()>0 ){
    Serial.println(softSerial->readString());
  }
}

String SIM900net::readSoftSerial(){

  while(!softSerial->available()>0){/*Ensures the Arduino waits for a response*/}
  while(softSerial->available()>0 ){
    String _str = softSerial->readString();
    Serial.println(_str);
    return _str;
  }
}
void SIM900net::setVerboseError(){
    softSerial->println("AT+CMEE=2");
    readSoftSerial();
    softSerial->println("AT&W");
    readSoftSerial();
}
void SIM900net::attachGPRS(){    
    //Check Signal Quality
    softSerial->println("AT+CSQ");       
    justReadSoftSerial();

    //Set to GPRS Mode
    //Is this still necessary? I guess we'll never know 8(
    softSerial->println("AT+CGATT=1");
    justReadSoftSerial();

    //Set Connection Type to GPRS
    softSerial->println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    justReadSoftSerial();
    
    //Set APN    
    softSerial->println("AT+SAPBR=3,1,\"APN\",\"airtel\"");
    justReadSoftSerial();
     
    /*Enable GPRS
    *If it gives an error turn, it's probably cause it's already enabled.
    *You can ignore it or if it gives problems, disable it with
    *AT+SAPBR=0,1 and rerun this code :)
    */

    softSerial->println("AT+SAPBR=1,1");
    _chk = readSoftSerial();
    chkError(_chk,_error,0);


    //Verify IP Address, if the IP is 0.0.0.0 then GPRS isn't attached,
    //re-run this method with verbose error enabled.
    softSerial->println("AT+SAPBR=2,1");
    justReadSoftSerial();    
}
/*Method to deal with AT+SAPBR=1,1 issues.
*pass "true" to disable GPRS, false to enable, though
*I recommend to jus re-run attachGPRS() :|
*(this is shit code :| [11-20-2018])
*/
void SIM900net::termGPRS(){
    softSerial->println("AT+SAPBR=0,1");
    justReadSoftSerial();        
}
/*This is where the Magic happens,
*Before running this method, ensure that GPRS is atttached and that
* Http is initialised. :)
*/
void SIM900net::httpPOST(String param,String url){
        char data[100];
    param.toCharArray(data,100);

    /*
    //Query IP
    softSerial.println("AT+SAPBR=2,1");
    delay(50);
    Serial.println(softSerial.readString());
    */
    
    //Set the URL
  
    softSerial->print("AT+HTTPPARA=\"URL\",\""); 
    softSerial->print(url);
    softSerial->println("\"");     
    justReadSoftSerial();

    //Set  Http Content
    softSerial->println("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"");
    justReadSoftSerial();

    //Enter Data
    softSerial->print("AT+HTTPDATA=");    
    softSerial->print(strlen(data));
    softSerial->print(",");
    softSerial->println("10000");
    delay(2000);
    softSerial->println(data);
    justReadSoftSerial();

    //Send Data
    delay(3000);
    softSerial->println("AT+HTTPACTION=1");
    //softSerial->println("WAIT=6");
    readSoftSerial();
    delay(3000);

    /*
    //Read Response
    softSerial->println("AT+HTTPREAD");
    readSoftSerial();  
    */       
}
void SIM900net::initialiseHTTP(){
  //Initialize HTTP
  /*If this gives an error, call resetHTTP();
  */
    softSerial->println("AT+HTTPINIT");
    _chk = readSoftSerial();
    chkError(_chk,_error,1);

    //Set the Bearer profile 
    softSerial->println("AT+HTTPPARA=\"CID\",1");
    justReadSoftSerial();
 }
 void SIM900net::termHTTP(){
    softSerial->println("AT+HTTPTERM");
    justReadSoftSerial();
 }
 void SIM900net::chkError(String _rsp,String _str,int z){
     if(z == 1){
        if(_rsp.indexOf(_str) != -1){
         termHTTP();
         softSerial->println("AT+HTTPINIT");
         justReadSoftSerial();
     }
     }else if(z == 0){
        if(_rsp.indexOf(_str) != -1){
            termGPRS();
            softSerial->println("AT+SAPBR=1,1");
            justReadSoftSerial();
        }
     }

 }

