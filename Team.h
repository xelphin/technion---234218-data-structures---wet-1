#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H

#include "Player.h"
#include "AVL_tree.h"

class Player;

class Team{
public:
    Team(int id, int totalPlayers, int totalPoints, int totalCards, Player *topScorer);

    void add_player();
    int get_id();
    int operator~();
    int operator!();
private:
    int id;
    int total_players;
    int total_points;
    int total_cards;
    Player *top_scorer; //may be changed to a different type of pointer later on.
    AVL_tree<Player> team_players;
    AVL_tree<Player> team_players_scores;

    int get_points();
};

#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
