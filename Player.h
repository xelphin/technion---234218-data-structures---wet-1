#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H

#include "Team.h"
#include "AVL_tree.h"


class Team;

class Player{
public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);

    int get_score() const;
    int get_id() const;
    int get_gamesPlayed() const;
    int get_cards() const;
    bool get_isGoalKeeper() const;
    Team* get_team() const;
    int compare(const Player& player2, bool sort_by_score) const;
    int operator SCORE() const;
    int operator ID() const;

    void set_team(Team* playerTeam);
    void update_gamesPlayed(int toAdd);
    void update_scoredGoals(int toAdd);
    void update_cardsReceived(int toAdd);


    friend std::ostream& operator<<(std::ostream& os, const Player& player);

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
