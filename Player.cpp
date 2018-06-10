//
// Created by Yarin on 08-Jun-18.
//

#include "Player.h"


void Player::nextLevel(){
    this->level ++;
    return;
}

void Player::makeStep(){
    this->position ++;
}

bool Player::isPlayer(const char* playerName) const{
    if(strcmp(playerName, name) == 0)
        return true;

    return false;
}

void Player::addLife(){
    this->life ++;
}

void Player::addStrength(int strengthToAdd){
    this->strength += strengthToAdd;
}

bool Player::isAlive()const{
    if(life > 0 && strength > 0 && level > 0)
        return true;

    return false;
}

bool Player::weaponIsWeak(int weaponMinStrength) const{
    if(weapon->getValue() < weaponMinStrength)
        return true;

    return false;
}

bool Player::fight(Player& player){

    // if position is not the same return false
    if(player.position != this->position)
        return false;

    // if the weapon power is the same return false
    if(player.weapon->getValue() == this->weapon->getValue())
        return false;


    Player* target_player;
    Target target;
    int damage = 0;

    if(this->weapon > weapon){
        target_player = &player;
        target = this->weapon->getTarget();
        damage = this->weapon->getHitStrength();
    }
    else{
        target_player = &*this;
        target = player.weapon->getTarget();
        damage = player.weapon->getHitStrength();
    }

    if(target == LIFE){
        while(target_player->life > 0 && damage > 0){
            target_player->life --;
            damage--;
        }
    }

    if(target == LEVEL){
        while(target_player->level > 0 && damage > 0){
            target_player->level --;
            damage--;
        }
    }

    if(target == STRENGTH){
        while(target_player->strength > 0 && damage > 0){
            target_player->strength --;
            damage--;
        }
    }

    return true;
}

ostream& operator<<(ostream& os, const Player& player){
    os << "{player name: " << player.name << ", weapon: "
       << *player.weapon;
    return os;
}

bool Player::operator<(const Player& player) const{
    return strcmp(this->name, player.name) < 0;
}


bool Player::operator>(const Player& player) const{
    return strcmp(this->name, player.name) > 0;
}

Player& Player::operator=(const Player& player){

    if(this == &player)
        return *this;

    delete[] this->name;
    this->name = new char[strlen(player.name) + 1];
    strcpy(this->name, player.name);

    delete this->weapon;
    this->weapon = new Weapon(*player.weapon);

    this->position = player.position;
    this->life = player.life;
    this->strength = player.strength;
    this->level = player.level;

    return *this;
}
