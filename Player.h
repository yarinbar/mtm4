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

    /**
     * increase the player life by 1
     */
    void addLife();

    /**
     * increase the player's strength by strengthToAdd
     * @param strengthToAdd - the amount of strength to add
     */
    void addStrength(int strengthToAdd);

    /**
     * checks the strength, life, level of the player
     * @return true if all of them is different from 0, false otherwise
     */
    bool isAlive()const;

    /**
     * check if the player's weapon value is lower then weaponMinStrength
     * @param weaponMinStrength - the filter to check
     * @return
     */
    bool weaponIsWeak(int weaponMinStrength) const;

    /**
     * initiate fight between this player and the given player
     * @param player - the opponent
     * @return true if the fight happened, otherwise false
     */
    bool fight(Player& player);

    /**
     * override of printing operator
     * has a friend privlege to access the private fields
     * @param player - the player to print
     *        ostream - any output stream
     * @return an ostream object
     */
    friend ostream& operator<<(ostream& os, const Player& player);

    /**
     * override of assignment operator
     * @param player - the new player to copy to this plaer
     * @return reference to this weapon
     */
    Player& operator=(const Player& player);

    /**
     * override of < operator
     * @param player1 - player 1 to compare
     * @param player2 - player 2 to compare
     * @return true if the first player's name smaller lexicography then the
     *         given's, otherwise false
     */
    friend bool operator<(const Player& player1, const Player& player2);

    /**
     * override of < operator
     * @param player1 - player 1 to compare
     * @param player2 - player 2 to compare
     * @return true if the first player's name bigger lexicography then the
     *         given's, otherwise false
     */
    friend bool operator>(const Player& player1, const Player& player2);

};






#endif //PROJECT_PLAYER_H
