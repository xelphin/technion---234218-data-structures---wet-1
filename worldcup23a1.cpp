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
            if (team->get_total_players() > 0)
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



StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    std::cout << "Inside add_player: " << std::endl;
    // INVALID INPUT (checks)
    if (teamId <= 0 || playerId <= 0 || gamesPlayed<0 || goals<0 || cards < 0)
        return StatusType::INVALID_INPUT;
    if (gamesPlayed==0 && (goals>0 || cards>0) )
        return StatusType::INVALID_INPUT;

    Team* team;
    if (teams_AVL.find_id(teamId) != nullptr && all_players_AVL.find_id(playerId) == nullptr) { // O(log(k) + log(n))
        // TODO: make more efficient instead of calling find_id twice (note: can't * if nullptr)
        // TEAM exists and PLAYER doesn't exist
        team = &(*((teams_AVL.find_id(teamId))->content)); // GET Team Content: O(log(k))
        // TRY Create PLAYER and ADD to TEAM and AVLs
        try {
            std::shared_ptr<Player> player(new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper));
            if (team!=nullptr) {
                team->add_player(player);
                team->update_cardsReceived(cards);
                team->update_scoredGoals(goals);
                team->update_addAGoalKeeper(goalKeeper);
            }
            else
                return StatusType::FAILURE;
            player->set_team(team);
            all_players_AVL.add(player);
            all_players_score_AVL.add(player);
        } catch (std::bad_alloc const&) { // EXCEPTION: Bad Alloc
            all_players_AVL.remove(playerId);
            all_players_score_AVL.remove(playerId);
            return StatusType::ALLOCATION_ERROR;
        } catch (const ID_ALREADY_EXISTS& e) { // EXCEPTION: ID already exists
            std::cout << "id: " << std::to_string(playerId) << " already exists" << std::endl;
            return StatusType::FAILURE;
        }

    } else {
        // TEAM DOES NOT EXIST
        std::cout << "team couldn't be found: " << std::to_string(teams_AVL.find_id(teamId) == nullptr)  << std::endl;
        std::cout << "player exists already: " << std::to_string(all_players_AVL.find_id(teamId) != nullptr)  << std::endl;
        return StatusType::FAILURE;
    }
    // SUCCESS
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    std::cout << "Inside remove_player: attempt remove" << std::to_string(playerId) << std::endl;
    std::cout << "(Before) Player_AVL: " << std::endl;
    std::cout << all_players_AVL.debugging_printTree();
    bool success1 = false;
    bool success2 = false;
    // INVALID INPUT
    if (playerId <=0) {
        return StatusType::INVALID_INPUT;
    }
    // ATTEMPT REMOVE
    try {
        // FIND PLAYER
        if (all_players_AVL.find_id(playerId) != nullptr) { // O(log(n))
            // TODO: make more efficient instead of calling find_id twice (note: can't * if nullptr)
            // PLAYER FOUND
            Player* player = &(*((all_players_AVL.find_id(playerId))->content)); // O(log(n))
            if (player != nullptr) { // note: have to do check for code to work
                Team* playerTeam = (*player).get_team();
                if (playerTeam != nullptr) {
                    // REMOVE from PLAYER_TEAM
                    success1 = (*playerTeam).remove_player(playerId); // we know: playerTeam != nullptr
                    // UPDATE PLAYER_TEAM
                    playerTeam->update_cardsReceived(-(player->get_cards())); // TODO: check if needed
                    playerTeam->update_scoredGoals(-(player->get_score()));
                    playerTeam->update_removeAGoalKeeper(player->get_isGoalKeeper());
                    // REMOVE from WORLD_CUP AVLs
                    success2 = all_players_AVL.remove(playerId);
                    all_players_score_AVL.remove(playerId);
                } else {
                    success1 = false;
                }
            } else {
                success2 = false;
            }

        } else {
            // PLAYER NOT FOUND
            std::cout << "Player not found, our Player_AVL: " << std::endl;
            std::cout << all_players_AVL.debugging_printTree();
            return StatusType::FAILURE;
        }

    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }

    if (success1 && success2) {
        return StatusType::SUCCESS;
    }
    // DON'T DELETE TILL FINISHED ALL DEBUGGING
    std::cout << "OUR ERROR - SHOULD NEVER GET HERE!!!!" << std::endl;

    return StatusType::FAILURE;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    std::cout << "Inside update_player_stats: attempt update: " << std::to_string(playerId) << std::endl;
    // INVALID INPUT
    if (playerId <=0 || gamesPlayed<0 || scoredGoals < 0 || cardsReceived < 0) {
        return StatusType::INVALID_INPUT;
    }
    // ATTEMPT UPDATE
    try {
        // FIND PLAYER
        if (all_players_AVL.find_id(playerId) != nullptr) { // O(log(n))
            // TODO: make more efficient instead of calling find_id twice (note: can't * if nullptr)
            // PLAYER FOUND
            Player* player = &(*((all_players_AVL.find_id(playerId))->content)); // O(log(k))
            if (player != nullptr) { // note: have to do check for code to work
                Team* playerTeam = (*player).get_team();
                if (playerTeam == nullptr)
                    return StatusType::FAILURE;
                // UPDATE PLAYER
                player->update_gamesPlayed(gamesPlayed);
                player->update_scoredGoals(scoredGoals);
                player->update_cardsReceived(cardsReceived);
                std::cout << "Player " << (playerId) << " gamesPlayed: " << (player->get_gamesPlayed())
                << " scoredGoals: " << (player->get_score()) << " cardsReceived: " << (player->get_cards()) << std::endl;
                // UPDATE TEAM
                playerTeam->update_cardsReceived(cardsReceived);
                playerTeam->update_scoredGoals(scoredGoals);
                // TODO: Check player/team really gets updated (not just from looking at prints)
            } else {
                std::cout << "OUR ERROR - SHOULD NEVER GET HERE!!!!" << std::endl;
                return StatusType::FAILURE;
            }

        } else {
            // PLAYER NOT FOUND
            std::cout << "Player not found, our Player_AVL: " << std::endl;
            std::cout << all_players_AVL.debugging_printTree();
            return StatusType::FAILURE;
        }

    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }
    //
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2) // O(log(k))
{
    // TODO: Check team really gets updated where necessary and properly -> Check from play_match test
    // INVALID INPUT
    if (teamId1 <=0 || teamId2<=0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    // FIND TEAMS O(log(k))
    Team* team1;
    Team* team2;
    if (teams_AVL.find_id(teamId1) != nullptr) {
        team1 = &(*((teams_AVL.find_id(teamId1))->content)); // GET Team Content: O(log(k))
    } else {
        return StatusType::FAILURE;
    }
    if (teams_AVL.find_id(teamId1) != nullptr) {
        team2 = &(*((teams_AVL.find_id(teamId2))->content)); // GET Team Content: O(log(k))
    } else {
        return StatusType::FAILURE;
    }
    // GET SCORES O(1)
    int score1 = team1->get_match_score();
    int score2 = team2->get_match_score();
    // APPLY POINTS O(1)
    if (score1 == score2) {
        team1->update_totalPoints(1);
        team2->update_totalPoints(1);
    } else if (score1 < score2) {
        team2->update_totalPoints(3);
    } else {
        team1->update_totalPoints(3);
    }
    // NOTE: Player->get_gamesPlayed() : takes into account Teams gamesPlayed
	return StatusType::SUCCESS;
}
/*
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
    // Make sure to put update the values of played_games in each team before you unite log(n), and whatever else
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
