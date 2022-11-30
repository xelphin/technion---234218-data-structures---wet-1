#include "Player.h"

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) 
: playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper), team(nullptr)
{
    // TODO: find Team using TeamId and connect our Team* to it (if team doesn't exist -> throw error)
}

int Player::get_score() const {
    return goals;
}

int Player::get_id() const {
    return playerId;
}

int Player::get_gamesPlayed() const
{
    if (team != nullptr)
        return gamesPlayed + team->get_gamesPlayed();
    return gamesPlayed;
}

int Player::get_cards() const
{
    return Player::cards;
}
bool Player::get_isGoalKeeper() const
{
    return goalKeeper;
}
int Player::operator ~() const {
    return get_id();
}

int Player::operator !() const {
    return get_score();
}

std::ostream& operator<<(std::ostream& os, const Player& toPrint)
{
    os << toPrint.get_id();
    return os;
}

int Player::compare(const Player& player2, bool sort_by_score) const
{
    //TODO: should maybe return bool instead of int?
    if (this->get_id() == player2.get_id()){
        throw IDENTICAL_IDS();
    }
    if (sort_by_score == SORT_BY_SCORE){
        int score_diff = this->get_score() - player2.get_score();
        if (score_diff != 0)
            return score_diff;
        else // if scores are identical, compare id. one id has to be bigger than the other since its different players.
            return this->get_id() - player2.get_id();
    }
    else
    {
        return Player::get_id() - player2.get_id();
    }
}

void Player::set_team(Team* playerTeam)
{
   this->team = playerTeam;
}

Team* Player::get_team() const
{
    return this->team;
}

void Player::update_gamesPlayed(int toAdd)
{
    this->gamesPlayed += toAdd;
}
void Player::update_scoredGoals(int toAdd)
{
    this->goals += toAdd;
}
void Player::update_cardsReceived(int toAdd)
{
    this->cards += toAdd;
}