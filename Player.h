#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H

#include "Team.h"
#include "NodeList.h"
#include "AVL_tree.h"
#include <memory>



class Team;

class Player{
public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);

    int get_score() const;
    int get_id() const;
    int get_gamesPlayed() const;
    int get_gamesPlayed_withoutTeam() const;
    int get_cards() const;
    bool get_isGoalKeeper() const;
    Team* get_team() const;
    int compare(const Player& player2, bool sort_by_score) const;
    bool get_closest_from_pair(const std::shared_ptr<Player>& player1, const std::shared_ptr<Player>& player2) const;
    int operator SCORE(const Player&) const;
    int operator ID() const;
    AVL_tree<std::shared_ptr<Player>>::Node* get_global_score_node();
    NodeList::Node* get_playerScoreListNode();

    void change_team(Team* new_team);
    void set_team(Team* playerTeam);
    void update_gamesPlayed(int toAdd);
    void set_gamesPlayed();
    void update_scoredGoals(int toAdd);
    void update_cardsReceived(int toAdd);
    void set_global_score_node(AVL_tree<std::shared_ptr<Player>>::Node* node);
    void set_playerScoreListNode(NodeList::Node* node);


    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    int playerId;
    int teamId;

    int gamesPlayed;
    int goals;
    int cards;
    bool goalKeeper;
    Team* team;
    AVL_tree<std::shared_ptr<Player>>::Node* global_scorers_tree_node;
    NodeList::Node* playerScoreListNode;
};

// used to iterate on inorder_traversal and add all players to a new array.
class Functor{
private:
    Team* new_team;
public:
    explicit Functor(Team* team): new_team(team){}

    // call is: functor(node->content);
    void operator() (std::shared_ptr<Player>& player) {
        player->change_team(new_team);
    }
};




#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_PLAYER_H
