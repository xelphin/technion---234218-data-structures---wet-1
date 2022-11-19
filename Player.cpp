#include "Player.h"

Player::Player() {}


int Player::get_score() {
    return score;
}

int Player::get_id() {
    return id;
}

int Player::operator~() {
    return get_id();
}

int Player::operator!() {
    return get_score();
}

