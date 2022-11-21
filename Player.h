#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H

#include "Team.h"
#include "AVL_tree.h"


class Team;

class Player{
public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
    int get_score();
    int get_id();

    int operator~(); 
    int operator!();

private:
    int playerId;
    int teamId;
    int gamesPlayed;
    int goals;
    int cards;
    bool goalKeeper;
    Team *team;
};

#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
