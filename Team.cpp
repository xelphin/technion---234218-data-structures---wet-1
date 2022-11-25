#include "Team.h"



Team::Team(int id)
: id(id),total_players(0),total_points(0),total_cards(0),top_scorer(nullptr),
team_players(SORT_BY_SCORE),team_players_scores(SORT_BY_ID)
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

std::ostream& operator<<(std::ostream& os, const Team& toPrint)
{
    os << toPrint.get_id();
    return os;
}