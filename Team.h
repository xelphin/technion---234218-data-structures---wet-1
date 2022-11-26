#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H

#include "Player.h"
#include "AVL_tree.h"

class Player;

class Team{
public:
    Team(int id);

    void add_player(Player* player);
    void remove_player(int id);
    AVL_tree<Player*>* get_AVL_tree_id();
    AVL_tree<Player*>* get_AVL_tree_score();
    int get_id() const;
    int operator~();
    int operator!();

    friend std::ostream& operator<<(std::ostream& os, const Team& team);
    int compare(const Team& team2, bool sort_by_score) const;

private:
    int id;
    int total_players;
    int total_points;
    int total_cards;
    Player *top_scorer; //may be changed to a different type of pointer later on.
    AVL_tree<Player*> team_players;
    AVL_tree<Player*> team_players_scores;

    int get_points() const;
};

#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
