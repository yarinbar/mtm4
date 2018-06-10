//
// Created by Yarin on 08-Jun-18.
//

#ifndef PROJECT_WEAPON_H
#define PROJECT_WEAPON_H

#include <iostream>
#include <string.h>
using std::ostream;

typedef enum{
    LEVEL,
    STRENGTH,
    LIFE
} Target;



class Weapon{

private:
    char* name;
    Target target;
    int hitStrength;

public:
    // Constructor
    Weapon(const char* name, Target target, int hitStrength):
            name(new char [strlen(name) + 1]),
            target(target),
            hitStrength(hitStrength){

        strcpy(this->name,name);
    }

    // Constructor
    ~Weapon(){
        delete[] name;
    }

    // Copy Constructor
    Weapon(const Weapon& weapon):
            name(new char[strlen(weapon.name) + 1]),
            target(weapon.target),
            hitStrength(weapon.hitStrength){

        strcpy(this->name,weapon.name);
    }

    /**
     * get the weapon's target
     * @return the target
     */
    Target getTarget() const;

    /**
     * get the weapon's hitStrength
     * @return the hitStrength
     */
    int getHitStrength() const;

    /**
     * get the weapon's value
     * @return the value
     */
    int getValue() const;

    /**
     * override of printing operator
     * has a friend privlege to access the private fields
     * @param weapon - the weapon to print
     *        ostream - any output stream
     * @return an ostream object
     */
    friend ostream& operator<<(ostream&, const Weapon& weapon);

    /**
     * override of assignment operator
     * @param weapon - the new weapon to copy to this weapon
     * @return reference to this weapon
     */
    Weapon& operator=(const Weapon& weapon);

    /**
     * override of < operator
     * @param weapon1 - the first weapon
     * @param weapon2 - the second weapon
     * @return true if the first weapon's value is smaller then the second's,
     *         otherwise false
     */
    bool operator<(const Weapon& weapon) const;

    /**
  * override of > operator
  * @param weapon1 - the first weapon
  * @param weapon2 - the second weapon
  * @return true if the first weapon's value is bigger then the second's,
  *         otherwise false
  */
    bool operator>(const Weapon& weapon) const;
};

/**
 * override of == operator
 * symmetric operator
 * @param weapon1 - the first weapon
 * @param weapon2 - the second weapon
 * @return true if the weapons are equal, otherwise false
 */
bool operator==(const Weapon& weapon1, const Weapon& weapon2);

/**
 * override of != operator
 * symmetric operator
 * @param weapon1 - the first weapon
 * @param weapon2 - the second weapon
 * @return true if the weapons are not equal, otherwise false
 */
bool operator!=(const Weapon& weapon1, const Weapon& weapon2);








#endif //PROJECT_WEAPON_H
