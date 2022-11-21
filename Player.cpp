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

AVL_tree<Player>::COMPARISON Player::compare(Player& b, bool sortBy)
{
    int a_value, b_value;
    if (sortBy == SORT_BY_ID) {
        a_value = this->get_id();
        b_value = b.get_id();
    } else {
        a_value = this->get_score();
        b_value = b.get_score();   
    }
    return Player::compareValues(a_value, b_value);
}

AVL_tree<Player>::COMPARISON Player::compareValues(int a_value, int b_value)
{
    if (a_value > b_value)
        return AVL_tree<Player>::COMPARISON::A_BIGGER_THAN_B;
    else if (a_value < b_value)
        return AVL_tree<Player>::COMPARISON::A_SMALLER_THAN_B;
    return AVL_tree<Player>::COMPARISON::A_EQUAL_TO_B;
}

