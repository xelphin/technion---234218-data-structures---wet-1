// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef WORLDCUP23A1_H_
#define WORLDCUP23A1_H_

#include "wet1util.h"
#include <iostream>
#include <memory>

#include "AVL_tree.h"
#include "Player.h"
#include "Team.h"
#include "NodeList.h"

class world_cup_t {
private:
    // Here you may add anything you want
    int amount_players;
    int top_scorer_id;
    void set_top_scorer();

	AVL_tree<std::shared_ptr<Player>> all_players_AVL;
    AVL_tree<std::shared_ptr<Player>> all_players_score_AVL;
    AVL_tree<std::shared_ptr<Team>> teams_AVL;
    AVL_tree<std::shared_ptr<Team>> valid_teams_AVL;
    NodeList sorted_score_List;
	
public:
	// <DO-NOT-MODIFY> {
	
	world_cup_t();
	virtual ~world_cup_t();
	
	StatusType add_team(int teamId, int points);
	
	StatusType remove_team(int teamId);
	
	StatusType add_player(int playerId, int teamId, int gamesPlayed,
	                      int goals, int cards, bool goalKeeper);
	
	StatusType remove_player(int playerId);
	
	StatusType update_player_stats(int playerId, int gamesPlayed,
	                                int scoredGoals, int cardsReceived);
	
	StatusType play_match(int teamId1, int teamId2);
	
	output_t<int> get_num_played_games(int playerId);
	
	output_t<int> get_team_points(int teamId);
	
	StatusType unite_teams(int teamId1, int teamId2, int newTeamId);
	
	output_t<int> get_top_scorer(int teamId);
	
	output_t<int> get_all_players_count(int teamId);
	
	StatusType get_all_players(int teamId, int *const output);
	
	output_t<int> get_closest_player(int playerId, int teamId);
	
	output_t<int> knockout_winner(int minTeamId, int maxTeamId);
	
	// } </DO-NOT-MODIFY>
    void add_player_to_sorted_score_list(const std::shared_ptr<Player>& player);
};

#endif // WORLDCUP23A1_H_
