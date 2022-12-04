//
// Created by Administrator on 04/12/2022.
//

#ifndef NODELIST_TEAMS_H
#define NODELIST_TEAMS_H

// USED ONLY FOR KNOCKOUT

class NodeList_Teams {
public:
    class Node;

    explicit NodeList_Teams(); // O(1)

    ~NodeList_Teams();

    NodeList_Teams(const NodeList_Teams &) = delete; //cant copy trees
    NodeList_Teams &operator=(NodeList_Teams &other) = delete;

    // Add (inorder) the valid teams
    void add(int id, int total_points, int total_goals, int total_cards);
    int knockout();

private:
    NodeList_Teams::Node *start;
    NodeList_Teams::Node *end;
};

class NodeList_Teams::Node{ // Node => Represents a Teams Stats
public:
    NodeList_Teams::Node *next;
    int id;
    int total_points;
    int total_goals;
    int total_cards;

    explicit Node(int id, int total_points, int total_goals, int total_cards);

    Node(const NodeList_Teams &) = delete; //cant copy nodes. make new ones.
    Node &operator=(NodeList_Teams &other) = delete;
    ~Node() = default;


};

#endif //NODELIST_TEAMS_H
