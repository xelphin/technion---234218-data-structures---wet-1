#include "worldcup23a1.h"
#include "Exception.h"

world_cup_t::world_cup_t()
: amount_players(0), top_scorer_id(0), all_players_AVL(SORT_BY_ID), all_players_score_AVL(SORT_BY_SCORE),
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
        if(team->get_isValid()){
            valid_teams_AVL.add(team);
        }
        if (team == nullptr){
            throw;
        }
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
        bool team_valid_before_action = team->get_isValid();
        // TEAM exists and PLAYER doesn't exist
        // TRY to Create PLAYER and ADD to TEAM and AVLs
        try {
            // Create player
            std::shared_ptr<Player> player(new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper));
            player->set_team(team);
            // Update team
            team->add_player(player);
            team->update_cardsReceived(cards);
            team->update_scoredGoals(goals);
            team->update_addAGoalKeeper(goalKeeper);
            // Add team to valid_teams_AVL
            if (team->get_isValid() && !team_valid_before_action){
                valid_teams_AVL.add(teams_AVL.get_content(teamId));
            }
            // Add player to AVLs
            player->set_team(team);
            player->update_gamesPlayed(-team->get_gamesPlayed());
            all_players_AVL.add(player);
            player->set_global_score_node(all_players_score_AVL.add(player));
            set_top_scorer();

            add_player_to_sorted_score_list(player);


        } catch (std::bad_alloc const&) { // EXCEPTION: Bad Alloc
//            all_players_AVL.remove(playerId); //no need to free memory since we are using a shared pointer and tree d'tor.
//            all_players_score_AVL.remove_by_item(player);
            return StatusType::ALLOCATION_ERROR;
        } catch (const ID_ALREADY_EXISTS& e) { // EXCEPTION: ID already exists
            return StatusType::FAILURE;
        }

    } else {
        // TEAM DOES NOT EXIST
        return StatusType::FAILURE;
    }
    // SUCCESS
    amount_players++;
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
        std::shared_ptr<Player> player = all_players_AVL.get_content(playerId); // O(log(n))
        if (player != nullptr) {
            // PLAYER FOUND
            Team* playerTeam = (*player).get_team();
            bool team_valid_before_action = playerTeam->get_isValid();
            if (playerTeam != nullptr) {
                // REMOVE from PLAYER_TEAM
                success1 = (*playerTeam).remove_player(playerId); // we know: playerTeam != nullptr
                // UPDATE PLAYER_TEAM
                playerTeam->update_cardsReceived(-(player->get_cards()));
                playerTeam->update_scoredGoals(-(player->get_score()));
                playerTeam->update_removeAGoalKeeper(player->get_isGoalKeeper());
                if (!playerTeam->get_isValid() && team_valid_before_action){ //team not valid anymore
                    valid_teams_AVL.remove(playerTeam->get_id());
                }

                // Remove player from sorted_score_List
                sorted_score_List.remove(player->get_playerScoreListNode());


            } else {
                success1 = false;
            }
            // REMOVE from WORLD_CUP AVLs (even if player does not have a team)
            success2 = all_players_AVL.remove(playerId);
            all_players_score_AVL.remove_by_item(player);
            set_top_scorer();
        } else {
            // PLAYER NOT FOUND
            return StatusType::FAILURE;
        }

    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }

    if (success1 && success2) {
        amount_players--;
        return StatusType::SUCCESS;
    }
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
        std::shared_ptr<Player> player = all_players_AVL.get_content(playerId); // O(log(players))
        if (player != nullptr) {
            Team* playerTeam = player->get_team();
            if (playerTeam == nullptr){
                return StatusType::FAILURE;
            }
            all_players_score_AVL.remove_by_item(player);
            playerTeam->remove_player(playerId);
            // UPDATE PLAYER
            player->update_gamesPlayed(gamesPlayed);
            player->update_scoredGoals(scoredGoals);
            player->update_cardsReceived(cardsReceived);

            // UPDATE TEAM
            playerTeam->update_cardsReceived(cardsReceived);
            playerTeam->update_scoredGoals(scoredGoals);
            // remove and re-add for correct position in score tree
            playerTeam->add_player(player);

            // UPDATE WORLD-CUP
            // remove and re-add for correct position in score tree
            player->set_global_score_node(all_players_score_AVL.add(player));
            set_top_scorer();
            sorted_score_List.remove(player->get_playerScoreListNode());
            add_player_to_sorted_score_list(player);

        } else {
            return StatusType::FAILURE;
        }

    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }
    //
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2){
    // O(log(k))
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
    } else if (score1 < score2) {
        team2->update_totalPoints(3);
    } else {
        team1->update_totalPoints(3);
    }

    // UPDATE GAMES PLAYED O(1)
    team1->update_gamesPlayed();
    team2->update_gamesPlayed();
    // NOTE: Player->get_gamesPlayed() : takes into account Teams gamesPlayed
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    // CHECK INVALID INPUT - O(1)
    if (playerId <= 0)
        return StatusType::INVALID_INPUT;
    // FIND PLAYER - O(log(n))
    Player* player = &(*(all_players_AVL.get_content(playerId)));
    // CHECK PLAYER - O(1)
    if (player == nullptr)
        return StatusType::FAILURE;
    // RETURN - O(1)
    return player->get_gamesPlayed();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    // CHECK INVALID - O(1)
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    // FIND TEAM - O(log(k))
    Team* team = &(*(teams_AVL.get_content(teamId)));
    // GET TEAM POINTS - O(1)
    if (team == nullptr) {
        return StatusType::FAILURE;
    }
	return team->get_total_points();
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    // CHECK INVALID - O(1)
    if (newTeamId <= 0 || teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    // FIND TEAMS - O(log(k))
    Team* team1 = &(*(teams_AVL.get_content(teamId1)));
    Team* team2 = &(*(teams_AVL.get_content(teamId2)));
    if (team1 == nullptr || team2 == nullptr || (newTeamId != teamId1 && newTeamId != teamId2 && this->teams_AVL.find_id(newTeamId)))
        return StatusType::FAILURE;
    AVL_tree<std::shared_ptr<Player>>* team1_players = team1->get_AVL_tree_id();
    AVL_tree<std::shared_ptr<Player>>* team2_players = team2->get_AVL_tree_id();
    AVL_tree<std::shared_ptr<Player>>* team1_players_scores = team1->get_AVL_tree_score();
    AVL_tree<std::shared_ptr<Player>>* team2_players_scores = team2->get_AVL_tree_score();
    if (team1_players == nullptr || team2_players == nullptr ||
        team1_players_scores == nullptr || team2_players_scores == nullptr) {
        return StatusType::FAILURE;
    }
    int total_points = team1->get_total_points() + team2->get_total_points();
    int total_players = team1->get_total_players() + team2->get_total_players();
    int total_goals = team1->get_goals() + team2->get_goals();
    int total_cards = team1->get_cards() + team2->get_cards();
    int total_goalKeepers = team1->get_totalGoalKeepers() + team2->get_totalGoalKeepers();



    // CREATE TEAM - O(log(n[team1] + n[team2]))
    try {
        std::shared_ptr<Team> team0(new Team
        (
        //basic data:
        newTeamId, total_points
        ,total_players, total_goals, total_cards, total_goalKeepers,

        //new AVL trees:
         team1_players, team2_players,
         team1_players_scores, team2_players_scores
         ));

        teams_AVL.remove(teamId1);
        valid_teams_AVL.remove(teamId1);
        teams_AVL.remove(teamId2);
        valid_teams_AVL.remove(teamId2);

        try
        {
            teams_AVL.add(team0);
        }
        catch (ID_ALREADY_EXISTS&){
            return StatusType::FAILURE;
        }
        if (team0->get_isValid()){
            valid_teams_AVL.add(team0);
        }

//        //std::cout << (team0->get_AVL_tree_id())->debugging_printTree();
//        //std::cout << "amount of players in team0: " << (team0->get_total_players()) << std::endl;

    } catch (std::bad_alloc const&){
        return StatusType::ALLOCATION_ERROR;
    }


	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    //needs to be O(log(teams)), does not depend on number of players.
    // needs to be O(1) if teamId<0.
    if (teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamId < 0) // get from global tree
    {
        if (top_scorer_id != 0)
        {
            return top_scorer_id;
        }
        else{ //no players
            return StatusType::FAILURE;
        }
    }
    else{ // teamId > 0, not >= 0.
        // multiple gets_team don't matter because every one is O(log(n))
        if (teams_AVL.get_content(teamId) && //team exists
            (teams_AVL.get_content(teamId)->get_top_scorer())) //players in the team
        {
                return teams_AVL.get_content(teamId)->get_top_scorer();
        }
        else{
            return StatusType::FAILURE; // no team or no players in team
        }
    }
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    // CHECK INVALID - O(1)
    if (teamId == 0)
        return StatusType::INVALID_INPUT;
    // RETURN AMOUNT ALL PLAYERS - O(1)
    if (teamId < 0) {
        return all_players_AVL.get_amount();
    }
    // FIND TEAM - O(log(k))
    Team* team = &(*(teams_AVL.get_content(teamId)));
    if (team == nullptr )
        return StatusType::FAILURE;
    // RETURN AMOUNT PLAYERS IN TEAM - O(1)

    return team->get_AVL_tree_id()->get_amount();
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    // CHECK INVALID - O(1)
    if (teamId == 0 || output == nullptr)
        return StatusType::INVALID_INPUT;
    int arr_size;

    //inorder traversal with the right functor fills the target array with IDs of the players inside the tree.
    if (teamId < 0) {
        arr_size = all_players_score_AVL.get_amount();
        if (arr_size == 0){
            return StatusType::FAILURE;
        }
        all_players_score_AVL.in_order_traversal_wrapper(ArrayFillerFunctor_ID<std::shared_ptr<Player>>(output, arr_size));
    }
    else{ //team id > 0. not >= 0.
        std::shared_ptr<Team> team = teams_AVL.get_content(teamId);
        if (team) {
            arr_size = team->get_total_players();
            if (team->get_total_players() > 0)
            {
                team->get_AVL_tree_score()->in_order_traversal_wrapper(
                        ArrayFillerFunctor_ID<std::shared_ptr<Player>>(output, arr_size));
            }
            else{
                return StatusType::FAILURE;
            }

        }
        else{
            return StatusType::FAILURE;
        }
    }

    return StatusType::SUCCESS;
}


output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if (playerId <= 0 || teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (all_players_AVL.get_amount() <= 1) {
        return StatusType::FAILURE;
    }

    try {
        // FIND PLAYER
        Team* team = &(*(teams_AVL.get_content(teamId)));
        if (team == nullptr) {
            return StatusType::FAILURE;
        }
        std::shared_ptr<Player> player = team->find_player(playerId); // O(log(n))

        if (player != nullptr) {
            // PLAYER FOUND
            NodeList::Node* node_in_list = player->get_playerScoreListNode();
            return sorted_score_List.get_closest(node_in_list);

        } else {
            // PLAYER NOT FOUND
            return StatusType::FAILURE;
        }

    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	if (minTeamId<0 || maxTeamId<0 || maxTeamId<minTeamId)
            return StatusType::INVALID_INPUT;
    if (valid_teams_AVL.get_amount() < 1) {
        return StatusType::FAILURE;
    }
    try {
        NodeList list;
        valid_teams_AVL.add_to_list(list, minTeamId, maxTeamId);
        int winnerId = list.knockout();
        if (winnerId < 1)
            return StatusType::FAILURE;
        return winnerId;
    } catch (std::bad_alloc const&){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

void world_cup_t::set_top_scorer() {
    if (all_players_score_AVL.get_biggest_in_tree() != nullptr)
    {
        top_scorer_id = all_players_score_AVL.get_biggest_in_tree()->get_id();
    }
    else
    {
        top_scorer_id = 0;
    }
}

void world_cup_t::add_player_to_sorted_score_list(const std::shared_ptr<Player>& player) {
    // Add player to sorted_score_List
    AVL_tree<std::shared_ptr<Player>>::Node* close_node = all_players_score_AVL.find_a_closest(player->get_global_score_node()); // find neighbor
    if (close_node != nullptr && close_node->content != nullptr) {
        // Get where close_node points to itself in the list
        NodeList::Node* close_node_in_list = close_node->content->get_playerScoreListNode();
        if (close_node_in_list == nullptr) {
            //std::cout << "ERROR: all players should point to where they are in the list" << std::endl;
            throw;
        }
        // Add to the list our new player (and make our player point to its location in the list)
        NodeList::Node* newNode = sorted_score_List.add(close_node_in_list, player->get_id(), 0, player->get_score(), player->get_cards());
        player->set_playerScoreListNode(newNode);

    } else { // empty list
        // add player directly with nullptr
        NodeList::Node* newNode = sorted_score_List.add(nullptr, player->get_id(), 0, player->get_score(), player->get_cards());
        player->set_playerScoreListNode(newNode);
    }
}
