//
// Created by Yarin on 08-Jun-18.
//

#include "Weapon.h"




Target Weapon::getTarget() const {
    return this->target;
}

int Weapon::getHitStrength() const{
    return this->hitStrength;
}

int Weapon::getValue() const{
    if(target == LEVEL)
        return hitStrength;
    else if(target == STRENGTH)
        return 2 * hitStrength;
    else
        return 3 * hitStrength;
}

ostream& operator<<(ostream& os,const Weapon& weapon){
    os << "{weapon name: " << weapon.name << ", weapon value:"
                                            << weapon.getValue() << "}";
    return os;
}


Weapon& Weapon::operator=(const Weapon& weapon){
    if(this == &weapon)
        return *this;

    delete[] this->name;
    this->name = new char [strlen(weapon.name) + 1];
    strcpy(this->name,weapon.name);

    this->target = weapon.target;
    this->hitStrength = weapon.hitStrength;

    return *this;
}

bool operator==(const Weapon& weapon1, const Weapon& weapon2){
    return weapon1.getValue() == weapon2.getValue();
}

bool operator!=(const Weapon& weapon1, const Weapon& weapon2){
    return !(weapon1.getValue() == weapon2.getValue());
}

bool operator<(const Weapon& weapon1, const Weapon& weapon2){
    return weapon1.getValue() < weapon2.getValue();
}

bool operator>(const Weapon& weapon1, const Weapon& weapon2){
    return !(weapon1.getValue() < weapon2.getValue()) && !(weapon1.getValue() == weapon2.getValue()) ;
}