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
