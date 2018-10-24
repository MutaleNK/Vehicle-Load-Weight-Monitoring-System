/*This class Represents a PIR object and assigns a value to it
@Author: Nkumbula Mutale II
@Date : 06/10/2018
Released into public domain
*/

#include "Pir.h"

class Pir;
Pir::Pir(int pin,int value){
    this -> pin = pin;
    this -> value = value;
}
Pir::Pir(){
    this -> pin = 0;
    this -> value = 0;
}
int Pir::get_value(){
    return this->value;
}
void Pir::set_value(int val){
    this->value = val;
}

