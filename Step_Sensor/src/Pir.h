/*This class Represents a PIR object and assigns a value to it
@Author: Nkumbula Mutale II
@Date : 06/10/2018
Released into public domain
*/

#ifndef PIR_H
#define PIR_H

class Pir {
public:
    Pir(int, int);
    int pin;
    bool status;
    int get_value();

private:
    int value;
};

#endif /* PIR_H */

