#include "Player.h"

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) 
: playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper)
{

}

int Player::get_score() {
    return goals;
}

int Player::get_id() {
    return playerId;
}

int Player::operator~() {
    return get_id();
}

int Player::operator!() {
    return get_score();
}


