#include "Team.h"



Team::Team(int id)
: id(id),total_players(0),total_points(0),total_cards(0),top_scorer(nullptr),
team_players(SORT_BY_ID),team_players_scores(SORT_BY_SCORE)
{}

int Team::get_id() const{
    return id;
}

int Team::operator~() {
    return get_id();
}

int Team::operator!() {
    return get_points();
}

int Team::get_points() const{
    return total_points;
}

void Team::add_player(Player* player) {
    team_players.add(player);
    team_players_scores.add(player);
    if (top_scorer == nullptr) {
        top_scorer = player;
    } else if (top_scorer->get_score() < player->get_score()) {
        top_scorer = player;
    } else if (top_scorer->get_score() == player->get_score() && top_scorer->get_id() == player->get_id()) {
        top_scorer = player;
    }
}

void Team::remove_player(int id)
{
    team_players.remove(id);
    team_players_scores.remove(id);
    // TODO: top_scorer mechanism when you have remove
}

AVL_tree<Player*>* Team::get_AVL_tree_id()
{
    return &team_players;
}

AVL_tree<Player*>* Team::get_AVL_tree_score()
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