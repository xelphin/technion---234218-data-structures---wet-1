#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H

#include "Player.h"
#include "AVL_tree.h"
#include <memory>

class Player;

class Team{
public:
    Team(int id, int points);
    Team(int id, int points, int total_players, int total_goals, int total_cards, int total_goalKeepers, std::shared_ptr<Player> top_scorer,
         AVL_tree<std::shared_ptr<Player>>* team1_players, AVL_tree<std::shared_ptr<Player>>* team2_players,
         AVL_tree<std::shared_ptr<Player>>* team1_players_scores, AVL_tree<std::shared_ptr<Player>>* team2_players_scores);

    void add_player(const std::shared_ptr<Player>& player);
    std::shared_ptr<Player> find_player(int player_id);
    bool remove_player(int player_id);

    int get_id() const;
    int get_cards() const;
    int get_goals() const;
    int get_total_players() const;
    int get_total_points() const;
    int get_match_score() const;
    int get_gamesPlayed() const;
    int get_totalGoalKeepers() const;
    int compare(const Team& team2, bool sort_by_score) const;
    bool get_isValid() const;
    int operator ID() const;
    int operator SCORE() const;
    std::shared_ptr<Player> get_top_scorer();

    void update_scoredGoals(int toAdd);
    void update_cardsReceived(int toAdd);
    void update_addAGoalKeeper(bool add);
    void update_removeAGoalKeeper(bool remove);
    void update_totalPoints(int toAdd);
    void update_gamesPlayed();
    void compare_to_top_scorer(const std::shared_ptr<Player> &sharedPtr);


    // PRINTING AND DEBUGGING
    friend std::ostream& operator<<(std::ostream& os, const Team& team);
    AVL_tree<std::shared_ptr<Player>>* get_AVL_tree_id(); // a pointer to an AVL tree of player nodes
    AVL_tree<std::shared_ptr<Player>>* get_AVL_tree_score(); // a pointer to an AVL tree of player nodes

private:
    int id;
    int total_players;
    int total_points; // ?
    int total_goals;
    int total_cards;
    int total_goalKeepers;
    int gamesPlayed;
    std::shared_ptr<Player> top_scorer; //should get updated when a player is added or removed
    AVL_tree<std::shared_ptr<Player>> team_players;
    AVL_tree<std::shared_ptr<Player>> team_players_scores;

    int get_points() const;
};

#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_TEAM_H
