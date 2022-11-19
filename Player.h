#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H

#include "Team.h"

class Team;

class Player{
public:
    Player();
    int get_score();
    int get_id();

    int operator~();
    int operator!();
private:
    int id;
    int score;
    int cards;
    int games_played;
    Team *team;
};

#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
