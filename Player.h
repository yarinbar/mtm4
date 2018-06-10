//
// Created by Yarin on 08-Jun-18.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <iostream>
#include <string.h>
#include "Weapon.h"

using std::cout;
using std::endl;

class Player{

    char* name;
    int level;
    int life;
    int strength;
    Weapon* weapon;
    int position;
    
public:
    // Constructor
    Player(const char* name, const Weapon& weapon):
            name(new char [strlen(name) + 1]), // +1 for 0 terminator
            level(1),
            life(1),
            strength(1),
            weapon(new Weapon(weapon)),
            position(0){

        strcpy(this->name, name);

    }

    // Destructor
    ~Player(){
        delete[] this->name;
        delete this->weapon;
    }

    // Copy Constructor
    Player(const Player& player):
            name(new char [strlen(player.name) + 1]),
            level(player.level),
            life(player.life),
            strength(player.strength),
            weapon(new Weapon(*player.weapon)),
            position(player.position){

        strcpy(this->name, player.name);
    }

    /**
     * increase the player level by 1
     */
    void nextLevel();

    /**
     * increase the player step by 1
     */
    void makeStep();

    /**
     * checks if playerName is this player's name
     * @param playerName - the name to check
     * @return true if this is the player's name, otherwise false
     */
    bool isPlayer(const char* playerName) const;
    void addLife();
    void addStrength(int strengthToAdd);
    bool isAlive()const;
    bool weaponIsWeak(int weaponMinStrength) const;
    bool fight(Player& player);

    bool operator<(const Player& player) const;
    bool operator>(const Player& player) const;
    friend ostream& operator<<(ostream& os, const Player& player);
    Player& operator=(const Player& player);
};






#endif //PROJECT_PLAYER_H
