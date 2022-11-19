#include "Team.h"

void Team::add_player() {

}

Team::Team(int id, int totalPlayers, int totalPoints, int totalCards, Player *topScorer,
           const AVL_tree<Player> &teamPlayers, const AVL_tree<Player> &teamPlayersScores) :
           id(id),total_players(totalPlayers),total_points(totalPoints),total_cards(totalCards),top_scorer(topScorer),
            team_players(teamPlayers),team_players_scores(teamPlayersScores) {}

int Team::get_id() {
    return id;
}

int Team::operator~() {
    return get_id();
}

int Team::operator!() {
    return get_points();
}

int Team::get_points() {
    return total_points;
}
