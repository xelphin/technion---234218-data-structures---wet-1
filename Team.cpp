#include "Team.h"



Team::Team(int id, int points)
: id(id),total_players(0),total_points(points), total_goals(0), total_cards(0), total_goalKeepers(0),
wins(0), gamesPlayed(0), top_scorer(nullptr), team_players(SORT_BY_ID),team_players_scores(SORT_BY_SCORE)
{}

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

void Team::add_player(std::shared_ptr<Player> player) { //TODO: clang tidy: make player a const reference?
    // TODO: check that the argument is valid
    team_players.add(player);
    team_players_scores.add(player);
    if (top_scorer == nullptr ||
        (top_scorer->get_score() < player->get_score()) ||
        (top_scorer->get_score() == player->get_score() && top_scorer->get_id() == player->get_id()))
    {
        top_scorer = &*player;
    }
    total_players++;
}

std::shared_ptr<Player> Team::find_player(int id)
{
    // O(log(n))
    // TODO: make sure this does not need to return a pointer to the shared pointer.
    return team_players.get_content(id);
}

bool Team::remove_player(int id)
{
    bool success = team_players.remove(id);
    team_players_scores.remove(id);
    if (success) {
        total_players--;
    }
    return success;
    // TODO: top_scorer mechanism when you have remove
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
        this->total_goalKeepers += 1;
}

void Team::update_removeAGoalKeeper(bool remove)
{
    if (remove)
        this->total_goalKeepers -= 1;
}
void Team::update_totalPoints(int toAdd)
{
    this->total_points += toAdd;
}

void Team::update_wins()
{
    this->wins++;
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