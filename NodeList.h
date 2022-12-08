//
// Created by Administrator on 04/12/2022.
//

#ifndef NODELIST_TEAMS_H
#define NODELIST_TEAMS_H

#include <string>
#include <iostream>

// USED ONLY FOR KNOCKOUT

class NodeList {
public:
    class Node;

    explicit NodeList(); // O(1)
    ~NodeList() = default;
    NodeList(const NodeList &) = delete; //cant copy trees
    NodeList &operator=(NodeList &other) = delete;

    // Add (inorder) the valid teams
    void add(int id, int total_points, int total_goals, int total_cards);
    NodeList::Node* add(Node* nodeNextTo, int id, int total_points, int total_goals, int total_cards);
    int get_closest(Node* node) const;
    void remove(Node* node);
    int knockout();
    std::string debug_print();

private:
    Node* start;
    Node* end;

    void call_match();
    int get_winnerId(Node& team1, Node& team2);
    bool player1_biggerScorer(Node& player1, Node& player2);
};
//
class NodeList::Node{ // Node => Represents a Teams Stats
public:
    Node(int id) : id(id){};
////    NodeList::Node *prev;
////    NodeList::Node *next;
    int id;
////    int total_points;
////    int total_goals;
////    int total_cards;
//////
//////    explicit Node(int id, int total_points, int total_goals, int total_cards);
//////
//////    int get_match_points() const;
//////    int get_id() const;
//////
//////    Node(const Node &) = delete; //cant copy nodes. make new ones.
//////    Node &operator=(Node &other) = delete;
//////    ~Node() = default;
////
////
};

#endif //NODELIST_TEAMS_H
