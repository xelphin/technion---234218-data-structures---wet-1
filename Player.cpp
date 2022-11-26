#include "Player.h"

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) 
: playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper)
{
    // TODO: find Team using TeamId and connect our Team* to it (if team doesn't exist -> throw error)
}

int Player::get_score() const {
    return goals;
}

int Player::get_id() const {
    return playerId;
}

int Player::operator~() {
    return get_id();
}

int Player::operator!() {
    return get_score();
}

std::ostream& operator<<(std::ostream& os, const Player& toPrint)
{
    os << toPrint.get_id();
    return os;
}

int Player::compare(const Player& player2, bool sort_by_score) const
{
    if (sort_by_score == SORT_BY_SCORE){
        int score_diff = Player::get_score() - player2.get_score();
        if (score_diff != 0)
            return score_diff;
        else
            return Player::get_id() - player2.get_id();
    }
    else
    {
        return Player::get_id() - player2.get_id();
    }
}
