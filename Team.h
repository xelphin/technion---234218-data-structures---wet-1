#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H

#include "Player.h"
#include "AVL_tree.h"
#include <memory>

class Player;

class Team{
public:
    Team(int id, int points);

    void add_player(std::shared_ptr<Player> player);
    std::shared_ptr<Player> find_player(int id);
    bool remove_player(int id);

    AVL_tree<std::shared_ptr<Player>>* get_AVL_tree_id();
    AVL_tree<std::shared_ptr<Player>>* get_AVL_tree_score();
    int get_id() const;
    int operator~();
    int operator!();

    void update_scoredGoals(int toAdd);
    void update_cardsReceived(int toAdd);
    void update_addAGoalKeeper(bool add);
    void update_removeAGoalKeeper(bool remove);
    void update_totalPoints(int toAdd);
    void update_wins();
    void update_gamesPlayed();
    int get_cards() const;
    int get_goals() const;
    int get_total_players() const;
    int get_total_points() const;
    int get_match_score() const;
    int get_gamesPlayed() const;

    friend std::ostream& operator<<(std::ostream& os, const Team& team);
    int compare(const Team& team2, bool sort_by_score) const;

private:
    int id;
    int total_players;
    int total_points; // ?
    int total_goals;
    int total_cards;
    int total_goalKeepers;
    int wins;
    int gamesPlayed;
    Player *top_scorer; //may be changed to a different type of pointer later on.
    AVL_tree<std::shared_ptr<Player>> team_players;
    AVL_tree<std::shared_ptr<Player>> team_players_scores;

    int get_points() const;
};

#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
