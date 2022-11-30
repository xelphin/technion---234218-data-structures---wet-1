#include "worldcup23a1.h"


world_cup_t::world_cup_t()
: amount_players(0), all_players_AVL(SORT_BY_ID), all_players_score_AVL(SORT_BY_SCORE),
  teams_AVL(SORT_BY_ID), valid_teams_AVL(SORT_BY_ID)
{}

world_cup_t::~world_cup_t()
{}


StatusType world_cup_t::add_team(int teamId, int points)
{

	if (teamId <= 0 || points < 0)
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
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    bool success = false;
    if (teamId <=0) {
        return StatusType::INVALID_INPUT;
    }
	try {
        Team* team = &(*(teams_AVL.get_content(teamId))); // O(log(k))
        if (team != nullptr) {
            if (team->get_total_players() > 0)
                return StatusType::FAILURE;
            success = teams_AVL.remove(teamId);
            if (success){ // also needs to remove from other AVL
                valid_teams_AVL.remove(teamId);
            }
        }
        else{
            return StatusType::FAILURE;
        }
    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }

    return success ? StatusType::SUCCESS : StatusType::FAILURE;
}



StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    // INVALID INPUT (checks)
    if (teamId <= 0 || playerId <= 0 || gamesPlayed<0 || goals<0 || cards < 0)
        return StatusType::INVALID_INPUT;
    if (gamesPlayed==0 && (goals>0 || cards>0) )
        return StatusType::INVALID_INPUT;

    Team* team = &(*(teams_AVL.get_content(teamId))); // O(log(k))
    if (team != nullptr && all_players_AVL.find_id(playerId) == nullptr) { // O(log(k) + log(n))
        // TEAM exists and PLAYER doesn't exist
        // TRY to Create PLAYER and ADD to TEAM and AVLs
        try {
            std::shared_ptr<Player> player(new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper));
            team->add_player(player);
            team->update_cardsReceived(cards);
            team->update_scoredGoals(goals);
            team->update_addAGoalKeeper(goalKeeper);

            player->set_team(team);
            all_players_AVL.add(player);
            all_players_score_AVL.add(player);
        } catch (std::bad_alloc const&) { // EXCEPTION: Bad Alloc
            all_players_AVL.remove(playerId);
            all_players_score_AVL.remove(playerId);
            return StatusType::ALLOCATION_ERROR;
        } catch (const ID_ALREADY_EXISTS& e) { // EXCEPTION: ID already exists
            return StatusType::FAILURE;
        }

    } else {
        // TEAM DOES NOT EXIST
        return StatusType::FAILURE;
    }
    // SUCCESS
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    bool success1 = false;
    bool success2 = false;
    // INVALID INPUT
    if (playerId <=0) {
        return StatusType::INVALID_INPUT;
    }
    // ATTEMPT REMOVE
    try {
        // FIND PLAYER
        Player* player = &(*(all_players_AVL.get_content(playerId))); // O(log(n))
        if (player != nullptr) {
            // PLAYER FOUND
            Team* playerTeam = (*player).get_team();
            if (playerTeam != nullptr) {
                // REMOVE from PLAYER_TEAM
                success1 = (*playerTeam).remove_player(playerId); // we know: playerTeam != nullptr
                // UPDATE PLAYER_TEAM
                playerTeam->update_cardsReceived(-(player->get_cards())); // TODO: check if needed
                playerTeam->update_scoredGoals(-(player->get_score()));
                playerTeam->update_removeAGoalKeeper(player->get_isGoalKeeper());
            } else {
                success1 = false;
            }
            // REMOVE from WORLD_CUP AVLs (even if player does not have a team)
            success2 = all_players_AVL.remove(playerId);
            all_players_score_AVL.remove(playerId);
        } else {
            // PLAYER NOT FOUND
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
    if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0) {
        return StatusType::INVALID_INPUT;
    }
    // ATTEMPT UPDATE
    try {
        // FIND PLAYER
        Player* player = &(*(all_players_AVL.get_content(playerId))); // O(log(players))
        if (player != nullptr) {
            // PLAYER FOUND
            Team* playerTeam = (*player).get_team();
            if (playerTeam == nullptr)
                return StatusType::FAILURE;
            // UPDATE PLAYER
            player->update_gamesPlayed(gamesPlayed);
            player->update_scoredGoals(scoredGoals);
            player->update_cardsReceived(cardsReceived);
            // UPDATE TEAM
            playerTeam->update_cardsReceived(cardsReceived);
            playerTeam->update_scoredGoals(scoredGoals);
            // TODO: Check player/team really gets updated (not just from looking at prints)
        } else {
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
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    //GET Team Content: O(log(k))
    Team* team1 = &(*teams_AVL.get_content(teamId1));
    Team* team2 = &(*teams_AVL.get_content(teamId2));
    if(team1 == nullptr || team2 == nullptr){
        return StatusType::FAILURE;
    }
    if (!(team1->get_isValid()) || !(team2->get_isValid())) {
        return StatusType::FAILURE;
    }
    // GET SCORES O(1)
    int score1 = team1->get_match_score();
    int score2 = team2->get_match_score();
    // APPLY POINTS O(1)
    if (score1 == score2) {
        team1->update_totalPoints(1);
        team2->update_totalPoints(1);
        std::cout << "Tie" << std::endl;
    } else if (score1 < score2) {
        team2->update_totalPoints(3);
        std::cout << "Team: " << (teamId2) << "won" << std::endl;
    } else {
        team1->update_totalPoints(3);
        std::cout << "Team: " << (teamId1) << "won" << std::endl;;
    }
    // UPDATE GAMES PLAYED O(1)
    team1->update_gamesPlayed();
    team2->update_gamesPlayed();
    // NOTE: Player->get_gamesPlayed() : takes into account Teams gamesPlayed
	return StatusType::SUCCESS;
}
/*
output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    // CHECK INVALID INPUT
    if (playerId <= 0)
        return StatusType::INVALID_INPUT;
    // FIND PLAYER
    Player* player = &(*(all_players_AVL.get_content(playerId))); // O(log(n))
    // CHECK PLAYER
    if (player == nullptr)
        return StatusType::FAILURE;
    // RETURN
    return player->get_gamesPlayed();
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
