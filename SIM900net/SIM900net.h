/*@Author Nkumbula Mutale II
*@Date 11-20-2018
*Purpose : Simple Library to send data to a remote server using
* the Arduino and SIM900 Module.(For Sibeso).
*Here are a few Error codes
*    600 Not HTTP PDU
*    601 Network Error
*    602 No memory
*    603 DNS Error
*    604 Stack Busy
*For any Error codes that throw you off, you can
*check the meaning for them at:
*https://www.micromedia-int.com/en/gsm-2/73-gsm/669-cme-error-gsm-equipment-related-errors
*FOR TINYSINE SHIELD::
*TXpin=2;
*RXpin=3;
*FOR GEETECH SHIELD::
*TXpin=8;
*RXpin=7;
*Released into Public domain
*/
#ifndef SIM900net_H
#define SIM900net_H

#include <Arduino.h>
#include <SoftwareSerial.h>

/*Create instance of Software Serial object,
*Alter pin numbers to suit your SIM900 Module*/
class SIM900net{
    public:
        SIM900net(SoftwareSerial *ss);         //Constructor;
        void httpPOST(String,String); 
        void termHTTP();       //If AT+HTTPINIT gives error, re-initalise HTTPStatus.(ON then OFF then ON)
        void termGPRS();       //If AT+SAPBR=1,1 gives error, re-initalise GPRS.(ON then OFF then ON)
        void attachGPRS();
        void initialiseHTTP();
        void begin(int);
    

    private:
        void chkError(String,String,int);
        String readSoftSerial();
        void justReadSoftSerial();
        void setVerboseError();          //State Error Messages?
        SoftwareSerial *softSerial;     //Software Serial object.(Dummy Figures)
        String _error = "ERROR";
        String _ok    = "OK";
        String _chk;                    //Check for Error


};
#endif /* SIM900net_H */
