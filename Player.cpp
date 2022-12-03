#include "Player.h"

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) 
: playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), goalKeeper(goalKeeper), team(nullptr)
{
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
int Player::operator ID() const {
    return get_id();
}

int Player::operator SCORE(const Player& other) const {
    int scoreDiff = get_score() - other.get_score();
        int cardDiff = get_cards() - other.get_cards();
        if (scoreDiff != 0)
            return scoreDiff;
        else if (cardDiff != 0)
            return -cardDiff; // should be negative because more cards is bad.
        return get_id() - other.get_id();
}

std::ostream& operator<<(std::ostream& os, const Player& toPrint)
{
    os << toPrint.get_id();
    return os;
}

int Player::compare(const Player& player2, bool sort_by_score) const
{
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

void Player::set_gamesPlayed()
{
    if (team != nullptr)
        this->gamesPlayed += gamesPlayed + team->get_gamesPlayed();
}

void Player::update_scoredGoals(int toAdd)
{
    this->goals += toAdd;
}
void Player::update_cardsReceived(int toAdd)
{
    this->cards += toAdd;
}

void Player::change_team(Team* new_team) {
    set_gamesPlayed();
    set_team(new_team);
}

bool Player::get_closest_from_pair(const std::shared_ptr<Player>& player1, const std::shared_ptr<Player>& player2) const {
    //true for player 1 is closer, false for player 2 is closer.
    //returns the closest of the two players, corresponding to get_closest_player instruction.

    //comparing score:
    if (abs(get_score() - player1->get_score()) > abs(get_score() - player2->get_score())){
        return false; // score is closest.
    }
    else if (abs(get_score() - player1->get_score()) < abs(get_score() - player2->get_score())){
        return true;
    }

    else{
        // comparing cards
        if (abs(get_cards() - player1->get_cards()) > abs(get_cards() - player2->get_cards())){
            return false;
        }
        else if (abs(get_cards() - player1->get_cards()) < abs(get_cards() - player2->get_cards())){
            return true;
        }

        else{
            // comparing IDs
            if (abs(get_id() - player1->get_id()) > abs(get_id() - player2->get_id())){
                return false;
            }
            else if (abs(get_id() - player1->get_id()) < abs(get_id() - player2->get_id())){
                return true;
            }

            else{
                // return bigger id
                if (player1->get_id() > player2->get_id())
                {
                    return true; // true == player 1
                }
            }
        }
    }
    throw;
}

void Player::set_global_score_node(AVL_tree<std::shared_ptr<Player>>::Node* node) {
    global_scorers_tree_node = node;
}

AVL_tree<std::shared_ptr<Player>>::Node *Player::get_global_score_node() {
    return global_scorers_tree_node;
}
