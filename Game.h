//
// Created by Yarin on 08-Jun-18.
//

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Player.h"
#include "Weapon.h"

typedef enum{
    INVALID_PARAM,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXIST,
    FIGHT_FAILED,
    SUCCESS
}GameStatus;


class Game {
private:
    int maxPlayers;
    Player** players;
    int currentPlayers;

    /**
     * checks if a player with "playerName" exists in the game
     * @param playerName - the name to check
     * @return true if the play exists, otherwise false
     */
    bool isPlayerExist(const char* playerName) const;

    /**
     * checks if the game is full (if currentPlayers equals maxPlayers)
     * @return true if the game is full, otherwise false
     */
    bool isGameFull() const;

    /**
     * gets a Player by it's name
     * @param playerName - the name of the player to get
     * @return player by value
     */
    Player getPlayer(const char* playerName) const;

    /**
     * removes a given player from the game
     * @param playerName - the name of the player to remove
     */
    void removePlayer(const char* playerName);

public:
    // Constructor
    explicit Game(int maxPlayers):
                    maxPlayers(maxPlayers),
                    players(new Player*[maxPlayers]()),
                    currentPlayers(0)
                    {

    }

    // Destructor
    ~Game(){
        for(int i = 0; i < currentPlayers; i++){
            delete players[i];
        }
        delete[] players;
    }

    // Copy Constructor
    Game(const Game& game):
            maxPlayers(game.maxPlayers),
            players(new Player*[game.maxPlayers]()),
            currentPlayers(game.currentPlayers){

        for(int i = 0; i < currentPlayers; i++){
            players[i] = new Player(*game.players[i]);
        }

    }

    /**
     * adding new player to the game
     * @param playerName - the name of the new player
     * @param weaponName - the weapon name of the new player
     * @param target - the new weapon's target
     * @param hitStrength - the new weapon's strength
     * @return returns the following status:
     *         NAME_ALREADY_EXISTS - if there is already a player in
     *                               the game with that name
     *         GAME_FULL - there is no place left in the game
     *         SUCCESS - the operation worked
     */
    GameStatus addPlayer(const char* playerName, const char* weaponName,
                            Target target, int hitStrength);

    /**
     * increase a player's level
     * @param playerName - the name of the player
     * @return returns the following status:
     *         NAME_DOES_NOT_EXIST - there's no player with this name in game
     *         SUCCESS - the operation worked
     */
    GameStatus nextLevel(const char* playerName) const ;

    /**
     * increase a player's step
     * @param playerName - the name of the player
     * @return returns the following status:
     *         NAME_DOES_NOT_EXIST - there's no player with this name in game
     *         SUCCESS - the operation worked
     */
    GameStatus makeStep(const char* playerName) const ;

    /**
     * increase a player's life
     * @param playerName - the name of the player
     * @return returns the following status:
     *         NAME_DOES_NOT_EXIST - there's no player with this name in game
     *         SUCCESS - the operation worked
     */
    GameStatus addLife(const char* playerName) const ;

    /**
     * increase a player's strength by a given amount
     * @param playerName - the name of the player
     * @param strengthToAdd - the amount of strength to add
     * @return returns the following status:
     *         NAME_DOES_NOT_EXIST - there's no player with this name in game
     *         INVALID_PARAM - if the amount to add is negative
     *         SUCCESS - the operation worked
     */
    GameStatus addStrength(const char* playerName, int strengthToAdd) const ;

    /**
     * removes all the player which their weapon's strength is lower then the
     * given amount
     * @param weaponStrength - the strength to filter by
     * @return true if players were removed, otherwise false
     */
    bool removeAllPlayersWithWeakWeapon(int weaponStrength);

    /**
     * activates fight between to players
     * @param playerName1 - the name of the first player in the fight
     * @param playerName2 - the name of the second player in the fight
     * @return returns the following status:
     *         NAME_DOES_NOT_EXIST - there's no player with this name in game
     *         FIGHT_FAILED - player's fight function returned false (the fight
     *                        didn't accured)
     *         SUCCESS - the operation worked
     */
    GameStatus fight(const char* playerName1, const char* playerName2);

    /**
     * printing operator for game
     * @return an ostream object
     */
    friend ostream& operator<<(ostream&, const Game&);

    Game& operator=(const Game& game);

};



#endif //PROJECT_GAME_H
