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

    int operator~(); // NOTE: I think this is too cryptic -> Enums are better
    int operator!();

    AVL_tree<Player>::COMPARISON compare(Player& b, bool sortBy);

private:
    int playerId;
    int teamId;
    int gamesPlayed;
    int goals;
    int cards;
    bool goalKeeper;
    Team *team;

    AVL_tree<Player>::COMPARISON compareValues(int a_value, int b_value);
};

#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
