#include "worldcup23a1.h"


world_cup_t::world_cup_t()
: amount_players(0), all_players_AVL(SORT_BY_ID), all_players_score_AVL(SORT_BY_SCORE),
  teams_AVL(SORT_BY_ID), valid_teams_AVL(SORT_BY_ID)
{}

world_cup_t::~world_cup_t()
{}


StatusType world_cup_t::add_team(int teamId, int points)
{
    std::cout << "Inside add_team: " << std::endl;
	if (teamId <= 0 || points<0)
        return StatusType::INVALID_INPUT;
    try {
        std::shared_ptr<Team> team(new Team(teamId, points));
        // valid_teams_AVL.add(team); TODO: Implement properly when needed later
        teams_AVL.add(team); // CHECK:
    } catch (std::bad_alloc const&){
        return StatusType::ALLOCATION_ERROR;
    } catch (const ID_ALREADY_EXISTS& e) {
        return StatusType::FAILURE;
    }
    std::cout << "Valid Teams: " << std::endl;
    std::cout << valid_teams_AVL.debugging_printTree();
    std::cout << "Teams: " << std::endl;
    std::cout << teams_AVL.debugging_printTree();
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    std::cout << "Inside remove_team: " << std::endl;
    bool success = false;
    if (teamId <=0) {
        return StatusType::INVALID_INPUT;
    }
	try {
        if (teams_AVL.find_id(teamId) != nullptr) { // O(log(k))
            // TODO: make more efficient instead of calling find_id twice (note: can't * if nullptr)
            Team* team = &(*((teams_AVL.find_id(teamId))->content)); // O(log(k))
            if (team->get_total_players() <= 0)
                return StatusType::FAILURE;
            success = teams_AVL.remove(teamId);
            valid_teams_AVL.remove(teamId);
        }

    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }
    std::cout << "Teams: " << std::endl;
    std::cout << teams_AVL.debugging_printTree();
    if (success)
            return StatusType::SUCCESS;
	return StatusType::FAILURE;
}

/*

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}
*/
