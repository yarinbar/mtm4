//
// Created by Yarin on 08-Jun-18.
//

#include "Game.h"

static void swap(Player** a, Player** b){
    Player* temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

static int indexOfMax (Player** a, int n){
    int i, iMax = 0;
    for(i = 1; i < n; i++){
        if(*a[i] > *a[iMax]) iMax = i;
    }
    return iMax;
}

// recursive
static void maxSort(Player** a, int n){
    if (n == 1) return;

    int iMax = indexOfMax(a, n);

    swap(&a[n - 1], &a[iMax]);
    maxSort(a, n - 1);
}

bool Game::isPlayerExist(const char* name) const{

    for(int i = 0; i < currentPlayers; i++){
        if(players[i]->isPlayer(name))
            return true;
    }

    return false;
}

bool Game::isGameFull() const{
    return currentPlayers == maxPlayers;
}

Player Game::getPlayer(const char* playerName) const{

    for(int i = 0; i < currentPlayers; i++){
        if(players[i]->isPlayer(playerName))
            return *players[i];
    }

    //will not get here
    return *players[0];
}

void Game::removePlayer(const char* playerName){

    for(int i = 0; i < currentPlayers; i++){
        // if this is the player to delete, delete it and move the last player
        // to his place instead
        if(players[i]->isPlayer(playerName)){
            delete players[i];
            players[i] = players[currentPlayers - 1];
            currentPlayers--;
        }
    }

}

//----------------------- End of Private Functions -----------------------//

GameStatus Game::addPlayer(const char* playerName, const char* weaponName,
                           Target target, int hitStrength){

    if((target != LEVEL && target != STRENGTH && target != LIFE)
       || hitStrength < 0)
        return INVALID_PARAM;

    if(isPlayerExist(playerName))
        return NAME_ALREADY_EXISTS;

    if(isGameFull())
        return GAME_FULL;

    Weapon weapon(weaponName, target, hitStrength);

    if(currentPlayers == 0)
        players[0] = new Player(playerName, weapon);
    else
        players[currentPlayers] = new Player(playerName, weapon);

    currentPlayers ++;
    return SUCCESS;
}

GameStatus Game::nextLevel(const char* playerName) const{

    if(!isPlayerExist(playerName))
        return NAME_DOES_NOT_EXIST;

    for(int i = 0; i < currentPlayers; i++){
        if(players[i]->isPlayer(playerName)){
            players[i]->nextLevel();
            return SUCCESS;
        }
    }
    return SUCCESS;
}


GameStatus Game::makeStep(const char* playerName) const{

    if(!isPlayerExist(playerName))
        return NAME_DOES_NOT_EXIST;

    for(int i = 0; i < currentPlayers; i++){
        if(players[i]->isPlayer(playerName)){
            players[i]->makeStep();
            return SUCCESS;
        }
    }
    return SUCCESS;
}

GameStatus Game::addLife(const char* playerName) const{

    if(!isPlayerExist(playerName))
        return NAME_DOES_NOT_EXIST;

    for(int i = 0; i < currentPlayers; i++){
        if(players[i]->isPlayer(playerName)){
            players[i]->addLife();
            return SUCCESS;
        }
    }
    return SUCCESS;
}

GameStatus Game::addStrength(const char * playerName, int strengthToAdd) const{

    if(!isPlayerExist(playerName))
        return NAME_DOES_NOT_EXIST;

    if(strengthToAdd < 0)
        return INVALID_PARAM;

    for(int i = 0; i < currentPlayers; i++){
        if(players[i]->isPlayer(playerName)){
            players[i]->addStrength(strengthToAdd);
            return SUCCESS;
        }
    }
    return SUCCESS;
}

bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength){
    bool isRemoved = false;
    int numCurrentPlayers = currentPlayers;
    Player** temp_players = new Player*[maxPlayers]();
    for(int i = 0, j = 0; i < numCurrentPlayers; i++){
        if(players[i]->weaponIsWeak(weaponStrength)){
            delete players[i];
            this->currentPlayers--;
            isRemoved = true;
        }
        else{
            //if we don't want to delete this player, save it in the temp array
            temp_players[j] = players[i];
            j++;
        }
    }

    //if we removed some players
    if(isRemoved){
        //replace the game player array (after deletions) with the temp array
        delete[] this->players;
        this->players = temp_players;
    }
    else{
        //if we didn't removed any player just delete the temp array
        delete[] temp_players;
    }
    return isRemoved;
}

GameStatus Game::fight(const char* playerName1, const char* playerName2){

    if(!isPlayerExist(playerName1) || !isPlayerExist(playerName2))
        return NAME_DOES_NOT_EXIST;

    Player player1 = getPlayer(playerName1);
    Player player2 = getPlayer(playerName2);

    if(!player1.fight(player2))
        return FIGHT_FAILED;

    if(!player1.isAlive())
        removePlayer(playerName1);
    if(!player2.isAlive())
        removePlayer(playerName2);

    return SUCCESS;
}


ostream& operator<<(ostream& os,const Game& game){

    Player** temp_players = new Player*[game.currentPlayers]();
    for(int i = 0; i < game.currentPlayers; i++){
        temp_players[i] = game.players[i];
    }
    maxSort(temp_players, game.currentPlayers);

    for(int i = 0; i < game.currentPlayers; i++){
        os << "player " << i << ": " << *temp_players[i] << "}," << endl;
    }

    delete[] temp_players;
    return os;
}


Game& Game::operator=(const Game& game){
    if(this == &game)
        return *this;

    for(int i = 0; i < this->currentPlayers; i++){
        delete this->players[i];
    }
    delete[] this->players;

    this->maxPlayers = game.maxPlayers;
    this->currentPlayers = game.currentPlayers;


    this->players = new Player*[maxPlayers]();
    for(int i = 0; i < this->currentPlayers; i++){
        this->players[i] = new Player(*game.players[i]);
    }

    return *this;
}