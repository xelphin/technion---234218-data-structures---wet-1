#include "Team.h"



Team::Team(int id, int points)
: id(id),total_players(0),total_points(points), total_goals(0), total_cards(0), total_goalKeepers(0),
 gamesPlayed(0), top_scorer(nullptr), team_players(SORT_BY_ID),team_players_scores(SORT_BY_SCORE)
{}

// C'tor used for merging two different teams

Team::Team(int id, int points, int total_players, int total_goals, int total_cards, int total_goalKeepers, Player* top_scorer,
     AVL_tree<std::shared_ptr<Player>>* team1_players, AVL_tree<std::shared_ptr<Player>>* team2_players,
     AVL_tree<std::shared_ptr<Player>>* team1_players_scores, AVL_tree<std::shared_ptr<Player>>* team2_players_scores)
     : id(id), total_players(total_players), total_points(points), total_goals(total_goals),
       total_cards(total_cards), total_goalKeepers(total_goalKeepers), gamesPlayed(0), top_scorer(top_scorer),
       team_players(*team1_players, *team2_players, SORT_BY_ID),
       team_players_scores(*team1_players_scores, *team2_players_scores, SORT_BY_SCORE)
       // Each Calls: c'tor of AVL_tree and creates new tree with all players from team1 and team2
{

}



int Team::get_id() const{
    return id;
}

int Team::operator ID() const {
    return get_id();
}

int Team::operator SCORE() const {
    return get_points();
}

int Team::get_points() const{
    return total_points;
}

void Team::add_player(const std::shared_ptr<Player>& player) {
    if (player == nullptr)
        return;
    team_players.add(player);
    team_players_scores.add(player);
    // TODO M: Matan fix this lol
//    if (top_scorer == nullptr ||
//        (top_scorer->get_score() < player->get_score()) ||
//        (top_scorer->get_score() == player->get_score() && top_scorer->get_id() == player->get_id()))
//    {
//        top_scorer = &*player;
//    }
    total_players++;
}

std::shared_ptr<Player> Team::find_player(int id)
{
    // O(log(n))
    // TODO M: make sure this does not need to return a pointer to the shared pointer.
    return team_players.get_content(id);
}

bool Team::remove_player(int player_id)
{
    // needs to be O(players in the system)
    bool success = team_players.remove(player_id);
    team_players_scores.remove(player_id);
    if (success) {
        total_players--;
    }
    return success;
    // TODO M: top_scorer mechanism when you have remove. possibly use inorder_traversal() for that, since we just need O(n), not log.
}

AVL_tree<std::shared_ptr<Player>>* Team::get_AVL_tree_id()
{
    return &team_players;
}

AVL_tree<std::shared_ptr<Player>>* Team::get_AVL_tree_score()
{
    return &team_players_scores;
}

std::ostream& operator<<(std::ostream& os, const Team& toPrint)
{
    os << toPrint.get_id();
    return os;
}

int Team::compare(const Team& team2, bool sort_by_score) const
{
    //TODO M: make sure int is right return type.
    if (sort_by_score == SORT_BY_SCORE){
        int score_diff = Team::get_points() - team2.get_points();
        if (score_diff != 0)
            return score_diff;
        else
            return Team::get_id() - team2.get_id();
    }
    else
    {
        return Team::get_id() - team2.get_id();
    }
}

void Team::update_scoredGoals(int toAdd)
{
    this->total_goals += toAdd;
}
void Team::update_cardsReceived(int toAdd)
{
    this->total_cards += toAdd;
}

void Team::update_addAGoalKeeper(bool add)
{
    if (add)
        this->total_goalKeepers++;
}

void Team::update_removeAGoalKeeper(bool remove)
{
    if (remove)
        this->total_goalKeepers--;
}
void Team::update_totalPoints(int toAdd)
{
    this->total_points += toAdd;
}

void Team::update_gamesPlayed()
{
    this->gamesPlayed++;
}

int Team::get_cards() const
{
    return total_cards;
}

int Team::get_goals() const
{
    return total_goals;
}

int Team::get_total_players() const
{
    return total_players;
}

int Team::get_total_points() const
{
    return total_points;
}

int Team::get_match_score() const
{
    return total_points + total_goals - total_cards;
}

int Team::get_gamesPlayed() const
{
    return gamesPlayed;
}

int Team::get_totalGoalKeepers() const
{
    return total_goalKeepers;
}

bool Team::get_isValid() const
{
    if (total_goalKeepers > 0 && total_players > 10) {
        return true;
    }
    return false;
}